#include "Stage.h"
#include "../Creature/Player/Player.h"
#include "../BackGround/BackGround.h"
#include "../Destructible/Crystal/Crystal.h"
#include "../Destructible/Treasure/Treasure.h"
#include "../../../Data/BinaryAccessor.hpp"
#include "../../../Utility/UtilityMath.hxx"
#include "../../../Utility/UtilityDefault.hxx"

Stage::Stage() noexcept
	: m_stageType(Def::SizTNull)
	, m_stageDistance(Def::FloatNull)
	, m_isAction(false)
{}

void Stage::Init()
{
	m_spBackGround = std::make_shared<BackGround>();
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

void Stage::DrawBright()
{
}

void Stage::Update()
{
	if (!m_wpPlayer.expired())
	{
		auto player(m_wpPlayer.lock());
		if (m_stageType == static_cast<size_t>(StageType::Crystal))
		{
			auto distance(player->GetPos().x - m_spCrystal->GetPos().x);
			if (distance == Def::FloatNull)
			{
				if (player->IsUsing())
				{
					if (!m_isAction)
					{
						m_spCrystal->OnBreak(player->SwingPow());
						if (m_spCrystal->IsBroken()) player->ChainCombo();
					}
					m_isAction = true;
				}
				else if (player->IsTaking())
				{
					if (!m_isAction) player->ComboInterrupted();
					m_isAction = true;
				}
				else m_isAction = false;
			}
			if (distance <= m_stageDistance) m_isExpired = true;
			if (m_spCrystal->IsBroken() ||player->IsTaking()) player->Move();
		}
		if (m_stageType == static_cast<size_t>(StageType::Treasure))
		{
			auto distance(player->GetPos().x - m_spTreasure->GetPos().x);
			if (distance == Def::FloatNull)
			{
				if (player->IsUsing())
				{
					if (!m_isAction)
					{
						m_spTreasure->OnBreak();
						if (m_spTreasure->IsBroken()) player->ComboInterrupted();
					}
					m_isAction = true;
				}
				else if (player->IsTaking())
				{
					if (!m_isAction)
					{
						m_spTreasure->OnCollect();
						if (m_spTreasure->IsCollect())player->ChainCombo();
					}
					m_isAction  = true;
				}
				else m_isAction = false;
			}
			if (distance <= m_stageDistance) m_isExpired = true;
			if (m_spTreasure->IsBroken() || m_spTreasure->IsCollect()) player->Move();
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
	else
	{
		m_stageType  = static_cast<size_t>(StageType::Treasure);
		m_spTreasure = std::make_shared<Treasure>();
	}
}

void Stage::AddStage()
{
	auto percentage(Formula::Rand(0, 99));
	if (percentage >= 49)
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

void Stage::SetPos(const Math::Vector3& pos, const float& stageDistance)
{
	m_mWorld.Translation(pos);
	m_spBackGround->SetPos(pos);
	if (m_stageType == static_cast<size_t>(StageType::Crystal)) m_spCrystal->SetPos(pos);
	else m_spTreasure->SetPos(pos);
	m_stageDistance = stageDistance;
}