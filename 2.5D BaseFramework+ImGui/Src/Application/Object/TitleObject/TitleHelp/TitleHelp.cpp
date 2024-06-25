#include "TitleHelp.h"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Data/ResourceManager.h"
#include "../../../Data/BinaryAccessor.hpp"

TitleHelp::TitleHelp() noexcept
	: m_moveY      (Def::FloatNull)
	, m_moveYSpeed (Def::FloatNull)
	, m_fullDegrees(Def::FloatNull)
{ Init(); }

void TitleHelp::Init()
{
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TitleHelpTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TitleHelpTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_spTex = RESOURCE.IndexTexture("Texts/titleHelp.png");
	if (!m_spTex) _ASSERT_EXPR(false, L"TextureData Not Found");

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_pos         = {x,y};
	m_moveY       = parameter[--counter];
	m_moveYSpeed  = parameter[--counter];
	m_fullDegrees = parameter[--counter];
}

void TitleHelp::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + cos(DirectX::XMConvertToRadians(m_moveY)) * m_moveYSpeed));
}

void TitleHelp::Update()
{
	++m_moveY;
	if (m_moveY > m_fullDegrees) m_moveY -= m_fullDegrees;
}