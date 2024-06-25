#pragma once
#include "../BaseGameUi.hpp"

class Counter;
class Timer;

class StageTime : public BaseGameUi
{
public:
	StageTime (const std::shared_ptr<KdTexture>& spTex) noexcept;
	StageTime () noexcept = default;
	~StageTime() noexcept override = default;

	void DrawSprite() noexcept override;
	void Update() override;

	auto const GetTime()     const noexcept { return m_time; }
	auto const IsLimitOver() const noexcept { return m_isModeTimeLimit ? m_isLimitOver : false; }

private:


	void Init() override;

	std::shared_ptr<Counter> m_spCounter;
	std::shared_ptr<Timer>   m_spTimer;

	Math::Vector2 m_tiredEndGoalPos;
	Math::Vector2 m_goalPos;
	 
	int   m_limitTime;
	int   m_time;
	float m_speed;
	bool  m_isLimitOver;
};