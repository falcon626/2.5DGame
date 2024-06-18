#pragma once

class Coin : public KdGameObject 
{
public:
	Coin () noexcept = default;
	~Coin() noexcept override = default;

	void Init()override;
	void SetTex(const std::shared_ptr<KdTexture>& spTex) { m_spTex = spTex; }
	void DrawSprite()override;
	void Update()override;
private:
	std::shared_ptr<KdTexture> m_spTex;
	Math::Vector2 m_pos;
};