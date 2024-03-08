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

    Raytracer::DiffuseMaterial diffuseMaterial(Raytracer::Vec3(0.3, 0.8, 0.3), 0.5);

    Raytracer::Mesh mesh = Raytracer::ObjFileParser::parse("../Resources/bunny-lowpoly.obj", &diffuseMaterial);
    mesh.scale(1);
    mesh.rotate(Raytracer::Vec3(M_PI, 0.9 * M_PI, -M_PI/2.2));

    std::vector<Raytracer::Triangle> triangles;
    triangles.emplace_back(Raytracer::Vec3(0, -0.5773, 1),
                       Raytracer::Vec3(0.5, 0.2887, 1),
                      Raytracer::Vec3(-0.5, 0.2887, 1));
    std::shared_ptr<Raytracer::Mesh> mesh1 = std::make_shared<Raytracer::Mesh>(triangles, &diffuseMaterial);

    std::shared_ptr<Raytracer::Mesh> bunny = std::make_shared<Raytracer::Mesh>(mesh);

    std::shared_ptr<Raytracer::SunLight> sunLight =
            std::make_shared<Raytracer::SunLight>(Raytracer::Vec3(0, 0, 1), Raytracer::Vec3(1, 1, 1), 1);

    Raytracer::Vec3 position(-375, -40, -400);
    Raytracer::Vec3 orientation(1, 0, 1);
    float fov = 18.0f;

    Raytracer::BasicCamera camera(position, orientation, fov, 0.75f);

    Raytracer::Scene scene(camera);
    scene.addObject(bunny);
    scene.addLight(sunLight);

    scene.setAmbient(Raytracer::Vec3(1, 1, 1), 0.8);

    std::cout << "Scene built successfully. Starting rendering..." << std::endl;

    Raytracer::Renderer renderer(1200, 900, scene);
    renderer.render();

    std::cout << "Finished Rendering.";
}
