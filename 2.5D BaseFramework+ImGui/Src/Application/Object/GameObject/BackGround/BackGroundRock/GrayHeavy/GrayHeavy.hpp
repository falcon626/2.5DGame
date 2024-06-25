#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayHeavy : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	GrayHeavy ()noexcept { SetModelData("Rock/Rock_01.gltf"); }
	~GrayHeavy()noexcept override = default;
private:
};