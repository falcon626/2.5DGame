#pragma once
#include "../BasePickaxe.h"

class IronPickaxe : public BasePickaxe
{
public:
	IronPickaxe () noexcept = default;
	~IronPickaxe() noexcept override = default;

	void Init() override;
private:
};