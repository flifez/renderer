//
// Created by flif3 on 8/2/2023.
//


#include <random>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include "Renderer.h"

namespace Raytracer {
    std::mutex consoleMutex;
    std::mutex queueMutex;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable condition;

    const unsigned int NUM_THREADS = std::thread::hardware_concurrency();

    bool all_tasks_submitted = false;

    Vec3 adjustGamma(const Vec3& color, float gamma = 2.2f) {
        float inverseGamma = 1.0f / gamma;
        return {pow(color.x, inverseGamma), pow(color.y, inverseGamma), pow(color.z, inverseGamma)};
    }

    void clampColor(Vec3& color) {
        color.x = std::min(color.x, 1.0);
        color.y = std::min(color.y, 1.0);
        color.z = std::min(color.z, 1.0);
    }

    float random_float() {
        static std::uniform_real_distribution<float> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    void displayProgressBar(unsigned int numThreads, int threadId, int progress, int total) {
        int barWidth = 1200 / numThreads;

        int lineNumber = 5 + threadId;

        consoleMutex.lock();
        std::cout << "\033[" << lineNumber << ";0H";
        std::cout << "[";
        int pos = barWidth * progress / total;
        for (int i = 0; i < barWidth; i++) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "]" << int(progress / (float)total * 100.0) << "% (thread " << threadId << ")";
        std::cout.flush();
        consoleMutex.unlock();
    }

    void worker(){
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);

                condition.wait(lock, [&]{ return !tasks.empty() || all_tasks_submitted; });
                if (tasks.empty()) {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();
            }

            task();
        }
    }

    void Renderer::render() const {
        int width = w;
        int height = h;
        const int SAMPLES_PER_PIXEL = 8;
        int sqrt_samples = sqrt(SAMPLES_PER_PIXEL);

        std::vector<unsigned char> pixels(width * height * 3);

        auto render_section = [&](int start, int end, int threadId) {
            const int ITERATIONS = 1;
            const int SAMPLES_PER_PIXEL = 64;

            for (int iteration = 0; iteration < ITERATIONS; iteration++) {
                for (int y = start; y < end; y++) {

                    displayProgressBar(NUM_THREADS, threadId, y - start, end - start);

                    for (int x = 0; x < width; x++) {
                        Vec3 color(0, 0, 0);

                        for (int p = 0; p < sqrt_samples; p++) {
                            for(int q = 0; q < sqrt_samples; q++) {
                                float u = (x + (p + random_float()) / sqrt_samples) / (width - 1);
                                float v = (y + (q + random_float()) / sqrt_samples) / (height - 1);
                                Ray ray = scene.getCamera().generateRay(u, v);
                                HitInfo hitInfo = scene.findClosestIntersection(ray, 0);

                                if (hitInfo.material == nullptr) {
                                    color = color + scene.getAmbient();
                                } else {
                                    color = color + calculateColor(ray, hitInfo);
                                }
                            }
                        }

                        color = color / float(SAMPLES_PER_PIXEL);

                        // gamma correction
                        color = adjustGamma(color, 1.0f);
                        clampColor(color);

                        // convert color from float to byte
                        pixels[(y * width + x) * 3 + 0] += static_cast<unsigned char>(color.x * 255.99 / ITERATIONS);
                        pixels[(y * width + x) * 3 + 1] += static_cast<unsigned char>(color.y * 255.99 / ITERATIONS);
                        pixels[(y * width + x) * 3 + 2] += static_cast<unsigned char>(color.z * 255.99 / ITERATIONS);
                    }
                }
            }
        };

        // create threads
        for (unsigned int i = 0; i < NUM_THREADS; i++) {
            threads.emplace_back(worker);
        }

        for (unsigned int i = 0; i < NUM_THREADS; i++) {
            int start = i * height / NUM_THREADS;
            int end = (i + 1) * height / NUM_THREADS;

            tasks.push([=]{
                render_section(start, end, i);
            });
        }

        all_tasks_submitted = true;

        condition.notify_all();

        // join threads
        for (auto& thread : threads) {
            thread.join();
        }

        stbi_write_png("image.png", width, height, 3, pixels.data(), width * 3);
    }

    // color calculation: for each light in the scene, we calculate the color of the light, and add it to the color of the pixel
    Vec3 Renderer::calculateColor(const Ray& ray, const HitInfo& hitInfo) const {
        const float EPSILON = 0.0001f;
        Vec3 color(0, 0, 0);  // Initialize color as black

        for (const std::shared_ptr<Light>& light : scene.getLights()) {
            Vec3 lightDirection = light->getDirection(hitInfo.point);
            Vec3 viewDirection = scene.getCamera().getDirection(hitInfo.point);
            Vec3 lightIntensity = light->getIntensity(hitInfo.point);
            Vec3 lightColor = light->getColor();
            color = color + hitInfo.material->shade(lightDirection,
                                                    viewDirection,
                                                    hitInfo.normal,
                                                    lightColor,
                                                    lightIntensity,
                                                    scene.getAmbient());
        }

        const_cast<HitInfo&>(hitInfo).depth++;

        // recursive raytracing: if we have not reached the maximum recursion depth (MAX_DEPTH), and the material is reflective or refractive, then we calculate the color of the reflected or refracted ray
        if (hitInfo.depth < MAX_DEPTH && (hitInfo.material->isReflective() || hitInfo.material->isRefractive())) {
            // epsilon offsetting: we offset the ray origin by a small amount in the direction of the normal, to prevent self-intersection
            Vec3 offsetOrigin = hitInfo.point + hitInfo.normal * EPSILON;

            Ray reflectedRay = ray.reflect(offsetOrigin, hitInfo.normal);
            Ray refractedRay = ray.refract(offsetOrigin, hitInfo.normal, hitInfo.material->getRefractiveIndex());

            HitInfo reflectedHitInfo = scene.findClosestIntersection(reflectedRay, hitInfo.depth);
            HitInfo refractedHitInfo = scene.findClosestIntersection(refractedRay, hitInfo.depth);

            if (hitInfo.material->isReflective() && reflectedHitInfo.material != nullptr) {
                color = color + calculateColor(reflectedRay, reflectedHitInfo) * hitInfo.material->getReflectivity();
            }

            if (hitInfo.material->isRefractive() && refractedHitInfo.material != nullptr) {
                color = color + calculateColor(refractedRay, refractedHitInfo) * hitInfo.material->getTransparency();
            }
        }

        return color;
    }

} // Raytracer
