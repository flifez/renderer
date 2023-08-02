cmake_minimum_required(VERSION 3.25)
project(renderer)

set(CMAKE_CXX_STANDARD 20)

add_executable(renderer main.cpp CodeHelper/Vec3.h Ray/Ray.h CodeHelper/mathutil.h Cameras/BasicCamera.cpp Cameras/BasicCamera.h Ray/Ray.cpp Materials/MaterialVariants/DiffuseMaterial.cpp Materials/MaterialVariants/DiffuseMaterial.h Scene/Scene.cpp Scene/Scene.h Lights/LightVariants/PointLight.cpp Lights/LightVariants/PointLight.h Objects/ObjectVariants/Sphere.cpp Objects/ObjectVariants/Sphere.h Materials/Material.h Lights/Light.h Objects/Object.cpp Objects/Object.h Renderer/Renderer.cpp Renderer/Renderer.h Lights/Light.cpp CodeHelper/Vec3.cpp CodeHelper/mathutil.cpp Materials/MaterialVariants/BlingPhongMaterial.cpp Materials/MaterialVariants/BlingPhongMaterial.h)
