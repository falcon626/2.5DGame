#pragma once
#include "BaseGameUi.hpp"

class StageTime;
class Gauge;
class ComboCounter;
class ScoreCounter;
class Character;
class Ban;

class GameUi : public BaseGameUi
{
public:
	GameUi ()noexcept;
	~GameUi()noexcept override = default;

	void DrawSprite() noexcept override;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;

	bool const IsTired()     const noexcept;
	bool const IsLimitOver() const noexcept;
	bool const IsComboOver() const noexcept;

	void SetNowComboNum(const size_t& comboNum) noexcept;

	void SetModePractice()   noexcept;
	void SetModeSurvival()   noexcept;
	void SetModeTimeAttack() noexcept;
	void SetModeTimeLimit()  noexcept;

	int GetMaxCombo() noexcept;
	int GetTime    () noexcept;
	int GetScore   () noexcept;

	void CrystalBroken() noexcept;
	void TreasureCollected() noexcept;

	void Mistake() noexcept;

private:
	void Init()override;

	template <class T, typename... Args>
	inline auto AddUiObjList(Args&&... args)
	{
		static_assert(std::is_base_of<BaseGameUi, T>::value, "T Must Be Derived From BaseGameUi");
		m_spUiObj.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	template <class _T, typename... _Args>
	inline auto AddUiObjList(std::weak_ptr<_T>& wpUiObj , _Args&&... args)
	{
		static_assert(std::is_base_of<BaseGameUi, _T>::value, "_T Must Be Derived From BaseGameUi");
		auto uiObj = std::make_shared<_T>(std::forward<_Args>(args)...);
		wpUiObj = uiObj;
		m_spUiObj.push_back(uiObj);
	}

	std::list<std::shared_ptr<BaseGameUi>> m_spUiObj;

	std::weak_ptr<StageTime>    m_wpStageTime;
	std::weak_ptr<Gauge>        m_wpGauge;
	std::weak_ptr<ComboCounter> m_wpComboCounter;
	std::weak_ptr<ScoreCounter> m_wpScoreCounter;
	std::weak_ptr<Character>    m_wpCharacter;
	std::weak_ptr<Ban>          m_wpBan;

	bool m_isCharacterExpired;
};