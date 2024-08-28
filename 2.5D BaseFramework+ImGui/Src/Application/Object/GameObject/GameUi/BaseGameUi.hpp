#pragma once

class BaseGameUi : public KdGameObject
{
public:
	BaseGameUi()noexcept 
		: m_isModePractice  (false)
		, m_isModeSurvival  (false)
		, m_isModeTimeAttack(false)
		, m_isModeTimeLimit (false)
		, m_isTired         (false)
		, m_isLimitOver     (false)
		, m_isComboOver     (false)
	{};
	virtual ~BaseGameUi()noexcept override = default;

	virtual void DrawSprite() noexcept override 
	{ KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spTex, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y)); }

	inline auto SetTex(const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; }

	inline auto SetPractice()   noexcept { m_isModePractice   = true; } // Why Not Bit
	inline auto SetSurvival()   noexcept { m_isModeSurvival   = true; } // Expansion Possibilities
	inline auto SetTimeAttack() noexcept { m_isModeTimeAttack = true; } // More Efficiently
	inline auto SetTimeLimit()  noexcept { m_isModeTimeLimit  = true; } // Growth Potential

	inline auto SetIsTired(const bool& isTired) noexcept { m_isTired     = isTired; }
	inline auto SetIsLimit(const bool& isLimit) noexcept { m_isLimitOver = isLimit; }
	inline auto SetIsCombo(const bool& isCombo) noexcept { m_isComboOver = isCombo; }

	// Ius Vitae Necisque
	auto KillExistence() noexcept { m_isExpired = true; }

protected:
	std::shared_ptr<KdTexture> m_spTex;
	Math::Vector2              m_pos;

	bool m_isModePractice;
	bool m_isModeSurvival;
	bool m_isModeTimeAttack;
	bool m_isModeTimeLimit;

	bool m_isTired;
	bool m_isLimitOver;
	bool m_isComboOver;
private:
};