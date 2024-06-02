#pragma once

class Crystal;
class BackGroundRock;

class BackGround :public KdGameObject
{
public:
	BackGround() { Init(); }
	~BackGround() noexcept override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;
	void DrawBright() override;
	void PreUpdate() override;
	void Update()override;
	void PostUpdate() override;
private:

	enum Surface
	{
		Top,
		Bottom,
		Front,
		Back,
		AllSurface
	};

	enum RockPattern
	{
		First,
		Second,
		Third,
		Fourth,
		Fifth,
		AllPattern
	};

	void Init() override;

	std::array<std::shared_ptr<KdSquarePolygon>, Surface::AllSurface> m_spPolygon;
	std::array<Math::Matrix, Surface::AllSurface> m_mWorldPolygon;
	std::shared_ptr<Crystal> m_spCrystal;
	std::array<std::shared_ptr<BackGroundRock>, RockPattern::AllPattern> m_spRock;
};