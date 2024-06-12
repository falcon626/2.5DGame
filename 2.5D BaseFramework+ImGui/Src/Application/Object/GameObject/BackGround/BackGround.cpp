#include "BackGround.h"
#include "BackGroundRock/BlueCrystal/BlueCrystal.hpp"
#include "BackGroundRock/GrayFlat/GrayFlat.hpp"
#include "BackGroundRock/GrayHeavy/GrayHeavy.hpp"
#include "BackGroundRock/GrayProtrusion/GrayProtrusion.hpp"
#include "BackGroundRock/GraySlanted/GraySlanted.hpp"
#include "BackGroundRock/GrayTowering/GrayTowering.hpp"
#include "BackGroundRock/YellowBumpy/YellowBumpy.hpp"
#include "BackGroundRock/YellowSmooth/YellowSmooth.hpp"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Data/BinaryAccessor.hpp"


void BackGround::Init()
{
	for (decltype(auto) blCr : m_spBlueCrystal)
		blCr = std::make_shared<BlueCrystal>();
	for (decltype(auto) grFl : m_spGrayFlat)
		grFl = std::make_shared<GrayFlat>();
	for (decltype(auto) grHe : m_spGrayHeavy)
		grHe = std::make_shared<GrayHeavy>();
	for (decltype(auto) grPr : m_spGrayProtrusion)
		grPr = std::make_shared<GrayProtrusion>();
	for (decltype(auto) grSl : m_spGraySlanted)
		grSl = std::make_shared<GraySlanted>();
	for (decltype(auto) grTo : m_spGrayTowering)
		grTo = std::make_shared<GrayTowering>();
	for (decltype(auto) yeBu : m_spYellowBumpy)
		yeBu = std::make_shared<YellowBumpy>();
	for (decltype(auto) yeSm : m_spYellowSmooth)
		yeSm = std::make_shared<YellowSmooth>();
	
	//m_spPolygon.fill(std::make_shared<KdSquarePolygon>());
	//{
	//	auto spMaterialTex = std::make_shared<KdTexture>();
	//	{
	//		const auto IsAssert = spMaterialTex->Load("Asset/Textures/BackGround/stone_00007.png");
	//		_ASSERT_EXPR(IsAssert, L"MaterialData Not Found");
	//	}
	//	for (decltype(auto) arr : m_spPolygon)
	//	{
	//		arr->SetMaterial(spMaterialTex);
	//		arr->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//	}
	//}

	//m_spRock[RockPattern::First]->SetPos({-6,3,16});
	//m_spRock[RockPattern::Second]->SetPos({-3,7,15});
	//m_spRock[RockPattern::Third]->SetPos({4,3,14});
	//m_spRock[RockPattern::Fourth]->SetPos({6,0,7});
	//m_spRock[RockPattern::Fifth]->SetPos({-5,2,7});
	//auto mScale = Math::Matrix::CreateScale(30.00f);
	//auto mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	//m_mWorldPolygon[Surface::Top] = mScale * mRotation * Math::Matrix::CreateTranslation(0, 15, -15);
	//m_mWorldPolygon[Surface::Bottom] = mScale * mRotation * Math::Matrix::CreateTranslation(0, 0, -15);
	//m_mWorldPolygon[Surface::Front] = mScale * Math::Matrix::CreateTranslation(0, 0, 15);
	//m_mWorldPolygon[Surface::Back] = mScale * Math::Matrix::CreateTranslation(0, 0, -15);
}

