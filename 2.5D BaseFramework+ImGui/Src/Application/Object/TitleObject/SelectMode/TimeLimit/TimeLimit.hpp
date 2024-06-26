#pragma once
#include "../BaseSelectMode.hpp"

class TimeLimit : public BaseSelectMode
{
public:
	explicit  TimeLimit (const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }
	~TimeLimit()noexcept override = default;
private:
};