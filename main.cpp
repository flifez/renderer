#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Renderer/Renderer.h"
#include "Objects/ObjectVariants/Sphere.h"
#include "Materials/MaterialVariants/BlinnPhongMaterial.h"
#include "Lights/LightVariants/PointLight.h"
#include "Materials/MaterialVariants/DiffuseMaterial.h"
#include "Materials/MaterialVariants/MirrorMaterial.h"
#include "Lights/LightVariants/AreaLight.h"
#include "Lights/LightVariants/SunLight.h"

const int MAX_DEPTH = 5;

int main() {
    std::cout << "Renderer initializing..." << std::endl;

    Raytracer::BlinnPhongMaterial blinnPhongMaterial(Raytracer::Vec3(0.3, 0.3, 0.8), 0.4, 0.8, 500);
    Raytracer::MirrorMaterial mirrorMaterialDefault(Raytracer::Vec3(0.7, 0.7, 0.7), 0.7);
    Raytracer::MirrorMaterial mirrorMaterialRed(Raytracer::Vec3(0.8, 0.3, 0.3), 0.7);
    Raytracer::DiffuseMaterial diffuseMaterial(Raytracer::Vec3(0.3, 0.8, 0.3), 0.7);
    Raytracer::Vec3 pos1(-0.5, 0.2887, 1.0);
    Raytracer::Vec3 pos2(0.5, 0.2887, 1.0);
    Raytracer::Vec3 pos3(0, -0.5773, 1.0);
    Raytracer::Vec3 pos4(-1, -0.5773, 1.0);
    std::shared_ptr<Raytracer::Sphere> sphere1 = std::make_shared<Raytracer::Sphere>(&blinnPhongMaterial, pos1, 0.3);
    std::shared_ptr<Raytracer::Sphere> sphere2 = std::make_shared<Raytracer::Sphere>(&mirrorMaterialDefault, pos2, 0.3);
    std::shared_ptr<Raytracer::Sphere> sphere3 = std::make_shared<Raytracer::Sphere>(&diffuseMaterial, pos3, 0.3);
    std::shared_ptr<Raytracer::Sphere> sphere4 = std::make_shared<Raytracer::Sphere>(&mirrorMaterialRed, pos4, 0.3);

    std::shared_ptr<Raytracer::PointLight> pointLight =
            std::make_shared<Raytracer::PointLight>(Raytracer::Vec3(0.5, -0.5, 0.5), Raytracer::Vec3(1, 1, 1), 4.0);
    std::shared_ptr<Raytracer::AreaLight> areaLight =
            std::make_shared<Raytracer::AreaLight>(Raytracer::Vec3(0.5, 0.5, 0.5),
                                                   Raytracer::Vec3(0, 1, 0),
                                                   Raytracer::Vec3(1, 1, 1),
                                                   1, 0.5, 0.5);
    std::shared_ptr<Raytracer::SunLight> sunLight =
            std::make_shared<Raytracer::SunLight>(Raytracer::Vec3(0, 0, 1), Raytracer::Vec3(1, 1, 1), 0.8);

    Raytracer::Vec3 position(0, 0, -3);
    Raytracer::Vec3 orientation(0, 0, 1);
    float fov = 20.0f;

    Raytracer::BasicCamera camera(position, orientation, fov, 0.75f);

    Raytracer::Scene scene(camera);
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(sphere4);
    // scene.addLight(pointLight);
    // scene.addLight(areaLight);
    scene.addLight(sunLight);
    scene.setAmbient(Raytracer::Vec3(1, 1, 1), 0.1);

    std::cout << "Scene built successfully. Starting rendering..." << std::endl;

    Raytracer::Renderer renderer(2400, 1800, scene);
    renderer.render();

    std::cout << "Finished Rendering.";
}
