#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GraySlanted : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	GraySlanted ()noexcept { SetModelData("Rock/Rock_02.gltf"); }
	~GraySlanted()noexcept override = default;
private:
};