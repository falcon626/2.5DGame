#pragma once
#include "../BaseGameUi.hpp"

class Gauge : public BaseGameUi
{
public:
	explicit Gauge (const std::shared_ptr<KdTexture>& spTex) noexcept;
	Gauge () noexcept = default;
	~Gauge() noexcept override = default;

	void DrawSprite() noexcept override;
	void Update()              override;
	void PostUpdate()          override;

	void MisTake() noexcept { ++m_mistakeCount; }

	inline auto const IsTired() const { return m_isTired; }

private:
	void Init() override;

	Math::Vector2 m_goalPos;

	Math::Rectangle m_rect;
	
	int    m_rectY;
	size_t m_mistakeCount;
	size_t m_maxMistake;
	float  m_speed;
	bool   m_isTired;
};