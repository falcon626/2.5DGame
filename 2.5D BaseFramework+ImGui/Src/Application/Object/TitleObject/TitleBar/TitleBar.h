#pragma once

class TitleBar : public KdGameObject
{
public:
	TitleBar ()noexcept;
	~TitleBar()noexcept override = default;

	void DrawSprite() override;
	void Update() override;

private:
	void Init() override;

	std::shared_ptr<KdTexture> m_spTex;

	Math::Vector2 m_pos;

	float m_moveY;
	float m_moveYSpeed;
	float m_fullDegrees;
};