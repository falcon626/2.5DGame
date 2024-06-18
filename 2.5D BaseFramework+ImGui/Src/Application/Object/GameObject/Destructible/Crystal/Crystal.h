#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Crystal : public BaseExtensionObject
{
public:
	Crystal () noexcept;
	~Crystal() noexcept override = default;


	void GenerateDepthMapFromLight() noexcept override;
	void DrawLit() noexcept override;
	void Update()  override;
	
	void OnBreak(const size_t& pow) noexcept;
	inline auto const IsBroken() const { return m_isBroken; }

	void SetPos(const Math::Vector3& pos) override;

private:
	void Init() noexcept override { SetModelData("Crystal/purple/crystals.gltf"); }

	size_t      m_hp;
	size_t      m_interval;
	size_t      m_intervalLim;
	float       m_dissolve;
	float       m_dissolveDamageEffect;
	float       m_dissolveSpeed;
	bool        m_isBroken;
	bool        m_isHit;
};