#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayTowering : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	GrayTowering ()noexcept { SetModelData("Rock/Rock_03.gltf"); }
	~GrayTowering()noexcept override = default;
private:
};