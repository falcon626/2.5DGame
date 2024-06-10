#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GraySlanted : public BaseExtensionObject
{
public:
	GraySlanted ()noexcept { Init(); }
	~GraySlanted()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/Rock_02.gltf"); };
};