#include "GameUi.h"
#include "../../../Data/ResourceManager.h"

void GameUi::Init()
{
}

void GameUi::DrawSprite()
{
}

void GameUi::Update()
{
}

void GameUi::SetTexture()
{
	 m_spCoinTex = RESOURCE.IndexTexture("Coin/coin.png");
	 if(!m_spCoinTex) _ASSERT_EXPR(false, L"TextureData Not Found");
}
