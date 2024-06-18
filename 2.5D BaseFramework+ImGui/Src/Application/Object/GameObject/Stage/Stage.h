#pragma once

class Player;
class BackGround;
class Crystal;
class Treasure;

class Stage : public KdGameObject
{
public:
	Stage ()noexcept;
	~Stage()noexcept override = default;

	void Init()       override;
	void GenerateDepthMapFromLight() override;
	void DrawLit()    override;
	void DrawBright() override;
	void Update()     override;

	void AddStage(const size_t& pattern);
	void AddStage();
	void SetPlayerWeakPtr(const std::shared_ptr<Player>& spPplayer) noexcept { m_wpPlayer = spPplayer; }
	void SetPos(const Math::Vector3& pos, const float& stageDistance);

private:
	enum class StageType
	{
		None,
		Crystal,
		Treasure,
		All
	};

	std::shared_ptr<BackGround> m_spBackGround;
	std::shared_ptr<Crystal>    m_spCrystal;
	std::shared_ptr<Treasure>   m_spTreasure;

	std::weak_ptr<Player> m_wpPlayer;

	size_t m_stageType;
	float m_stageDistance;
	bool m_isAction;
};