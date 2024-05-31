#pragma once

class Hammer : public KdGameObject
{
public:
	Hammer();
	~Hammer() override{}

	void Init()override;
	void SetModel(const std::string& path);
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Update()override;

private:

};