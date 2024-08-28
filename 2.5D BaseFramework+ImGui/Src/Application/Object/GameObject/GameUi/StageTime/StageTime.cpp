#include "StageTime.h"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../System/Counter/Counter.h"
#include "../../../../System/Timer/Timer.h"
#include "../../../../main.h"

StageTime::StageTime(const std::shared_ptr<KdTexture>& spTex) noexcept
	: m_limitTime  (Def::IntNull)
	, m_time       (Def::IntNull)
	, m_speed      (Def::FloatNull)
	, m_isLimitOver(false)
{
	SetTex(spTex);
	Init();
}

void StageTime::Init()
{
	m_spCounter = std::make_shared<Counter>();
	m_spTimer   = std::make_shared<Timer>();

	m_spTimer->Start();
	m_spCounter->SetTex(m_spTex);

	// Local Declaration
	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/StageTimeTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/StageTimeTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_pos             = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_tiredEndGoalPos = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_goalPos         = { x,y };

	m_speed           = parameter[--counter];
	m_limitTime       = static_cast<int>(parameter[--counter]);
}

void StageTime::DrawSprite() noexcept
{
	m_spCounter->DrawSpriteCounter();
}

void StageTime::Update()
{
	if(m_isModeTimeLimit) m_time = m_limitTime - static_cast<int>(m_spTimer->ElapsedSeconds());
	else m_time = static_cast<int>(m_spTimer->ElapsedSeconds());
	
	if (m_isModeTimeLimit && m_time <= Def::IntNull) m_isLimitOver = true;

	m_spCounter->SetCounterParameter(m_time, m_pos);

	m_spCounter->Update();

	if (m_isTired)
	{
		m_spTimer->Stop();

		auto distance(m_tiredEndGoalPos - m_pos);
		if (std::abs(distance.LengthSquared()) > (m_speed * m_speed))
		{
			distance.Normalize();
			m_pos += distance * m_speed;
		}
		else m_pos = m_tiredEndGoalPos;
	}

	else if (m_isComboOver || m_isLimitOver)
	{
		m_spTimer->Stop();

		auto distance(m_goalPos - m_pos);
		if (std::abs(distance.LengthSquared()) > (m_speed * m_speed))
		{
			distance.Normalize();
			m_pos += distance * m_speed;
		}
		else m_pos = m_goalPos;
	}
}