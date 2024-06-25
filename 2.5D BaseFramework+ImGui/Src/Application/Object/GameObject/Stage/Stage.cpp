#include "Stage.h"
#include "../Creature/Player/Player.h"
#include "../BackGround/BackGround.h"
#include "../GameUi/GameUi.h"
#include "../Destructible/Crystal/Crystal.h"
#include "../Destructible/Treasure/Treasure.h"
#include "../../../Data/BinaryAccessor.hpp"
#include "../../../Utility/UtilityMath.hxx"
#include "../../../Utility/UtilityDefault.hxx"

Stage::Stage() noexcept
	: m_stageType           (Def::SizTNull)
	, m_maxPercentage       (Def::SizTNull)
	, m_crystalPopPercentage(Def::SizTNull)
	, m_stageDistance       (Def::FloatNull)
	, m_isAction            (false)
{}

void Stage::Init()
{
	m_spBackGround = std::make_shared<BackGround>();

	std::vector<int>  parameter;
	auto counter (Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/StageParameter/Initial_Int.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/StageParameter/Initial_Int.dat", parameter, counter);
#endif // _DEBUG
	}

	m_maxPercentage        = parameter[--counter];
	m_crystalPopPercentage = parameter[--counter];
}

void Stage::GenerateDepthMapFromLight()
{
	m_spBackGround->GenerateDepthMapFromLight();
	if (m_stageType == static_cast<size_t>(StageType::Crystal)) m_spCrystal->GenerateDepthMapFromLight();
	else m_spTreasure->GenerateDepthMapFromLight();
}

void Stage::DrawLit()
{
	m_spBackGround->DrawLit();
	if (m_stageType == static_cast<size_t>(StageType::Crystal)) m_spCrystal->DrawLit();
	else m_spTreasure->DrawLit();
}

void Stage::PreUpdate()
{
	SetNowComboNum();
}

void Stage::Update()
{
	if (!m_wpGameUi.expired() && 
		(m_wpGameUi.lock()->IsTired() || m_wpGameUi.lock()->IsLimitOver() || m_wpGameUi.lock()->IsComboOver())) return;
	if (!m_wpPlayer.expired())
	{
		auto player(m_wpPlayer.lock());
		if (m_stageType == static_cast<size_t>(StageType::Crystal))
		{
			auto distance(player->GetPos().x - m_spCrystal->GetPos().x);
			
			// Player Looking The Crystal
			if (distance == Def::FloatNull) TargetCrystal(player);

			// Suicide
			if (distance <= m_stageDistance) m_isExpired = true;

			if (m_spCrystal->IsBroken() ||player->IsTaking()) player->Move();
		}
		if (m_stageType == static_cast<size_t>(StageType::Treasure))
		{
			auto distance(player->GetPos().x - m_spTreasure->GetPos().x);

			// Player Looking The Treasure
			if (distance == Def::FloatNull) TargetTreasure(player);

			// Suicide
			if (distance <= m_stageDistance) m_isExpired = true;

			if (m_spTreasure->IsBroken() || m_spTreasure->IsCollected()) player->Move();
		}
	}

	if (m_stageType == static_cast<size_t>(StageType::Crystal)) m_spCrystal->Update();
	else m_spTreasure->Update();
}

void Stage::AddStage(const size_t& pattern)
{
	if (pattern == Def::SizTNull)
	{
		m_stageType = static_cast<size_t>(StageType::Crystal);
		m_spCrystal = std::make_shared<Crystal>();
	}
	else if(pattern == Def::SizTOne)
	{
		m_stageType  = static_cast<size_t>(StageType::Treasure);
		m_spTreasure = std::make_shared<Treasure>();
	}
	else
	{
		auto percentage(Formula::Rand(Def::SizTNull, m_maxPercentage));
		if (percentage >= m_crystalPopPercentage)
		{
			m_stageType = static_cast<size_t>(StageType::Crystal);
			m_spCrystal = std::make_shared<Crystal>();
		}
		else
		{
			m_stageType = static_cast<size_t>(StageType::Treasure);
			m_spTreasure = std::make_shared<Treasure>();
		}
	}
}

void Stage::AddStage()
{
	auto percentage(Formula::Rand(Def::SizTNull, m_maxPercentage));
	if (percentage >= m_crystalPopPercentage)
	{
		m_stageType = static_cast<size_t>(StageType::Crystal);
		m_spCrystal = std::make_shared<Crystal>();
	}
	else
	{
		m_stageType = static_cast<size_t>(StageType::Treasure);
		m_spTreasure = std::make_shared<Treasure>();
	}
}

void Stage::SetWeakPtr(const std::shared_ptr<Player>& spPlayer, const std::shared_ptr<GameUi>& spGameUi) noexcept
{
	m_wpPlayer = spPlayer;
	m_wpGameUi = spGameUi;
}

void Stage::SetNowComboNum()
{
	if (m_wpGameUi.expired() || m_wpPlayer.expired()) return;
	m_wpGameUi.lock()->SetNowComboNum(m_wpPlayer.lock()->GetCombo());
}

void Stage::SetPos(const Math::Vector3& pos, const float& stageDistance)
{
	m_mWorld.Translation(pos);
	m_spBackGround->SetPos(pos);
	if (m_stageType == static_cast<size_t>(StageType::Crystal)) m_spCrystal->SetPos(pos);
	else m_spTreasure->SetPos(pos);
	m_stageDistance = stageDistance;
}

void Stage::TargetCrystal(const std::shared_ptr<Player>& player) noexcept
{
	if (player->IsUsing())
	{
		if (!m_isAction)
		{
			m_spCrystal->OnBreak(player->SwingPow());
			if (m_spCrystal->IsBroken() && !m_wpGameUi.expired())
			{
				player->ChainCombo();
				m_wpGameUi.lock()->CrystalBroken();
			}
		}
		m_isAction = true;
	}
	else if (player->IsTaking())
	{
		if (!m_isAction && !m_wpGameUi.expired())
		{
			player->ComboInterrupted();
			m_wpGameUi.lock()->Mistake();
		}
		m_isAction = true;
	}
	else m_isAction = false;
}

void Stage::TargetTreasure(const std::shared_ptr<Player>& player) noexcept
{
	if (player->IsUsing())
	{
		if (!m_isAction)
		{
			m_spTreasure->OnBreak();
			if (m_spTreasure->IsBroken() && !m_wpGameUi.expired())
			{
				player->ComboInterrupted();
				m_wpGameUi.lock()->Mistake();
			}
		}
		m_isAction = true;
	}
	else if (player->IsTaking())
	{
		if (!m_isAction)
		{
			m_spTreasure->OnCollected();
			if (m_spTreasure->IsCollected() && !m_wpGameUi.expired())
			{
				player->ChainCombo();
				m_wpGameUi.lock()->TreasureCollected();
			}
		}
		m_isAction = true;
	}
	else m_isAction = false;
}