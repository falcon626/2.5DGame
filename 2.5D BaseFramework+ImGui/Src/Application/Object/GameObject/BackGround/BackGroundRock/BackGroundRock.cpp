#include "BackGroundRock.h"
#include "../../../../Utility/UtilityMath.hxx"
#include "../../../../Utility/UtilityDefault.hxx"

void BackGroundRock::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	{
		std::string path;
		switch (Formula::Rand(static_cast<int>(RockType::YelSmooth), static_cast<int>(RockType::Crystal)))
		{
		case RockType::YelSmooth:
			path = "Rock/ImageToStl.com_rock_01.gltf";
			SetScale(0.5f);
			break;
		case RockType::YelBumpy:
			path = "Rock/ImageToStl.com_rocks_02.gltf";
			break;
		case RockType::GraHeavy:
			path = "Rock/Rock_01.gltf";
			break;
		case RockType::GraSlanted:
			path = "Rock/Rock_02.gltf";
			break;
		case RockType::GraTowering:
			path = "Rock/Rock_03.gltf";
			break;
		case RockType::GraProtrusion:
			path = "Rock/Rock_04.gltf";
			break;
		case RockType::GraFlat:
			path = "Rock/Rock_05.gltf";
			break;
		case RockType::Crystal:
			path = "Crystal/biggestblue/crystalexport.gltf";
			SetScale(0.5f);
			break;
		default:
			_ASSERT_EXPR(false, L"Incorrect Random Range");
			break;
		}
		const auto IsAssert = m_spModel->Load("Asset/Models/" + path);
		_ASSERT_EXPR(IsAssert, L"ModelData Not Found");
	}
}

void BackGroundRock::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void BackGroundRock::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void BackGroundRock::Update()
{

}

void BackGroundRock::PostUpdate()
{
	
}
