#include "Gauge.h"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../Utility/UtilityDefault.hxx"

Gauge::Gauge(const std::shared_ptr<KdTexture>& spTex) noexcept
	: m_rectY       (Def::IntNull)
	, m_mistakeCount(Def::SizTNull)
	, m_maxMistake  (Def::SizTNull)
	, m_speed       (Def::FloatNull)
	, m_isTired     (false)
{
	SetTex(spTex);
	Init();
}

void Gauge::Init()
{
	// Local Declaration
	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/GageTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/GageTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x     (static_cast<long>(parameter[--counter]));
	auto y     (static_cast<long>(parameter[--counter]));
	auto width (static_cast<long>(parameter[--counter]));
	auto height(static_cast<long>(parameter[--counter]));

	m_rect       = { x, y, width, height };
	m_rectY      = static_cast<int>(parameter[--counter]);

	auto xX(parameter[--counter]);
	auto yY(parameter[--counter]);

	m_pos        = { xX,yY };

	xX = parameter[--counter];
	yY = parameter[--counter];

	m_goalPos    = { xX,yY };

	m_maxMistake = static_cast<size_t>(parameter[--counter]);
	m_speed      = parameter[--counter];
}

void Gauge::DrawSprite() noexcept
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rect.width, m_rect.height, &m_rect);
}

void Gauge::Update()
{
	if (m_isLimitOver || m_isComboOver)
	{
		auto distance(m_goalPos - m_pos);
		if (std::abs(distance.LengthSquared()) > (m_speed * m_speed))
		{
			distance.Normalize();
			m_pos += distance * m_speed;
		}
		else m_pos = m_goalPos;
	}

	if (m_mistakeCount >= m_maxMistake)
	{
		m_isTired   = true;
		m_isExpired = true;
	}
	m_rect.y = static_cast<long>(m_mistakeCount * m_rectY);
}

void Gauge::PostUpdate()
{
	if (m_isModePractice && m_mistakeCount >= m_maxMistake) m_mistakeCount = Def::SizTNull;
}