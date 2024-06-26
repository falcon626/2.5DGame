#pragma once
#include "../BaseSelectMode.hpp"

class Survival : public  BaseSelectMode
{
public:
	explicit  Survival (const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }
	~Survival()noexcept override = default;
private:
};