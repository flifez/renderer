#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Renderer/Renderer.h"
#include "Objects/ObjectVariants/Sphere.h"
#include "Materials/MaterialVariants/DiffuseMaterial.h"
#include "Lights/LightVariants/PointLight.h"

int main() {
    Raytracer::DiffuseMaterial diffuseMaterial(Raytracer::Vec3(0.8, 0.3, 0.3), 0.1, 0.7);
    Raytracer::Vec3 pos(0, 0, 1);
    std::shared_ptr<Raytracer::Sphere> sphere = std::make_shared<Raytracer::Sphere>(&diffuseMaterial, pos, 0.3);

    std::shared_ptr<Raytracer::PointLight> pointLight =
            std::make_shared<Raytracer::PointLight>(Raytracer::Vec3(0.5, 0.5, 0.5), Raytracer::Vec3(1, 1, 1), 10.0);

    Raytracer::Vec3 position(0, 0, 0);
    Raytracer::Vec3 orientation(0, 0, 1);
    float fov = 90.0f;

    Raytracer::BasicCamera camera(position, orientation, fov, 0.75f);

    Raytracer::Scene scene(camera);
    scene.addObject(sphere);
    scene.addLight(pointLight);
    scene.setAmbientLight(Raytracer::Vec3(0.5, 0.5, 0.5));

    Raytracer::Renderer renderer(scene);
    renderer.render();
    std::cout << "1";
}

