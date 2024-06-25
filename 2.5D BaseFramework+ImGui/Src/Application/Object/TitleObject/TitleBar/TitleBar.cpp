#include "TitleBar.h"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Data/ResourceManager.h"
#include "../../../Data/BinaryAccessor.hpp"

TitleBar::TitleBar() noexcept
	: m_moveY      (Def::FloatNull)
	, m_moveYSpeed (Def::FloatNull)
	, m_fullDegrees(Def::FloatNull)
{ Init(); }

void TitleBar::Init()
{
	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TitleBarTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TitleBarTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_spTex = RESOURCE.IndexTexture("Texts/miner.png");
	if (!m_spTex) _ASSERT_EXPR(false, L"TextureData Not Found");

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_pos         = { x,y };
	m_moveY       = parameter[--counter];
	m_moveYSpeed  = parameter[--counter];
	m_fullDegrees = parameter[--counter];
}

void TitleBar::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + sin(DirectX::XMConvertToRadians(m_moveY)) * m_moveYSpeed));
}

void TitleBar::Update()
{
	++m_moveY;
	if (m_moveY > m_fullDegrees) m_moveY -= m_fullDegrees;
}