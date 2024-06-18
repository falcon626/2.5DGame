#include "Crystal.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Data/BinaryAccessor.hpp"


Crystal::Crystal() noexcept
	: m_hp(Def::IntNull)
	, m_interval(Def::SizTNull)
	, m_dissolve(Def::FloatNull)
	, m_dissolveDamageEffect(Def::FloatNull)
	, m_dissolveSpeed(Def::FloatNull)
	, m_isBroken(false)
	, m_isHit(false)
{ Init(); }

void Crystal::SetPos(const Math::Vector3& pos)
{
	std::vector<float> parameter;
	auto counter (Def::SizTNull);
	auto correctionPos(Def::Vec);
	auto scale  (Def::FloatNull);

	{
		const auto IsAssert = DATA.Load("Asset/Data/CrystalParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
	}

	m_hp                   = static_cast<size_t>(parameter[--counter]);
	m_intervalLim          = static_cast<size_t>(parameter[--counter]);
	m_dissolveDamageEffect = parameter[--counter];
	m_dissolveSpeed        = parameter[--counter];
	scale                  = parameter[--counter];
	correctionPos.x        = parameter[--counter];
	correctionPos.y        = parameter[--counter];
	correctionPos.z        = parameter[--counter];

	SetScale(scale);
	m_mWorld.Translation(pos + correctionPos);
}

void Crystal::GenerateDepthMapFromLight() noexcept
{
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	BaseExtensionObject::GenerateDepthMapFromLight();
}

void Crystal::DrawLit() noexcept
{
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	BaseExtensionObject::DrawLit();
}

void Crystal::Update()
{
	if (m_isBroken)
	{
		m_dissolve += m_dissolveSpeed;
	}

	else if (m_isHit)
	{
		++m_interval;
		m_dissolve = m_dissolveDamageEffect;
	}
	if (m_isHit && m_interval > m_intervalLim)
	{
		m_isHit    = false;
		m_interval = Def::SizTNull;
		m_dissolve = Def::FloatNull;
	}
}

void Crystal::OnBreak(const size_t& pow) noexcept
{
	m_hp        -= pow;
	if (m_hp    <= Def::SizTNull) m_isBroken = true;
	else m_isHit = true;
}
