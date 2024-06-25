#pragma once
#include "../BackGroundRockObjectTag.hpp"
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class BlueCrystal : public BaseExtensionObject, BackGroundRockObjectTag
{
public:
	BlueCrystal ()noexcept { SetModelData("Crystal/biggestblue/crystalexport.gltf"); }
	~BlueCrystal()noexcept override = default;
private:
};