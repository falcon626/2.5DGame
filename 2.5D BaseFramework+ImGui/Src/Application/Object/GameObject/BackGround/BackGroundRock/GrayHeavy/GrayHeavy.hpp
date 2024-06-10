#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class GrayHeavy : public BaseExtensionObject
{
public:
	GrayHeavy ()noexcept { Init(); }
	~GrayHeavy()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/Rock_01.gltf"); };
};