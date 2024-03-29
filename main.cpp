#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Renderer/Renderer.h"

#include "Objects/ObjectVariants/Sphere.h"
#include "Materials/MaterialVariants/BlinnPhongMaterial.h"
#include "Lights/LightVariants/PointLight.h"

#include "Materials/MaterialVariants/DiffuseMaterial.h"

#include "Materials/MaterialVariants/MirrorMaterial.h"
#include "Lights/LightVariants/AreaLight.h"

#include "Lights/LightVariants/SunLight.h"
#include "Objects/ObjFileParser.h"

const int MAX_DEPTH = 5;

int main() {
    std::cout << "Renderer initializing..." << std::endl;

    Raytracer::DiffuseMaterial diffuseMaterial(Raytracer::Vec3(0.8, 0.8, 0.8), 0.8);
    Raytracer::BlinnPhongMaterial blinnPhongMaterial(Raytracer::Vec3(0.8, 0.8, 0.3), 0.4, 0.5, 0.9, 0);
    Raytracer::MirrorMaterial mirrorMaterial(Raytracer::Vec3(0.8, 0.3, 0.3), 0.9);

    Raytracer::Mesh mesh = Raytracer::ObjFileParser::parse("../Resources/bunny-lowpoly.obj", &mirrorMaterial);
    mesh.scale(1);
    mesh.rotate(Raytracer::Vec3(3.14159, 0.9 * 3.14159, -3.14159/2.2));

    std::vector<Raytracer::Triangle> triangles;
    triangles.emplace_back(Raytracer::Vec3(0, -20, -577.3),
                       Raytracer::Vec3(500, -20, 288.7),
                      Raytracer::Vec3(-500, 10, 288.7));
    std::shared_ptr<Raytracer::Mesh> mesh1 = std::make_shared<Raytracer::Mesh>(triangles, &diffuseMaterial);

    std::shared_ptr<Raytracer::Mesh> bunny = std::make_shared<Raytracer::Mesh>(mesh);

    std::shared_ptr<Raytracer::SunLight> sunLight =
            std::make_shared<Raytracer::SunLight>(Raytracer::Vec3(0, 1, 0), Raytracer::Vec3(1, 1, 1), 0.5);

    std::shared_ptr<Raytracer::PointLight> pointLight =
            std::make_shared<Raytracer::PointLight>(Raytracer::Vec3(30, -80, -80), Raytracer::Vec3(1, 1, 1), 30000.0);

    Raytracer::Vec3 position(-375, -40, -400);
    Raytracer::Vec3 orientation(1, 0, 1);
    float fov = 18.0f;

    Raytracer::BasicCamera camera(position, orientation, fov, 0.75f, 1/1.2, 500);

    Raytracer::Scene scene(camera);
    scene.addObject(bunny);
    scene.addObject(mesh1);
    scene.addLight(sunLight);
    scene.addLight(pointLight);

    scene.setAmbient(Raytracer::Vec3(1, 1, 1), 0.0);

    std::cout << "Scene built successfully. Starting rendering..." << std::endl;

    Raytracer::Renderer renderer(800, 600, scene);
    renderer.render();

    std::cout << "Finished Rendering.";
}
