//
// Created by flif3 on 8/7/2023.
//

#pragma once

#include "Mesh.h"

namespace Raytracer {
    // Parse an .obj file. Returns a Mesh object. Note: Mesh implementation is triangle list.
    class ObjFileParser {
    public:
        ObjFileParser() = default;
        static Mesh parse(const std::string& filename, Material *material);
    };

} // Raytracer