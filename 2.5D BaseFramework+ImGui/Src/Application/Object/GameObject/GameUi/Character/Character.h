#pragma once
#include "../BaseGameUi.hpp"

class Character : public BaseGameUi
{
public:
	explicit Character(const std::shared_ptr<KdTexture>& spCombo, const std::shared_ptr<KdTexture>& spTime, const std::shared_ptr<KdTexture>& spTension, const std::shared_ptr<KdTexture>& spMiddleClick)noexcept;
	~Character()noexcept override = default;

	void DrawSprite() noexcept override;

private:
	void Init()override;
	
	std::shared_ptr<KdTexture> m_spComboTex;
	std::shared_ptr<KdTexture> m_spTimeTex;
	std::shared_ptr<KdTexture> m_spTensionTex;
	std::shared_ptr<KdTexture> m_spMiddleClickTex;

	Math::Vector2 m_comboPos;
	Math::Vector2 m_timePos;
	Math::Vector2 m_tensionPos;
	Math::Vector2 m_middleClickPos;
};