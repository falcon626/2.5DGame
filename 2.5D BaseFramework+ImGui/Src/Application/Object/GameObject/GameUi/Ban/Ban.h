#pragma once
#include "../BaseGameUi.hpp"

class Ban: public BaseGameUi
{
public:
	Ban (const std::shared_ptr<KdTexture>& spTex) noexcept;
	~Ban() noexcept override = default;
private:
};