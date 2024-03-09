//
// Created by flif3 on 3/10/2024.
//

#pragma once

#include "AABB.h"
#include <vector>
#include <algorithm>

namespace Raytracer {

    class BVH {
    public:
        BVH* left; // left child
        BVH* right; // right child
        AABB box; // bounding box
        std::vector<AABB> objects; // objects in the BVH

        BVH() : left(nullptr), right(nullptr) { }

        // Constructor for a single AABB object
        BVH(AABB object) : box(object), left(nullptr), right(nullptr) {
            objects.push_back(object);
        }

        // Constructor for a vector of AABB objects
        BVH(std::vector<AABB> objects) : objects(objects) {
            build();
        }

        void insert(const AABB& object) {
            objects.push_back(object);
            build();
        }

        bool intersect(const Ray& ray) const {
            if (!box.intersects(ray)) {
                return false;
            }
            for (const auto& object : objects) {
                if (object.intersects(ray)) {
                    return true;
                }
            }
            return false;
        }

        void build() {
            int n = objects.size();
            int axis = rand() % 3;
            switch (axis) {
                case 0:
                    std::sort(objects.begin(), objects.end(), [](AABB a, AABB b) { return a.min.x < b.min.x; });
                    break;
                case 1:
                    std::sort(objects.begin(), objects.end(), [](AABB a, AABB b) { return a.min.y < b.min.y; });
                    break;
                case 2:
                    std::sort(objects.begin(), objects.end(), [](AABB a, AABB b) { return a.min.z < b.min.z; });
                    break;
            }

            if (n == 1) {
                left = right = new BVH(objects[0]);
            } else if (n == 2) {
                left = new BVH(objects[0]);
                right = new BVH(objects[1]);
            } else {
                std::vector<AABB> left_objects(objects.begin(), objects.begin() + n/2);
                std::vector<AABB> right_objects(objects.begin() + n/2, objects.end());
                left = new BVH(left_objects);
                right = new BVH(right_objects);
            }

            box = surrounding_box(left->box, right->box);

            std::cout << "Building BVH with " << n << " objects" << std::endl;
        }

        static AABB surrounding_box(const AABB& box0, const AABB& box1);
    };

} // Raytracer
