#pragma once

class TitleHelp : public KdGameObject
{
public:
	TitleHelp ()noexcept;
	~TitleHelp()noexcept override = default;
	
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