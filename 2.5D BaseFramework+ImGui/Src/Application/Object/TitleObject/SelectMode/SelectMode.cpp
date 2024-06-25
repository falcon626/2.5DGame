#include "SelectMode.h"
#include "../../../main.h"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Data/ResourceManager.h"
#include "Practice/Practice.hpp"
#include "Survival/Survival.hpp"
#include "TimeAttack/TimeAttack.hpp"
#include "TimeLimit/TimeLimit.hpp"

void SelectMode::Init()
{

	auto spTex(std::make_shared<KdTexture>());

	spTex = RESOURCE.IndexTexture("Texts/practiceMode.png");
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddModeObjList<Practice>(m_wpPractic, spTex);

	spTex = RESOURCE.IndexTexture("Texts/survivalMode.png");
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddModeObjList<Survival>(m_wpSurvival, spTex);

	spTex = RESOURCE.IndexTexture("Texts/timeAttackMode.png");
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddModeObjList<TimeAttack>(m_wpTimeAttack, spTex);

	spTex = RESOURCE.IndexTexture("Texts/timeLimitMode.png");
	if (!spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
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
}

size_t const SelectMode::GetMode() const noexcept
{
	if (m_wpPractic.expired() || m_wpSurvival.expired() || m_wpTimeAttack.expired() || m_wpTimeLimit.expired()) return static_cast<size_t>(GameMode::None);

	if (m_spModeObjVector[m_focusSelectMode] == m_wpPractic.lock())    return static_cast<size_t>(GameMode::Practice);
	if (m_spModeObjVector[m_focusSelectMode] == m_wpSurvival.lock())   return static_cast<size_t>(GameMode::Survival);
	if (m_spModeObjVector[m_focusSelectMode] == m_wpTimeAttack.lock()) return static_cast<size_t>(GameMode::TimeAttack);
	if (m_spModeObjVector[m_focusSelectMode] == m_wpTimeLimit.lock())  return static_cast<size_t>(GameMode::TimeLimit);

	return static_cast<size_t>(GameMode::None);
}
