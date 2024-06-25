﻿#include "TotalizationResult.h"
#include "../../../Utility/UtilityDefault.hxx"
#include "../../../Utility/UtilityKey.hxx"
#include "../../../Utility/UtilityMath.hxx"
#include "../../../Data/ResourceManager.h"
#include "../../../Data/BinaryAccessor.hpp"

TotalizationResult::TotalizationResult(const bool& isModeSurvival, const bool& isModeTimeAttack, const bool& isModeTimeLimit,
	const size_t& maxCombo, const size_t& time, const size_t& score, const Math::Vector3& pos) noexcept
	: m_pos              (pos)
	, m_maxCombo         (maxCombo)
	, m_time             (time)
	, m_score            (score)
	, m_maxPercentage       (Def::SizTNull)
	, m_randomization       (Def::SizTNull)
	, m_rotX                (Def::FloatNull)
	, m_rotY                (Def::FloatNull)
	, m_rotZ                (Def::FloatNull)
	, m_rotSpeed            (Def::FloatNull)
	, m_maxRot              (Def::FloatNull)
	, m_coefficient         (Def::FloatNull)
	, m_scale               (Def::FloatNull)
	, m_isModeSurvival   (isModeSurvival)
	, m_isModeTimeAttack (isModeTimeAttack)
	, m_isModeTimeLimit  (isModeTimeLimit)
{ Init(); }

void TotalizationResult::Init()
{
	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TotalizationResultParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TotalizationResultParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_rotSpeed    = parameter[--counter];
	m_maxRot      = parameter[--counter];
	m_coefficient = parameter[--counter];
	m_scale       = parameter[--counter];

	auto survivalSilverBorder   = parameter[--counter];
	auto survivalGoldBorder     = parameter[--counter];

	auto timeAttackComboBorder  = static_cast<size_t>      (parameter[--counter]);
	auto timeAttackBronzeBorder = static_cast<unsigned int>(parameter[--counter]);
	auto timeAttackSilverBorder = static_cast<unsigned int>(parameter[--counter]);

	auto timeLimitTimeBorder    = static_cast<size_t>(parameter[--counter]);
	auto timeLimitGoldBorder    = static_cast<size_t>(parameter[--counter]);
	auto timeLimitSilverBorder  = static_cast<size_t>(parameter[--counter]);

	if (m_isModeSurvival)
	{
		auto result((m_score / m_time) * (m_maxCombo * m_coefficient));

		if (result >= survivalGoldBorder) AwardGold();

		else if (result >= survivalSilverBorder) AwardSilver();

		else AwardBronze();
	}

	else if (m_isModeTimeAttack)
	{
		if (m_maxCombo < timeAttackComboBorder)    AwardBronze();

		auto result(m_time + (m_score - m_maxCombo));

		if (result >= timeAttackBronzeBorder)      AwardBronze();

		else if (result >= timeAttackSilverBorder) AwardSilver();

		else AwardGold();
	}

	else if (m_isModeTimeLimit)
	{
		if (m_time > timeLimitTimeBorder) AwardBronze();

		auto result(m_maxCombo);
		if (result >= timeLimitGoldBorder) AwardGold();

		else if (result >= timeLimitSilverBorder) AwardSilver();

		else AwardBronze();
	}
}

void TotalizationResult::Update()
{
	m_rotY += m_rotSpeed;
	if (m_rotY > m_maxRot) m_rotY -= m_maxRot;

	m_mWorld =
		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45.0f))*
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotY))*
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(3.00f));

	auto pos(m_pos + Math::Vector3(0, 6.5f, 2));
	SetScale(m_scale);
	SetPos(pos);
}