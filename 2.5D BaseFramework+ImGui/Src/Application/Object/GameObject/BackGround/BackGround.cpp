#include "BackGround.h"
#include "BackGroundRock/BlueCrystal/BlueCrystal.hpp"
#include "BackGroundRock/GrayFlat/GrayFlat.hpp"
#include "BackGroundRock/GrayHeavy/GrayHeavy.hpp"
#include "BackGroundRock/GrayProtrusion/GrayProtrusion.hpp"
#include "BackGroundRock/GraySlanted/GraySlanted.hpp"
#include "BackGroundRock/GrayTowering/GrayTowering.hpp"
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
}

void BackGround::SetPos(const Math::Vector3& stageZeroPoint)
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
}

void BackGround::DrawBright()
{
}

void BackGround::Update()
{
}