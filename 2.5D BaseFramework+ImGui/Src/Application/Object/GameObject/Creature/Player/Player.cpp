#include "Player.h"
#include "../../Tool/Pickaxe/PickaxeManager.h"

void Player::Init()
{
	{
		m_spModel = std::make_shared<KdModelData>();
		const auto IsAssert = m_spModel->Load("Asset/Models/Rail/cart.gltf");
		_ASSERT_EXPR(IsAssert, L"ModelData Not Found");
	}
	m_mWorld *= Math::Matrix::CreateScale(3.0f);
	m_mWorld *= Math::Matrix::CreateTranslation(-1.5f,0,0);

	m_spPickaxe = std::make_shared<PickaxeManager>();
	m_spPickaxe->Init();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	m_spPickaxe->GenerateDepthMapFromLight();
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	m_spPickaxe->DrawLit();
}

void Player::PreUpdate()
{
	m_spPickaxe->PreUpdate();
}

void Player::Update()
{
	m_spPickaxe->Update();
}

void Player::PostUpdate()
{
	m_spPickaxe->PostUpdate();
}
