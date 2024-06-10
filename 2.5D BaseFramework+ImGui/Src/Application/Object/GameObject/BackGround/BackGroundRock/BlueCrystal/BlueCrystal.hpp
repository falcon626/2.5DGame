#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class BlueCrystal : public BaseExtensionObject
{
public:
	BlueCrystal ()noexcept { Init(); }
	~BlueCrystal()noexcept override = default;
private:
	inline void Init()override { SetModelData("Crystal/biggestblue/crystalexport.gltf"); };
};