//
// Created by flif3 on 8/7/2023.
//

#include <fstream>
#include <sstream>
#include <utility>
#include <cstring>
#include "ObjFileParser.h"

namespace Raytracer {
    Mesh ObjFileParser::parse(const std::string& filename, Material* material) {
        std::vector<Vec3> vertices;
        std::vector<Triangle> triangles;

        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        while (getline(file, line)) {
            std::istringstream lineStream(line);
            std::string lineType;
            lineStream >> lineType;

            if (lineType == "v") {
                Vec3 vertex;
                lineStream >> vertex.x >> vertex.y >> vertex.z;

                // std::cout << "Vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;

                vertices.push_back(vertex);
            } else if (lineType == "f") {
                std::string vertexToken;
                int vertexIndices[3];
                for (int & vertexIndex : vertexIndices) {
                    lineStream >> vertexToken;
                    size_t doubleSlashPos = vertexToken.find("//");
                    if (doubleSlashPos != std::string::npos) {
                        // Extract the vertex index from before the "//"
                        vertexIndex = std::stoi(vertexToken.substr(0, doubleSlashPos)) - 1;
                    }
                }
                Triangle triangle = {vertices[vertexIndices[0]], vertices[vertexIndices[1]], vertices[vertexIndices[2]]};
                triangles.push_back(triangle);
            }
        }

        // Create and return a Mesh object populated with the parsed triangles
        return {triangles, (Material *) material};
    }
} // Raytracer