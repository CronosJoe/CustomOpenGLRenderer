#pragma once
#include "glew/GL/glew.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL 1
#include "glm/gtx/quaternion.hpp"
#undef GLM_ENABLE_EXPERIMENTAL
#include <vector>
namespace aie{
    class transform
    {
    public:
        glm::vec3 localPos;
        glm::quat localRot;
        glm::vec3 localScl;

        transform();

        // get/set parent
        void setParent(transform* newParent);
        transform* getParent() const;

        // get children
        transform* getChildAtIndex(size_t index) const;
        size_t getChildCount() const;

        //get/set the world positioon - analagons to transform.position
        glm::vec3 getPosition() const;
        void setPosition(glm::vec3 position);

        // get local model matrix
        glm::mat4 localMat() const;
        // get global model matrix
        glm::mat4 worldMat() const;

        // matrix used for converting transforming local-space coordinates to world-space
        glm::mat4 localToWorldMatrix() const;
        // matrix used for converting transforming world-space coordinates to local-space
        glm::mat4 worldToLocalMatrix() const;

    private:
        transform* parent;
        std::vector<transform*> children;

        void addChild(transform* const child);

        void removeChild(const transform const *child);
        
    };
}
