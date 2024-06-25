#pragma once
#include "SelectModeTag.hpp"

class Practice;
class Survival;
class TimeAttack;
class TimeLimit;

class SelectMode : public KdGameObject
{
public:

	enum class GameMode : size_t
	{
		None,
		Practice,
		Survival,
		TimeAttack,
		TimeLimit
	};

	SelectMode ()noexcept : m_focusSelectMode(NULL) { Init(); }
	~SelectMode()noexcept override = default;

	void DrawSprite() override;
	void Update() override;

	size_t const GetMode() const noexcept;
private:
	void Init()override;

	// Add ModeObjVector And Create WeakPtr
	template <class T, typename... Args>
	inline auto AddModeObjList(std::weak_ptr<T>& wpObj, Args&&... args) noexcept
	{
		static_assert(std::is_base_of<SelectModeTag, T>::value, "T Must Be Derived From SelectModeTag");
		auto spObj = std::make_shared<T>(std::forward<Args>(args)...);
		wpObj = spObj;
		m_spModeObjVector.push_back(spObj);
	}

	std::vector<std::shared_ptr<KdGameObject>> m_spModeObjVector;

	std::weak_ptr<Practice> m_wpPractic;
	std::weak_ptr<Survival> m_wpSurvival;
	std::weak_ptr<TimeAttack> m_wpTimeAttack;
	std::weak_ptr<TimeLimit> m_wpTimeLimit;

	int m_focusSelectMode;
};