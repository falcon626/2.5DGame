#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayFlat : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	GrayFlat ()noexcept { SetModelData("Rock/Rock_05.gltf"); }
	~GrayFlat()noexcept override = default;
private:
};