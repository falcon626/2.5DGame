#include "Coin.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Utility/UtilityMath.hxx"

void Coin::Init()
{
	m_spTex = std::make_shared<KdTexture>();
}

void Coin::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y);
}

void Coin::Update()
{

}