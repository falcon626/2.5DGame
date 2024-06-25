#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Rock : public BaseExtensionObject
{
public:
	Rock ()noexcept { Init(); }
	~Rock()noexcept override = default;
private:
	void Init()override;
};