#include "Pickaxe.h"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Utility/UtilityKey.hxx"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../Data/ResourceManager.h"


Pickaxe::Pickaxe() noexcept
	: m_swingFrameLim         (Def::SizTNull)
	, m_swingFrame            (Def::SizTNull)
	, m_maxIntervalTime       (Def::SizTNull)
	, m_intervalTime          (Def::SizTNull)
	, m_changeIntervalTime    (Def::SizTNull)
	, m_swingMinPow           (Def::SizTNull)
	, m_swingPow              (Def::SizTNull)
	, m_changeSwingPow        (Def::SizTNull)
	, m_comboNum              (Def::SizTNull)
	, m_firstGreatUpComboNum  (Def::SizTNull)
	, m_secondGreatUpComboNum (Def::SizTNull)
	, m_rollDegX              (Def::FloatNull)
	, m_rollDegZ              (Def::FloatNull)
	, m_scale                 (Def::FloatNull)
	, m_swingSpeed            (Def::FloatNull)
	, m_isUse                 (false)
{}

void Pickaxe::Init()
{
	{
		// Local Declaration
		std::vector<float> parameter;
		auto counter (Def::SizTNull);

		{
			// Load Initialization Value
#if _DEBUG
			const auto IsAssert = DATA.Load("Asset/Data/PickaxeParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
			DATA.Load("Asset/Data/PickaxeParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
		}

		// Set Value
		m_rollDegX              = parameter[--counter];
		m_pos.x                 = parameter[--counter];
		m_pos.y                 = parameter[--counter];
		m_pos.z                 = parameter[--counter];
		m_swingSpeed            = parameter[--counter];
		m_scale                 = parameter[--counter];
		m_swingFrameLim         = static_cast<size_t>(parameter[--counter]);
		m_intervalTime          = static_cast<size_t>(parameter[--counter]);
		m_swingPow              = static_cast<size_t>(parameter[--counter]);
		m_changeIntervalTime    = static_cast<size_t>(parameter[--counter]);
		m_changeSwingPow        = static_cast<size_t>(parameter[--counter]);
		m_firstGreatUpComboNum  = static_cast<size_t>(parameter[--counter]);
		m_secondGreatUpComboNum = static_cast<size_t>(parameter[--counter]);
	}

	m_maxIntervalTime = m_intervalTime;
	m_swingMinPow     = m_swingPow;

	// Load Model
	SetModelData("Pickaxe/pickaxe.gltf");

	// Set Object
	m_mScale    = Math::Matrix::CreateScale(m_scale);
	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rollDegX));
	m_mTrans    = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld    = m_mScale * m_mRotation * m_mTrans;
}

void Pickaxe::PreUpdate()
{
	if (m_comboNum > m_firstGreatUpComboNum && m_comboNum < m_secondGreatUpComboNum)
	{
		m_swingPow     = m_swingMinPow     + m_changeSwingPow;
		m_intervalTime = m_maxIntervalTime - m_changeIntervalTime;
	}
	else if (m_comboNum >= m_secondGreatUpComboNum)
	{
		m_swingPow     = m_swingMinPow     + m_changeSwingPow     + m_changeSwingPow;
		m_intervalTime = m_maxIntervalTime - m_changeIntervalTime - m_changeIntervalTime;
	}
	else
	{
		m_swingPow     = m_swingMinPow;
		m_intervalTime = m_maxIntervalTime;
	}
}

void Pickaxe::Update()
{
	if (!m_isUse) return;
	if (m_swingFrameLim > m_swingFrame) m_mRotation *= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_swingSpeed));
	else if (m_swingFrameLim > m_swingFrame - m_swingFrameLim) m_mRotation *= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-m_swingSpeed));
	if (m_intervalTime < m_swingFrame) m_isUse = false;
	++m_swingFrame;
}

void Pickaxe::Use() noexcept
{
	if ((!(Key::IsPushing(Key::L_Click)) && !(Key::IsPushing(Key::Q))) || m_isUse) return;
	m_isUse      = true;
	m_swingFrame = Def::SizTNull;
}

bool const Pickaxe::IsUsing() const noexcept
{
	return m_isUse;
}

size_t const Pickaxe::SwingPow() const noexcept
{
	return m_swingPow;
}
