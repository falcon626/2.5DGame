#include "GameUi.h"
#include "../../../Utility/UtilityKey.hxx"
#include "../../../Data/ResourceManager.h"
#include "StageTime/StageTime.h"
#include "Gauge/Gauge.h"
#include "ComboCounter/ComboCounter.h"
#include "ScoreCounter/ScoreCounter.h"
#include "Character/Character.h"
#include "Ban/Ban.h"

GameUi::GameUi() noexcept
	: m_isCharacterExpired(false)
{ Init(); }

void GameUi::Init()
{
	m_spTex = RESOURCE.IndexTexture("Numbers/numbersBox.png");
	if (!m_spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddUiObjList<StageTime>(m_wpStageTime, m_spTex);

	m_spTex = RESOURCE.IndexTexture("Gauge/gauge.png");
	if (!m_spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddUiObjList<Gauge>(m_wpGauge, m_spTex);

	m_spTex = RESOURCE.IndexTexture("Numbers/numbers.png");
	if (!m_spTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddUiObjList<ComboCounter>(m_wpComboCounter, m_spTex);

	auto spCrystalTex (RESOURCE.IndexTexture("Crystal/crystal.png"));
	if (!spCrystalTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	auto spTreasureTex(RESOURCE.IndexTexture("Treasure/treasure_bronze.png"));
	if (!spTreasureTex) _ASSERT_EXPR(false, L"TextureData Not Found");
	AddUiObjList<ScoreCounter>(m_wpScoreCounter, m_spTex, spCrystalTex, spTreasureTex);
}

void GameUi::DrawSprite() noexcept
{
	for (decltype(auto) obj : m_spUiObj)
		obj->DrawSprite();
}

void GameUi::PreUpdate()
{
	auto it = m_spUiObj.begin();

	while (it != m_spUiObj.end())
	{
		if ((*it)->IsExpired()) it = m_spUiObj.erase(it);
		else ++it;
	}

	for (auto& obj : m_spUiObj)
		obj->PreUpdate();
}

void GameUi::Update()
{
	for (decltype(auto) obj : m_spUiObj)
		obj->Update();

	if (Key::IsPushing(Key::Tab) || Key::IsPushing(Key::SideR_Click))
	{
		if (!Key::_isPush)
		{
			Key::_isPush = true;
			if (!m_isCharacterExpired)
			{
				m_isCharacterExpired = true;
				auto spComboTex(RESOURCE.IndexTexture("Texts/combo.png"));
				if (!spComboTex) _ASSERT_EXPR(false, L"TextureData Not Found");

				auto spTimeTex(RESOURCE.IndexTexture("Texts/time.png"));
				if (!spTimeTex) _ASSERT_EXPR(false, L"TextureData Not Found");

				auto spTensionTex(RESOURCE.IndexTexture("Texts/tension.png"));
				if (!spTensionTex) _ASSERT_EXPR(false, L"TextureData Not Found");

				auto spMiddleClickTex(RESOURCE.IndexTexture("Texts/middleClick.png"));
				if (!spMiddleClickTex) _ASSERT_EXPR(false, L"TextureData Not Found");

				AddUiObjList<Character>(m_wpCharacter, spComboTex, spTimeTex, spTensionTex, spMiddleClickTex);
			}
			else if (!m_wpCharacter.expired())
			{
				m_isCharacterExpired = false;
				m_wpCharacter.lock() ->KillExistence();
			}
		}
	}
	else Key::_isPush = false;
}

void GameUi::PostUpdate()
{
	if(m_wpGauge.expired() && !m_wpCharacter.expired()) m_wpCharacter.lock()->KillExistence();

	if (!m_wpGauge.expired() && !m_wpStageTime.expired() && !m_wpScoreCounter.expired() && !m_wpComboCounter.expired())
	{
		auto isTired(m_wpGauge.lock()->IsTired());

		m_wpStageTime.lock()   ->SetIsTired(isTired);
		m_wpScoreCounter.lock()->SetIsTired(isTired);
		m_wpComboCounter.lock()->SetIsTired(isTired);

	if(!m_wpCharacter.expired() && isTired) m_wpCharacter.lock()->KillExistence();
	}

	if (m_isModeTimeLimit)
	{
		if (!m_wpGauge.expired() && !m_wpStageTime.expired() && !m_wpScoreCounter.expired() && !m_wpComboCounter.expired())
		{
			auto isLimitOver(m_wpStageTime.lock()->IsLimitOver());

			m_wpGauge.lock()       ->SetIsLimit(isLimitOver);
			m_wpScoreCounter.lock()->SetIsLimit(isLimitOver);
			m_wpComboCounter.lock()->SetIsLimit(isLimitOver);

			if (!m_wpCharacter.expired() && isLimitOver) m_wpCharacter.lock()->KillExistence();
		}
	}

	if (m_isModeTimeAttack)
	{
		if (!m_wpGauge.expired() && !m_wpStageTime.expired() && !m_wpScoreCounter.expired() && !m_wpComboCounter.expired())
		{
			auto isComboOver(m_wpComboCounter.lock()->IsComboOver());

			m_wpStageTime.lock()   ->SetIsCombo(isComboOver);
			m_wpGauge.lock()       ->SetIsCombo(isComboOver);
			m_wpScoreCounter.lock()->SetIsCombo(isComboOver);
			m_wpComboCounter.lock()->SetIsCombo(isComboOver);

			if (!m_wpCharacter.expired() && isComboOver) m_wpCharacter.lock()->KillExistence();
		}
	}

	for (decltype(auto) obj : m_spUiObj)
		obj->PostUpdate();
}

bool const GameUi::IsTired() const noexcept
{
	if (m_wpGauge.expired())return true;
	auto gauge(m_wpGauge.lock());
	return gauge->IsTired();
}

bool const GameUi::IsLimitOver() const noexcept
{
	if (m_wpStageTime.expired())return true;
	auto limit(m_wpStageTime.lock());
	return limit->IsLimitOver();
}

bool const GameUi::IsComboOver() const noexcept
{
	if (m_wpComboCounter.expired())return true;
	auto combo(m_wpComboCounter.lock());
	return combo->IsComboOver();
}

void GameUi::SetNowComboNum(const size_t& comboNum) noexcept
{
	if (m_wpComboCounter.expired())return;
	auto comboCounter(m_wpComboCounter.lock());
	comboCounter->SetNowComboNum(comboNum);

	if (!m_wpBan.expired() && !comboNum) m_wpBan.lock()->KillExistence();
}

void GameUi::SetModePractice() noexcept
{
	if (m_wpGauge.expired() || m_wpStageTime.expired() ||
		m_wpComboCounter.expired() || m_wpScoreCounter.expired()) return;

	this                   ->SetPractice();

	m_wpComboCounter.lock()->SetPractice();
	m_wpGauge.lock()       ->SetPractice();
	m_wpScoreCounter.lock()->SetPractice();
	m_wpStageTime.lock()   ->SetPractice();
}

void GameUi::SetModeSurvival() noexcept
{
	if (m_wpGauge.expired() || m_wpStageTime.expired() ||
		m_wpComboCounter.expired() || m_wpScoreCounter.expired()) return;

	this                   ->SetSurvival();

	m_wpComboCounter.lock()->SetSurvival();
	m_wpGauge.lock()       ->SetSurvival();
	m_wpScoreCounter.lock()->SetSurvival();
	m_wpStageTime.lock()   ->SetSurvival();
}

void GameUi::SetModeTimeAttack() noexcept
{
	if (m_wpGauge.expired() || m_wpStageTime.expired() ||
		m_wpComboCounter.expired() || m_wpScoreCounter.expired()) return;

	this                   ->SetTimeAttack();

	m_wpComboCounter.lock()->SetTimeAttack();
	m_wpGauge.lock()       ->SetTimeAttack();
	m_wpScoreCounter.lock()->SetTimeAttack();
	m_wpStageTime.lock()   ->SetTimeAttack();
}

void GameUi::SetModeTimeLimit() noexcept
{
	if (m_wpGauge.expired() || m_wpStageTime.expired() || 
		m_wpComboCounter.expired() || m_wpScoreCounter.expired()) return;

	this                   ->SetTimeLimit();
	
	m_wpComboCounter.lock()->SetTimeLimit();
	m_wpGauge.lock()       ->SetTimeLimit();
	m_wpScoreCounter.lock()->SetTimeLimit();
	m_wpStageTime.lock()   ->SetTimeLimit();
}

int GameUi::GetMaxCombo() noexcept
{
	if (m_wpComboCounter.expired())return NULL;
	auto combo(m_wpComboCounter.lock());
	return combo->GetMaxCombo();
}

int GameUi::GetTime() noexcept
{
	if (m_wpStageTime.expired())return NULL;
	auto time(m_wpStageTime.lock());
	return time->GetTime();
}

int GameUi::GetScore() noexcept
{
	if (m_wpScoreCounter.expired())return NULL;
	auto score(m_wpScoreCounter.lock());
	return score->GetTotalScore();
}

void GameUi::CrystalBroken() noexcept
{
	if (m_wpScoreCounter.expired())return;
	auto score(m_wpScoreCounter.lock());
	score->CrystalBrokenCount();
}

void GameUi::TreasureCollected() noexcept
{
	if (m_wpScoreCounter.expired())return;
	auto score(m_wpScoreCounter.lock());
	score->TreasureCollectedCount();
}

void GameUi::Mistake() noexcept
{
	if (m_wpGauge.expired())return;
	auto gauge(m_wpGauge.lock());
	gauge->MisTake();

	auto spBanTex(RESOURCE.IndexTexture("Ban/ban.png"));
	if (!spBanTex) _ASSERT_EXPR(false, L"TextureData Not Found");

	AddUiObjList<Ban>(m_wpBan, spBanTex);

	KdAudioManager::Instance().Play("Asset/Sounds/Ban/ban.wav");
}