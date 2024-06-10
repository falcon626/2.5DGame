#pragma once
#include "../../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class YellowSmooth : public BaseExtensionObject
{
public:
	YellowSmooth ()noexcept { Init(); }
	~YellowSmooth()noexcept override = default;
private:
	inline void Init()override { SetModelData("Rock/ImageToStl.com_rock_01.gltf"); };
};