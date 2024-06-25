#pragma once

class Player;
class GameUi;
class BackGround;
class Crystal;
class Treasure;

class Stage : public KdGameObject
{
public:
	Stage ()noexcept;
	~Stage()noexcept override = default;

	void Init()                      override;
	void GenerateDepthMapFromLight() override;
	void DrawLit()                   override;
	void PreUpdate()                 override;
	void Update()                    override;

	// Select Stage
	void AddStage(const size_t& pattern);
	// Random Stage
	void AddStage();

	// Player And GameUi Set WeakPtr
	void SetWeakPtr(const std::shared_ptr<Player>& spPlayer, const std::shared_ptr<GameUi>& spGameUi) noexcept;
	
	void SetNowComboNum();
	void SetPos(const Math::Vector3& pos, const float& stageDistance);

private:
	enum class StageType : size_t
	{
		None,
		Crystal,
		Treasure,
		All
	};

	void TargetCrystal (const std::shared_ptr<Player>& player) noexcept;
	void TargetTreasure(const std::shared_ptr<Player>& player) noexcept;

	std::shared_ptr<BackGround> m_spBackGround;
	std::shared_ptr<Crystal>    m_spCrystal;
	std::shared_ptr<Treasure>   m_spTreasure;

	std::weak_ptr<Player> m_wpPlayer;
	std::weak_ptr<GameUi> m_wpGameUi;

	size_t m_stageType;
	size_t m_maxPercentage;
	size_t m_crystalPopPercentage;
	float  m_stageDistance;
	bool   m_isAction;
};