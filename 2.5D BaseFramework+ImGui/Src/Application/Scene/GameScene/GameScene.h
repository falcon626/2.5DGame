#pragma once
#include "../BaseScene/BaseScene.h"

class Player;
class GameUi;

class GameScene : public BaseScene
{
public :

	GameScene (const ModeFlg& mode) noexcept;
	~GameScene() noexcept override = default;

private:

	void Event() override;
	void Init() override;

	void LoadResources() noexcept override;

	std::weak_ptr<Player> m_wpPlayer;
	std::weak_ptr<GameUi> m_wpGameUi;

	Math::Vector3 m_cameraPos;
	Math::Vector3 m_endStagePos;
	Math::Vector3 m_lightStrength;

	ModeFlg m_mode;
	size_t  m_objListLimSize;
	float   m_cameraDeg;
	float   m_stageDistance;
	float   m_stageHeight;
	float   m_stageDepth;
	float   m_minWidthRange;
	float   m_maxWidthRange;
	float   m_minHighRange;
	float   m_maxHighRange;
	float   m_lightZ;
	bool    m_isClear;
};
