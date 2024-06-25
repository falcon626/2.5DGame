#pragma once
#include "../BaseSelectMode.hpp"

class Survival : public  BaseSelectMode
{
public:
	Survival (const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }
	~Survival()noexcept override = default;
private:
};