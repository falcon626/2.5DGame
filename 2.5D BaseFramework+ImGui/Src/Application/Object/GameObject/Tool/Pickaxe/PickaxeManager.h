#pragma once

class BasePickaxe;

class PickaxeManager
{
public:
	PickaxeManager() = default;
	~PickaxeManager() = default;

	enum class PickaxeType
	{
		Iron,
		Gold,
		Diamond
	};
	void Init(){ ChangeType(m_nowPickaxeType); };

	void GenerateDepthMapFromLight();
	void DrawLit();
	void PreUpdate();
	void Update();
	void PostUpdate();

private:
	void ChangeType(PickaxeType type);

	std::shared_ptr<BasePickaxe> m_spPickaxe;
	PickaxeType m_nowPickaxeType = PickaxeType::Iron;
	PickaxeType m_nextPickaxeType = m_nowPickaxeType;
};