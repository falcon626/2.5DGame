#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayProtrusion : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	GrayProtrusion ()noexcept { SetModelData("Rock/Rock_04.gltf"); }
	~GrayProtrusion()noexcept override = default;
private:
};