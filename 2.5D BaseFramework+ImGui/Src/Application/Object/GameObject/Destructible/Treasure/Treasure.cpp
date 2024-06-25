#include "Treasure.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Data/BinaryAccessor.hpp"

Treasure::Treasure() noexcept
	: m_dissolve(Def::FloatNull)
	, m_dissolveSpeed(Def::FloatNull)
	, m_scale(Def::FloatNull)
	, m_scaleChange(Def::FloatNull)
	, m_isBroken(false)
	, m_isCollected(false)
{ Init(); }


void Treasure::SetPos(const Math::Vector3& pos)
{
	std::vector<float> parameter;
	auto counter(Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TreasureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TreasureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_dissolveSpeed = parameter[--counter];

	m_mWorld       *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(parameter[--counter]));

	m_scale         = parameter[--counter];
	m_scaleChange   = parameter[--counter];
	SetScale(m_scale);

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);
	auto z(parameter[--counter]);
	Math::Vector3 position = { x,y,z };

	m_mWorld.Translation(position + pos);
}

void Treasure::GenerateDepthMapFromLight() noexcept
{
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	BaseExtensionObject::GenerateDepthMapFromLight();
}

void Treasure::DrawLit() noexcept
{
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	BaseExtensionObject::DrawLit();
}

void Treasure::Update()
{
	if (m_isBroken) m_dissolve += m_dissolveSpeed;
	else if (m_isCollected)
	{
		m_scale *= m_scaleChange;
		SetScale(m_scale);
	}
}
