#pragma once

class Crystal : public KdGameObject
{
public:
	Crystal() { Init(); }
	~Crystal() override {}

	void DrawLit()override;
	void Update()override;

private:
	void Init()override;
	std::shared_ptr<KdModelData> m_spModel;
};