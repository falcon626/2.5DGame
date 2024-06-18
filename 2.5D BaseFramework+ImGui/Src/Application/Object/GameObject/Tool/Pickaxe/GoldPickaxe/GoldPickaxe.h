#pragma once
#include "../BasePickaxe.h"

class GoldPickaxe : public BasePickaxe
{
public:
	GoldPickaxe () noexcept = default;
	~GoldPickaxe() noexcept override = default;

	void Init() override;
private:
};