//
// Created by flif3 on 8/2/2023.
//

#pragma once

#include "../stb_image_write.h"
#include "../Scene/Scene.h"

namespace Raytracer {

    class Renderer {
    public:
        explicit Renderer(int w, int h, const Scene& scene) : w(w), h(h), scene(scene) {}

        void render() const;

    private:
        const Scene& scene;
        int w;
        int h;

        Vec3 calculateColor(const Ray& ray, const HitInfo& hitInfo) const;
    };

} // Raytracer
