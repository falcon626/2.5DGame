#include "BasePickaxe.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Utility/UtilityKey.hxx"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../Data/ResourceManager.h"


BasePickaxe::BasePickaxe() noexcept
	: m_isUse(false)
	, m_intervalTime(Def::IntNull)
	, m_swingPow(Def::IntNull)
	, m_swingSpeed(Def::IntNull)
	, m_mScale(Def::Mat)
	, m_mRotation(Def::Mat)
	, m_mTrans(Def::Mat)
	, m_pos(Def::Vec)
	, m_swingTime(Def::IntNull)
	, m_swingFrame(Def::IntNull)
	, m_rollDegX(Def::FloatNull)
	, m_rollDegZ(Def::FloatNull)
	, m_scale(Def::FloatNull)
{}

void BasePickaxe::Init()
{
	{
		// Local Declaration
		auto counter = Def::SizTNull;
		std::vector<float> parameter;

		{
			// Load Initialization Value
			const auto IsAssert = DATA.Load(TemplateDataPath + "Common_Denominator_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		// Set Value
		m_rollDegX   = parameter[--counter];
		m_pos.x      = parameter[--counter];
		m_pos.y      = parameter[--counter];
		m_pos.z      = parameter[--counter];
		m_swingSpeed = parameter[--counter];
		m_scale      = parameter[--counter];
		m_swingTime  = static_cast<size_t>(parameter[--counter]);
	}

	// Set Object
	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rollDegX));
	m_mTrans    = Math::Matrix::CreateTranslation(m_pos);
	m_mScale    = Math::Matrix::CreateScale(m_scale);
	m_mWorld    = m_mScale * m_mRotation * m_mTrans;
}

void BasePickaxe::Update()
{
	if (!m_isUse) return;
	if (m_swingTime > m_swingFrame) m_mRotation *= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_swingSpeed));
	else if (m_swingTime > m_swingFrame - m_swingTime) m_mRotation *= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-m_swingSpeed));
	if (m_intervalTime < m_swingFrame) m_isUse = false;
	++m_swingFrame;
}

void BasePickaxe::PostUpdate()
{
	m_mWorld = m_mScale * m_mRotation * m_mTrans;
}

void BasePickaxe::Use()
{
	if (!(Key::IsPushing(Key::L_Click)) || m_isUse) return;
	m_isUse = true;
	m_swingFrame = Def::IntNull;
}
