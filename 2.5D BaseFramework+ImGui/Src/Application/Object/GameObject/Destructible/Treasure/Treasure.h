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

	void OnBreak() noexcept { m_isBroken = true; KdAudioManager::Instance().Play("Asset/Sounds/Pickaxe/swing.wav"); }
	inline auto const IsBroken() const { return m_isBroken; }

	void OnCollected() noexcept { m_isCollected = true; KdAudioManager::Instance().Play("Asset/Sounds/Collect/treasure.wav");
	}
	inline auto const IsCollected() const  { return m_isCollected; }

private:
	void Init() noexcept override { SetModelData("Treasure/Treasure_Chest.gltf"); }

	float  m_dissolve;
	float  m_dissolveSpeed;
	float  m_scale;
	float  m_scaleChange;
	bool   m_isBroken;
	bool   m_isCollected;
};