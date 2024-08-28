#include "ComboCounter.h"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../System/Counter/Counter.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Utility/UtilityMath.hxx"

ComboCounter::ComboCounter(const std::shared_ptr<KdTexture>& spTex) noexcept
	: m_color         (Def::Color)
	, m_nowComboNum   (Def::SizTNull)
	, m_maxComboNum   (Def::SizTNull)
	, m_limitComboNum (Def::SizTNull)
	, m_firstBorder   (Def::SizTNull)
	, m_secondBorder  (Def::SizTNull)
	, m_thirdBorder   (Def::SizTNull)
	, m_changeColorVal(Def::FloatNull)
{
	SetTex(spTex);
	Init();
}

void ComboCounter::Init()
{
	m_spCounter = std::make_shared<Counter>();
	m_spCounter ->SetTex(m_spTex);

	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = BinaryAccessor::Instance().Load("Asset/Data/ComboCounterTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/ComboCounterTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_pos            = { x,y };

	m_limitComboNum  = static_cast<size_t>(parameter[--counter]);

	m_firstBorder    = static_cast<size_t>(parameter[--counter]);
	m_secondBorder   = static_cast<size_t>(parameter[--counter]);
	m_thirdBorder    = static_cast<size_t>(parameter[--counter]);

	m_changeColorVal = parameter[--counter];
}

void ComboCounter::DrawSprite() noexcept
{
	m_spCounter->DrawSpriteCounter();
}

void ComboCounter::Update()
{
	if (m_isTired || m_isLimitOver || m_isComboOver ) m_nowComboNum = m_maxComboNum;

	m_spCounter->SetCounterParameter(static_cast<int>(m_nowComboNum), m_pos, m_color);
	m_spCounter->Update();

	if (m_nowComboNum >= m_firstBorder && m_nowComboNum < m_secondBorder)
	{
		m_color.G(m_changeColorVal);
		m_color.B(m_changeColorVal);
	}
	else if (m_nowComboNum >= m_secondBorder && m_nowComboNum < m_thirdBorder)
	{
		m_color.G(Def::FloatNull);
		m_color.B(Def::FloatNull);
	}
	else if (m_nowComboNum >= m_thirdBorder)
	{
		m_color.R(Formula::Rand(Def::FloatNull, Def::FloatOne));
		m_color.G(Formula::Rand(Def::FloatNull, Def::FloatOne));
		m_color.B(Formula::Rand(Def::FloatNull, Def::FloatOne));
	}
	else m_color = Def::Color;

	if (m_nowComboNum > m_maxComboNum) m_maxComboNum = m_nowComboNum;

	if (m_isModeTimeAttack && m_maxComboNum >= m_limitComboNum) m_isComboOver = true;
}