//
// Created by flif3 on 8/1/2023.
//

#include "Object.h"

namespace Raytracer {
    std::shared_ptr<Material> Object::getMaterial() const {
        return material;
    }
} // Raytracer