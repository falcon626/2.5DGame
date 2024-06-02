#include "BackGround.h"
#include "../Destructible/Crystal/Crystal.h"
#include "BackGroundRock/BackGroundRock.h"
#include "../../../Utility/UtilityDefault.hxx"


void BackGround::Init()
{
	m_spPolygon.fill(std::make_shared<KdSquarePolygon>());
	m_spRock.fill(std::make_shared<BackGroundRock>());
	m_spCrystal = std::make_shared<Crystal>();
	{
		auto spMaterialTex = std::make_shared<KdTexture>();
		{
			const auto IsAssert = spMaterialTex->Load("Asset/Textures/BackGround/backGround.png");
			_ASSERT_EXPR(IsAssert, L"MaterialData Not Found");
		}
		for (decltype(auto) arr : m_spPolygon)
		{
			arr->SetMaterial(spMaterialTex);
			arr->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
		}
		for (decltype(auto) arr : m_spRock)
			arr->Init();
	}
	m_spRock[RockPattern::First]->SetPos({-6,3,17});
	m_spRock[RockPattern::Second]->SetPos({-1,4,18});
	m_spRock[RockPattern::Third]->SetPos({4,0,15});
	m_spRock[RockPattern::Fourth]->SetPos({6,0,7});
	m_spRock[RockPattern::Fifth]->SetPos({-7,5,2});
	auto mScale = Math::Matrix::CreateScale(30.00f);
	auto mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	m_mWorldPolygon[Surface::Top] = mScale * mRotation * Math::Matrix::CreateTranslation(0, 15, -15);
	m_mWorldPolygon[Surface::Bottom] = mScale * mRotation * Math::Matrix::CreateTranslation(0, 0, -15);
	m_mWorldPolygon[Surface::Front] = mScale * Math::Matrix::CreateTranslation(0, 0, 15);
	m_mWorldPolygon[Surface::Back] = mScale * Math::Matrix::CreateTranslation(0, 0, -15);
}

void BackGround::GenerateDepthMapFromLight()
{
	for (auto i = Def::SizTNull; i < m_spPolygon.size(); ++i)
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon[i], m_mWorldPolygon[i]);
	//for (decltype(auto) arr : m_spRock)
	//	arr->GenerateDepthMapFromLight();
}

void BackGround::DrawLit()
{
	for (auto i = Def::SizTNull; i < m_spPolygon.size(); ++i)
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon[i], m_mWorldPolygon[i]);
	for (decltype(auto) arr : m_spRock)
		arr->DrawLit();
	m_spCrystal->DrawLit();
}

void BackGround::DrawBright()
{
}

void BackGround::PreUpdate()
{
}

void BackGround::Update()
{
	m_spCrystal->Update();
}

void BackGround::PostUpdate()
{
}