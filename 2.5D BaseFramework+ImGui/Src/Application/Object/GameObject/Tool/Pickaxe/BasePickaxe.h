#pragma once
#include "../../../../Object/BaseExtensionObject/BaseExtensionObject.h"

class BasePickaxe :public BaseExtensionObject
{
public:

	BasePickaxe() noexcept;
	virtual ~BasePickaxe() noexcept override = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void PostUpdate() override { m_mWorld = m_mScale * m_mRotation * m_mTrans; }

	void SetPos(const Math::Vector3& playerZeroPoint) override { m_mTrans.Translation(m_pos + playerZeroPoint); }

	void Use() noexcept;
	bool   const IsUsing () const noexcept;
	size_t const SwingPow() const noexcept;

protected:

	// Constan Value
	const std::string TemplateDataPath  = "Asset/Data/PickaxeParameter/";
	const std::string TemplateModelPath = "Pickaxe/";

	// Other Value
	bool   m_isUse;
	size_t m_intervalTime;
	size_t m_swingPow;
	float  m_swingSpeed;
private:

	// Class Or Struct Value
	Math::Matrix  m_mScale;
	Math::Matrix  m_mRotation;
	Math::Matrix  m_mTrans;
	Math::Vector3 m_pos;

	// Other Value
	size_t m_swingTime;
	size_t m_swingFrame;
	float  m_rollDegX;
	float  m_rollDegZ;
	float  m_scale;
};