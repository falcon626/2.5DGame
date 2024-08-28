#include "ScoreCounter.h"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../System/Counter/Counter.h"

ScoreCounter::ScoreCounter(const std::shared_ptr<KdTexture>& spTex, const std::shared_ptr<KdTexture> spCrystalTex, const std::shared_ptr<KdTexture> spTreasureTex) noexcept
	: m_crystalBrokenNum    (Def::IntNull)
	, m_treasureCollectedNum(Def::IntNull)
	, m_speed               (Def::FloatNull)
{
	SetTex(spTex);
	m_spCrystalTex  = spCrystalTex;
	m_spTreasureTex = spTreasureTex;
	Init();
}

void ScoreCounter::Init()
{
	m_spCrystalCounter  = std::make_shared<Counter>();
	m_spCrystalCounter->SetTex(m_spTex);

	m_spTreasureCounter = std::make_shared<Counter>();
	m_spTreasureCounter->SetTex(m_spTex);

	// Local Declaration
	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/ScoreCounterTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/ScoreCounterTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_pos                = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_crystalPos         = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_crystalCounterPos  = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_treasurePos        = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_treasureCounterPos = { x,y };

	m_goalPos = { m_pos.x,parameter[--counter]};

	m_speed   = parameter[--counter];
}

void ScoreCounter::DrawSprite() noexcept
{
	m_spCrystalCounter->DrawSpriteCounter();
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spCrystalTex, static_cast<int>(m_pos.x + m_crystalPos.x), static_cast<int>(m_pos.y + m_crystalPos.y));
	
	m_spTreasureCounter->DrawSpriteCounter();
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTreasureTex, static_cast<int>(m_pos.x + m_treasurePos.x), static_cast<int>(m_pos.y + m_treasurePos.y));
}

void ScoreCounter::Update()
{
	if (m_isTired || m_isLimitOver || m_isComboOver)
	{
		auto distance(m_goalPos - m_pos);
		if (std::abs(distance.LengthSquared()) > (m_speed * m_speed))
		{
			distance.Normalize();
			m_pos += distance * m_speed;
		}
		else m_pos = m_goalPos;
	}

	m_spCrystalCounter->SetCounterParameter(m_crystalBrokenNum, m_pos + m_crystalCounterPos, kBlueColor + kGreenColor);
	m_spCrystalCounter->Update();
	m_spTreasureCounter->SetCounterParameter(m_treasureCollectedNum, m_pos + m_treasureCounterPos, kRedColor + kGreenColor);
	m_spTreasureCounter->Update();
}