#pragma once

class Player;

class GameUi : public KdGameObject
{
public:
	GameUi ()noexcept { Init(); }
	~GameUi()noexcept override = default;

	void DrawSprite()override;
	void Update()override;

	void SetTexture();
	void SetPlayerWeakPtr(const std::shared_ptr<Player>& spPlayer) noexcept { m_wpPlayer = spPlayer; }

private:
	void Init()override;

	std::weak_ptr<Player> m_wpPlayer;
	std::shared_ptr<KdTexture> m_spCoinTex;
};