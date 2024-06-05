#include "Player.h"
#include "../../Tool/Pickaxe/PickaxeManager.h"
#include "../../../../Utility/UtilityKey.hxx"

void Player::Init()
{
	m_spPickaxe = std::make_shared<PickaxeManager>();
	m_spModel = std::make_shared<KdModelData>();
	{
		const auto IsAssert = m_spModel->Load("Asset/Models/Rail/cart.gltf");
		_ASSERT_EXPR(IsAssert, L"ModelData Not Found");
	}
	m_mWorld *= Math::Matrix::CreateScale(3.0f);
	m_mWorld *= Math::Matrix::CreateTranslation(-1.5f,0,0);

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
	if (Key::IsPushing(Key::E))
		m_spPickaxe->SetNextPickaxe(PickaxeManager::PickaxeType::Gold);
}

void Player::PostUpdate()
{
	m_spPickaxe->PostUpdate();
}
