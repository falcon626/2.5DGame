#pragma once
#include "../BasePickaxe.h"

class IronPickaxe : public BasePickaxe
{
public:
	IronPickaxe() {}
	~IronPickaxe() override {}

	void Init() override;
	void Use() override;
private:
};