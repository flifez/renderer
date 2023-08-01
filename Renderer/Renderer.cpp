//
// Created by flif3 on 8/2/2023.
//

#include "Renderer.h"

namespace Raytracer {
    void Renderer::render() const {
        int width = 800;
        int height = 600;

        std::vector<unsigned char> pixels(width * height * 3);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float u = float(x) / (width - 1);
                float v = float(y) / (height - 1);
                Ray ray = scene.getCamera().generateRay(u, v);
                HitInfo hitInfo = scene.findClosestIntersection(ray);
                if (hitInfo.material != nullptr) {
                    Vec3 color = calculateColor(ray, hitInfo);

                    // convert color from float to byte
                    pixels[(y * width + x) * 3 + 0] = static_cast<unsigned char>(color.x * 256);
                    pixels[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color.y * 256);
                    pixels[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color.z * 256);

                    //pixels[(x * height + y) * 3 + 0] = static_cast<unsigned char>(color.x * 255.99);
                    //pixels[(x * height + y) * 3 + 1] = static_cast<unsigned char>(color.y * 255.99);
                    //pixels[(x * height + y) * 3 + 2] = static_cast<unsigned char>(color.z * 255.99);
                }
            }
        }

        stbi_write_png("image.png", width, height, 3, pixels.data(), width * 3);
    }

    Vec3 Renderer::calculateColor(const Ray &ray, const Raytracer::HitInfo &hitInfo) const {
        Vec3 color = scene.getAmbientLight() * hitInfo.material->getColor();

        for (const std::shared_ptr<Light>& light : scene.getLights()) {
            Vec3 lightDirection = light->getDirection(hitInfo.point);
            Vec3 lightIntensity = light->getIntensity(hitInfo.point);
            Vec3 lightColor = light->getColor();
            color = color + hitInfo.material->shade(lightDirection, hitInfo.normal, lightColor, lightIntensity);
        }

        return color;
    }
} // Raytracer