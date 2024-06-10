#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayTowering : public BaseExtensionObject
{
public:
	GrayTowering ()noexcept { Init(); }
	~GrayTowering()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/Rock_03.gltf"); };
};