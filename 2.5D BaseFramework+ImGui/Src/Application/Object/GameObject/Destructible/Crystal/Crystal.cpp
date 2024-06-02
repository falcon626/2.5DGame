#include "Crystal.h"

void Crystal::Init()
{
	{
		m_spModel = std::make_shared<KdModelData>();
		const auto IsAssert = m_spModel->Load("Asset/Models/Crystal/purple/crystals.gltf");
		_ASSERT_EXPR(IsAssert, L"ModelData Not Found");
	}
	SetScale(0.5f);
	SetPos({0,1,8});
}

void Crystal::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Crystal::Update()
{
}
