#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Treasure :public BaseExtensionObject
{
public:
	Treasure ()noexcept;
	~Treasure()noexcept override = default;

	void GenerateDepthMapFromLight() noexcept override;
	void DrawLit() noexcept override;
	void Update()  override;

	void SetPos(const Math::Vector3& pos) override;

	void OnBreak() noexcept { m_isBroken = true; }
	inline auto const IsBroken() const { return m_isBroken; }

	void OnCollect() noexcept { m_isCollect = true; }
	inline auto const IsCollect() const  { return m_isCollect; }

private:
	void Init() noexcept override { SetModelData("Treasure/Treasure_Chest.gltf"); }

	size_t      m_hp;
	size_t      m_interval;
	float       m_dissolve;
	float       m_dissolveSpeed;
	bool        m_isBroken;
	bool        m_isCollect;
};