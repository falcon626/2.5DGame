#pragma once

class BasePickaxe;

class PickaxeManager
{
public:
	PickaxeManager()  noexcept = default;
	~PickaxeManager() noexcept = default;

	enum class PickaxeType
	{
		Iron,
		Gold,
		Diamond
	};
	void Init() noexcept { ChangeType(m_nowPickaxeType); };

	void GenerateDepthMapFromLight();
	void DrawLit();
	void PreUpdate();
	void Update();
	void PostUpdate();

	void SetNextPickaxe(PickaxeType nextType) noexcept { m_nextPickaxeType = nextType; }

private:
	void ChangeType(PickaxeType type);

	std::shared_ptr<BasePickaxe> m_spPickaxe;
	PickaxeType m_nowPickaxeType  = PickaxeType::Iron;
	PickaxeType m_nextPickaxeType = m_nowPickaxeType;
};