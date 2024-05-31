#pragma once

class Crystal;

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
		All
	};

	void Init() override;

	std::array<std::shared_ptr<KdSquarePolygon>, Surface::All> m_spPolygon;
	std::shared_ptr<Crystal> m_upCrystal;
};