void BackGround::SetObjectPosition()
{
	std::vector<float>  parameter;
	auto counter  (Def::SizTNull);
	auto stageZeroPoint(GetPos());
	{
		const auto IsAssert = DATA.Load("Asset/Data/RocksParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
	}
	SetObjectProperties(m_spBlueCrystal,    parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayFlat,       parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayHeavy,      parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayProtrusion, parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGraySlanted,    parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayTowering,   parameter, counter, stageZeroPoint);

	//m_spBlueCrystal[elementCount]->SetPos({8.0f, 1.0f, 15.0f});
	//m_spBlueCrystal[elementCount]->SetScale(0.60f);
	//++elementCount;
	//m_spBlueCrystal[elementCount]->SetPos({ 0,-1,15 });
	//m_spBlueCrystal[elementCount]->SetScale(0.7f);
	//++elementCount;
	//m_spBlueCrystal[elementCount]->SetPos({ 4,0,16 });
	//m_spBlueCrystal[elementCount]->SetScale(0.7f);
	//elementCount = Def::SizTNull;
	//m_spGrayFlat[elementCount]->SetPos({ -4,-2,10 });
	//m_spGrayFlat[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayFlat[elementCount]->SetPos({ 0,-12,0 });
	//m_spGrayFlat[elementCount]->SetScale(5.0f);
	//++elementCount;
	//m_spGrayFlat[elementCount]->SetPos({ 0,-12,8 });
	//m_spGrayFlat[elementCount]->SetScale(5.0f);
	//elementCount = Def::SizTNull;
	//m_spGrayHeavy[elementCount]->SetPos({ 3,0,16 });
	//m_spGrayHeavy[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayHeavy[elementCount]->SetPos({ 5,0,13 });
	//m_spGrayHeavy[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayHeavy[elementCount]->SetPos({ 7,1,15 });
	//m_spGrayHeavy[elementCount]->SetScale(1.0f);
	//elementCount = Def::SizTNull;
	//m_spGrayProtrusion[elementCount]->SetPos({ 10,0,13 });
	//m_spGrayProtrusion[elementCount]->SetScale(1.5f);
	//++elementCount;
	//m_spGrayProtrusion[elementCount]->SetPos({ 10,0,9 });
	//m_spGrayProtrusion[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayProtrusion[elementCount]->SetPos({ 10,0,5 });
	//m_spGrayProtrusion[elementCount]->SetScale(1.0f);
	//elementCount = Def::SizTNull;
	//m_spGraySlanted[elementCount]->SetPos({ -7,3,18 });
	//m_spGraySlanted[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGraySlanted[elementCount]->SetPos({ -7,1,18 });
	//m_spGraySlanted[elementCount]->SetScale(1.0f);
	//elementCount = Def::SizTNull;
	//m_spGrayTowering[elementCount]->SetPos({ -4,0,20 });
	//m_spGrayTowering[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayTowering[elementCount]->SetPos({ 2.3f,-2,20 });
	//m_spGrayTowering[elementCount]->SetScale(1.2f);
	//++elementCount;
	//m_spGrayTowering[elementCount]->SetPos({ -2,0,20 });
	//m_spGrayTowering[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayTowering[elementCount]->SetPos({ -5,0,20 });
	//m_spGrayTowering[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayTowering[elementCount]->SetPos({ -7,0,10 });
	//m_spGrayTowering[elementCount]->SetScale(1.0f);
	//++elementCount;
	//m_spGrayTowering[elementCount]->SetPos({ -7,0,15 });
	//m_spGrayTowering[elementCount]->SetScale(1.0f);
	//elementCount = Def::SizTNull;
}

void BackGround::SetPos(const Math::Vector3& stageZeroPoint) noexcept
{
	m_mWorld.Translation(stageZeroPoint);
	std::vector<float>  parameter;
	auto counter  (Def::SizTNull);
	{
		const auto IsAssert = DATA.Load("Asset/Data/RocksParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
	}
	SetObjectProperties(m_spBlueCrystal,    parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayFlat,       parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayHeavy,      parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayProtrusion, parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGraySlanted,    parameter, counter, stageZeroPoint);
	SetObjectProperties(m_spGrayTowering,   parameter, counter, stageZeroPoint);
}

void BackGround::GenerateDepthMapFromLight()
{
	for (decltype(auto) blCr : m_spBlueCrystal)
		blCr->GenerateDepthMapFromLight();
	for (decltype(auto) grFl : m_spGrayFlat)
		grFl->GenerateDepthMapFromLight();
	for (decltype(auto) grHe : m_spGrayHeavy)
		grHe->GenerateDepthMapFromLight();
	for (decltype(auto) grPr : m_spGrayProtrusion)
		grPr->GenerateDepthMapFromLight();
	for (decltype(auto) grSl : m_spGraySlanted)
		grSl->GenerateDepthMapFromLight();
	for (decltype(auto) grTo : m_spGrayTowering)
		grTo->GenerateDepthMapFromLight();
	//for (decltype(auto) yeBu : m_spYellowBumpy)
	//	yeBu->GenerateDepthMapFromLight();
	//for (decltype(auto) yeSm : m_spYellowSmooth)
	//	yeSm->GenerateDepthMapFromLight();
	//for (auto i = Def::SizTNull; i < m_spPolygon.size(); ++i)
	//	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon[i], m_mWorldPolygon[i]);
	//for (decltype(auto) arr : m_spRock)
	//	arr->GenerateDepthMapFromLight();
}

void BackGround::DrawLit()
{
	for (decltype(auto) blCr : m_spBlueCrystal)
		blCr->DrawLit();
	for (decltype(auto) grFl : m_spGrayFlat)
		grFl->DrawLit();
	for (decltype(auto) grHe : m_spGrayHeavy)
		grHe->DrawLit();
	for (decltype(auto) grPr : m_spGrayProtrusion)
		grPr->DrawLit();
	for (decltype(auto) grSl : m_spGraySlanted)
		grSl->DrawLit();
	for (decltype(auto) grTo : m_spGrayTowering)
		grTo->DrawLit();
	//for (decltype(auto) yeBu : m_spYellowBumpy)
	//	yeBu->DrawLit();
	//for (decltype(auto) yeSm : m_spYellowSmooth)
	//	yeSm->DrawLit();
	//for (auto i = Def::SizTNull; i < m_spPolygon.size(); ++i)
	//	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon[i], m_mWorldPolygon[i]);
	//for (decltype(auto) arr : m_spRock)
	//	arr->DrawLit();
}

void BackGround::DrawBright()
{
}

void BackGround::PreUpdate()
{
}

void BackGround::Update()
{
}

void BackGround::PostUpdate()
{
}