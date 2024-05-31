#pragma once

class PickaxeManager;

class Player : public KdGameObject
{
public:
	Player() { Init(); };
	~Player() = default;


	void GenerateDepthMapFromLight() override;
	void DrawLit() override;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_spModel;
	std::shared_ptr<PickaxeManager> m_spPickaxe;
};