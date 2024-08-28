#include "SelectMode.h"
#include "../../../main.h"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Utility/UtilityKey.hxx"
#include "../../../Data/ResourceManager.h"
#include "Practice/Practice.hpp"
#include "Survival/Survival.hpp"
#include "TimeAttack/TimeAttack.hpp"
#include "TimeLimit/TimeLimit.hpp"

void SelectMode::Init()
{
	auto spTex(std::make_shared<KdTexture>());

	spTex = RESOURCE.IndexTexture("Texts/practiceMode.png");

#if _DEBUG
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
#endif // _DEBUG

	AddModeObjList<Practice>(m_wpPractic, spTex);

	spTex = RESOURCE.IndexTexture("Texts/survivalMode.png");

#if _DEBUG
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
#endif // _DEBUG

	AddModeObjList<Survival>(m_wpSurvival, spTex);

	spTex = RESOURCE.IndexTexture("Texts/timeAttackMode.png");

#if _DEBUG
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
#endif // _DEBUG

	AddModeObjList<TimeAttack>(m_wpTimeAttack, spTex);

	spTex = RESOURCE.IndexTexture("Texts/timeLimitMode.png");

#if _DEBUG
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
#endif // _DEBUG

	AddModeObjList<TimeLimit>(m_wpTimeLimit, spTex);
}

void SelectMode::DrawSprite()
{
	m_spModeObjVector[m_focusSelectMode]->DrawSprite();
}

void SelectMode::Update()
{
	auto nowWheelVal(Application::Instance().GetMouseWheelValue());

	if (nowWheelVal > Def::IntNull)
	{
		nowWheelVal = Def::IntNull;

		KdAudioManager::Instance().Play("Asset/Sounds/Select/modeChange.wav");

		++m_focusSelectMode;
		if (m_focusSelectMode >= static_cast<int>(m_spModeObjVector.size())) m_focusSelectMode = Def::IntNull;
	}
	else if (nowWheelVal < Def::IntNull)
	{
		nowWheelVal = Def::IntNull;

		KdAudioManager::Instance().Play("Asset/Sounds/Select/modeChange.wav");

		--m_focusSelectMode;
		if (m_focusSelectMode < Def::IntNull) m_focusSelectMode = static_cast<int>(m_spModeObjVector.size() - Def::SizTOne);
	}

	if (Key::IsPushing(Key::W))
	{
		if (!Key::_isPush)
		{
			Key::_isPush = true;

			KdAudioManager::Instance().Play("Asset/Sounds/Select/modeChange.wav");

			++m_focusSelectMode;
			if (m_focusSelectMode >= static_cast<int>(m_spModeObjVector.size())) m_focusSelectMode = Def::IntNull;
		}
	}
	else Key::_isPush = false;
}

size_t const SelectMode::GetMode() const noexcept
{
	if (m_wpPractic.expired() || m_wpSurvival.expired() || m_wpTimeAttack.expired() || m_wpTimeLimit.expired()) return static_cast<size_t>(GameMode::None);

	if      (m_spModeObjVector[m_focusSelectMode] == m_wpPractic.lock())    return static_cast<size_t>(GameMode::Practice);
	else if (m_spModeObjVector[m_focusSelectMode] == m_wpSurvival.lock())   return static_cast<size_t>(GameMode::Survival);
	else if (m_spModeObjVector[m_focusSelectMode] == m_wpTimeAttack.lock()) return static_cast<size_t>(GameMode::TimeAttack);
	else if (m_spModeObjVector[m_focusSelectMode] == m_wpTimeLimit.lock())  return static_cast<size_t>(GameMode::TimeLimit);

	return static_cast<size_t>(GameMode::None);
}
