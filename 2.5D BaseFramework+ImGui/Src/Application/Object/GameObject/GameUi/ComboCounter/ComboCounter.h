#pragma once
#include "../BaseGameUi.hpp"

class Counter;

class ComboCounter: public BaseGameUi
{
public:
	explicit ComboCounter (const std::shared_ptr<KdTexture>& spTex) noexcept;
	ComboCounter ()noexcept = default;
	~ComboCounter()noexcept = default;

	void DrawSprite() noexcept override;
	void Update() override;

	auto const GetMaxCombo() const noexcept { return m_maxComboNum; }
	auto const IsComboOver() const noexcept { return m_isComboOver; }

	void SetNowComboNum(const size_t& comboNum) noexcept { m_nowComboNum = comboNum; }

private:

	enum class Digit : size_t
	{
		Ones,
		Tens,
		Hundreds,
		Maximize
	};

	void Init() override;

	std::array<Math::Rectangle, static_cast<size_t>(Digit::Maximize)> m_rect;
	std::shared_ptr<Counter> m_spCounter;

	Math::Color m_color;

	size_t m_nowComboNum;
	size_t m_maxComboNum;
	size_t m_limitComboNum;

	size_t m_firstBorder;
	size_t m_secondBorder;
	size_t m_thirdBorder;

	float m_changeColorVal;
};