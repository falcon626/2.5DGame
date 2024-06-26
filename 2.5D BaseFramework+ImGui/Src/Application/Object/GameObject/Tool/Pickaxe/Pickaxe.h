#pragma once
#include "../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class Pickaxe :public BaseExtensionObject
{
public:

	Pickaxe() noexcept;
	virtual ~Pickaxe() noexcept override = default;

	virtual void Init      () override;
	virtual void PreUpdate () override;
	virtual void Update    () override;
	virtual void PostUpdate() override { m_mWorld = m_mScale * m_mRotation * m_mTrans; }

	void SetPos(const Math::Vector3& playerZeroPoint) override { m_mTrans.Translation(m_pos + playerZeroPoint); }
	void SetComboNum(const size_t& comboNum) noexcept { m_comboNum = comboNum; }

	void         Use()            noexcept;
	bool   const IsUsing () const noexcept;
	size_t const SwingPow() const noexcept;

private:

	// Class Or Struct Value
	Math::Matrix  m_mScale;
	Math::Matrix  m_mRotation;
	Math::Matrix  m_mTrans;
	Math::Vector3 m_pos;

	// Other Value
	size_t m_swingFrameLim;
	size_t m_swingFrame;
	size_t m_maxIntervalTime;
	size_t m_intervalTime;
	size_t m_changeIntervalTime;

	size_t m_swingMinPow;
	size_t m_swingPow;
	size_t m_changeSwingPow;

	size_t m_comboNum;
	size_t m_firstGreatUpComboNum;
	size_t m_secondGreatUpComboNum;

	float  m_rollDegX;
	float  m_rollDegZ;
	float  m_scale;
	float  m_swingSpeed;

	bool   m_isUse;
};