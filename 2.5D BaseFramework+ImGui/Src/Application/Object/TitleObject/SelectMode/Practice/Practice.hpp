#pragma once
#include "../BaseSelectMode.hpp"

class Practice : public BaseSelectMode
{
public:
	Practice (const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }
	~Practice()noexcept override = default;
private:
};