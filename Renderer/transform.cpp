#include "transform.h"
namespace aie
{
	transform::transform()
	{
		//default initializing them all to 0 for an object in the center with no rotation and no scale
		localPos = glm::vec3(0,0,0);
		localRot = glm::quat(0, 0, 0, 0);
		localScl = glm::vec3(1, 1, 1);

		parent = NULL;
		children.clear(); // there should be nothing in there but this is to double check
	}
	void aie::transform::setParent(transform* newParent)
	{
		if (parent != nullptr) {
			parent->removeChild(this);
			parent = nullptr;
		}
		newParent->removeChild(this);
		parent = newParent;
	}

	transform* transform::getParent() const
	{
		return parent;
	}
	transform* transform::getChildAtIndex(size_t index) const
	{
		return children[index];
	}
	size_t transform::getChildCount() const
	{
		return children.size();
	}
	glm::vec3 transform::getPosition() const
	{
		return localToWorldMatrix() * glm::vec4(localPos,0);
	}
	void transform::setPosition(glm::vec3 position)
	{
		localPos = worldToLocalMatrix() * glm::vec4(position, 0);
	}
	glm::mat4 transform::localMat() const
	{
		glm::mat4 translate = glm::translate(glm::identity<glm::mat4>(), localPos);
		glm::mat4 rotation = glm::toMat4(localRot);
		glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), localScl);

		glm::mat4 trs = glm::translate(glm::identity<glm::mat4>(), localPos);
		trs *= glm::toMat4(localRot);
		trs = glm::scale(trs, localScl);

		return translate * rotation * scale;
	}
	glm::mat4 transform::worldMat() const
	{
		if(parent==nullptr)//expected case
		{
			return localMat();
		}else
		{
			return parent->worldMat() * localMat();
		}
	}
	glm::mat4 transform::localToWorldMatrix() const
	{
		if(parent!=nullptr)
		{
			return glm::identity<glm::mat4>();
		}
		else
		{
			return parent->worldMat();
		}
	}
	glm::mat4 transform::worldToLocalMatrix() const
	{
		return glm::inverse(localToWorldMatrix());
	}
	void transform::addChild(transform* const child)
	{
		children.push_back(child);
    }
	void transform::removeChild(const transform const* child)
	{
		for(size_t i = 0; i <children.size();i++)
		{
			if(children[i] == child)
			{
				children.erase(children.begin() + i);
				break;
			}
		}
	}
}