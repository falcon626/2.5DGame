#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayFlat : public BaseExtensionObject
{
public:
	GrayFlat ()noexcept { Init(); }
	~GrayFlat()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/Rock_05.gltf"); };
};