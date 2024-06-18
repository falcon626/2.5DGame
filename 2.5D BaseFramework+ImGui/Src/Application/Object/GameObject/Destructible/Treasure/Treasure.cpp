#include "Treasure.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Data/BinaryAccessor.hpp"

Treasure::Treasure() noexcept
	: m_hp(Def::SizTNull)
	, m_interval(Def::SizTNull)
	, m_dissolve(Def::FloatNull)
	, m_dissolveSpeed(Def::FloatNull)
	, m_isBroken(false)
	, m_isCollect(false)
{ Init(); }


void Treasure::SetPos(const Math::Vector3& pos)
{
	m_dissolveSpeed = 0.01f;
	m_mWorld *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	SetScale(6.0f);
	Math::Vector3 position = { 0,1,7 };
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
	else if (m_isCollect)
	{
		m_dissolve = 0.5f;
	}
}
