#include "Character.h"
#include "../../../../Data/BinaryAccessor.hpp"

Character::Character(const std::shared_ptr<KdTexture>& spCombo, const std::shared_ptr<KdTexture>& spTime, const std::shared_ptr<KdTexture>& spTension, const std::shared_ptr<KdTexture>& spMiddleClick) noexcept
	: m_spComboTex      (spCombo)
	, m_spTimeTex       (spTime)
	, m_spTensionTex    (spTension)
	, m_spMiddleClickTex(spMiddleClick)
{ Init(); }

void Character::Init()
{
	// Local Declaration
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/CharacterTexturParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/CharacterTexturParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	m_comboPos       = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_timePos        = { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_tensionPos
		= { x,y };

	x = parameter[--counter];
	y = parameter[--counter];

	m_middleClickPos = { x,y };
}

void Character::DrawSprite() noexcept
{
	KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spComboTex, static_cast<int>(m_comboPos.x), static_cast<int>(m_comboPos.y));

	KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spTimeTex, static_cast<int>(m_timePos.x), static_cast<int>(m_timePos.y));

	KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spTensionTex, static_cast<int>(m_tensionPos.x), static_cast<int>(m_tensionPos.y));

	KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spMiddleClickTex, static_cast<int>(m_middleClickPos.x), static_cast<int>(m_middleClickPos.y));
}