#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class YellowBumpy : public BaseExtensionObject
{
public:
	YellowBumpy ()noexcept { Init(); }
	~YellowBumpy()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/ImageToStl.com_rocks_02.gltf"); };
};