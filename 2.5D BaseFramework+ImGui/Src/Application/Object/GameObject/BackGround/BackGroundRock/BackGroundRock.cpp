﻿#include "BackGroundRock.h"
#include "../../../../Utility/UtilityMath.hxx"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Data/ResourceManager.h"

void BackGroundRock::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	{
		std::string path;
		switch (Formula::Rand(static_cast<size_t>(RockType::YelSmooth), static_cast<size_t>(RockType::Crystal)))
		{
		case RockType::YelSmooth:
			path = "Rock/ImageToStl.com_rock_01.gltf";
			SetScale(0.08f);
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
			SetScale(0.75f);
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
		m_spModel = RESOURCE.IndexModelData(path);
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
