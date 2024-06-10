#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayProtrusion : public BaseExtensionObject
{
public:
	GrayProtrusion ()noexcept { Init(); }
	~GrayProtrusion()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/Rock_04.gltf"); };
};