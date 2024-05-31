#include "BackGround.h"
#include "../../../Object/GameObject/Destructible/Crystal/Crystal.h"


void BackGround::Init()
{
	m_spPolygon.fill(std::make_shared<KdSquarePolygon>());
	m_upCrystal = std::make_shared<Crystal>();
	for (decltype(auto) arr: m_spPolygon)
	{
		arr->SetMaterial("Asset/Textures/BackGround/backGround.png");
		arr->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	SetScale(30);
	m_mWorld *= Math::Matrix::CreateTranslation(0,0,15);
}

void BackGround::GenerateDepthMapFromLight()
{
	for (decltype(auto) arr : m_spPolygon)
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*arr,m_mWorld);
}

void BackGround::DrawLit()
{
	for (decltype(auto) arr : m_spPolygon)
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*arr, m_mWorld);
	m_upCrystal->DrawLit();
}

void BackGround::DrawBright()
{
}

void BackGround::PreUpdate()
{
}

void BackGround::Update()
{
	m_upCrystal->Update();
}

void BackGround::PostUpdate()
{
}