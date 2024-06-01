#pragma once

class BackGroundRock : public KdGameObject
{
public:
	BackGroundRock() noexcept = default;
	~BackGroundRock() noexcept override = default;

	void Init() override;
	void GenerateDepthMapFromLight() override;
	void DrawLit() override;
	void Update() override;
	void PostUpdate() override;

private:

	enum RockType
	{
		YelSmooth,
		YelBumpy,
		GraHeavy,
		GraSlanted,
		GraTowering,
		GraProtrusion,
		GraFlat,
		Crystal
	};

	std::shared_ptr<KdModelData> m_spModel;
};