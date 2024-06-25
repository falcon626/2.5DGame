#pragma once
#include "../BaseSelectMode.hpp"

class TimeAttack : public BaseSelectMode
{
public:
	TimeAttack (const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }
	~TimeAttack()noexcept override = default;
private:
};