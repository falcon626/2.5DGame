#pragma once

class BasePickaxe;

class PickaxeManager
{
public:
	PickaxeManager () noexcept = default;
	~PickaxeManager() noexcept = default;

	enum class PickaxeType : size_t
	{
		Iron,
		Gold,
		Diamond
	};
	void Init() noexcept { ChangeType(m_nowPickaxeType); };

	void GenerateDepthMapFromLight() noexcept;
	void DrawLit() noexcept;
	void PreUpdate() noexcept;
	void Update() noexcept;
	void PostUpdate() noexcept;

	void         SetPos(const Math::Vector3& playerZeroPoint) noexcept;
	void         Use() noexcept;
	bool   const IsUsing () const noexcept;
	size_t const SwingPow() const noexcept;

	void SetNextPickaxe(PickaxeType nextType) noexcept { m_nextPickaxeType = nextType; }

private:
	void ChangeType(PickaxeType type) noexcept;

	std::shared_ptr<BasePickaxe> m_spPickaxe;
	PickaxeType m_nowPickaxeType  = PickaxeType::Iron;
	PickaxeType m_nextPickaxeType = m_nowPickaxeType;
};