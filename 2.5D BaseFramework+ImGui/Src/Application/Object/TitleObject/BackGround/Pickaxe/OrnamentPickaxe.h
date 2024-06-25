#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class OrnamentPickaxe : public BaseExtensionObject
{
public:
	OrnamentPickaxe ()noexcept { Init(); }
	~OrnamentPickaxe()noexcept override = default;
private:
	void Init()override;
};