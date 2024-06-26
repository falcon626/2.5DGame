#pragma once
#include "../BaseGameUi.hpp"

class Counter;

class ScoreCounter : public BaseGameUi
{
public:
	explicit ScoreCounter (const std::shared_ptr<KdTexture>& spTex, const std::shared_ptr<KdTexture> spCrystalTex, const std::shared_ptr<KdTexture> spTreasureTex) noexcept;
	ScoreCounter () noexcept = default;
	~ScoreCounter() noexcept override = default;

	void DrawSprite() noexcept override;
	void Update() override;

	auto const GetTotalScore() const noexcept { return m_crystalBrokenNum + m_treasureCollectedNum; }

	void CrystalBrokenCount    () noexcept { ++m_crystalBrokenNum; }
	void TreasureCollectedCount() noexcept { ++m_treasureCollectedNum; }
private:
	void Init() override;

	std::shared_ptr<Counter>   m_spCrystalCounter;
	std::shared_ptr<Counter>   m_spTreasureCounter;

	std::shared_ptr<KdTexture> m_spCrystalTex;
	std::shared_ptr<KdTexture> m_spTreasureTex;

	Math::Vector2 m_crystalPos;
	Math::Vector2 m_crystalCounterPos;
	Math::Vector2 m_treasurePos;
	Math::Vector2 m_treasureCounterPos;

	Math::Vector2 m_goalPos;

	int   m_crystalBrokenNum;
	int   m_treasureCollectedNum;
	float m_speed;
};