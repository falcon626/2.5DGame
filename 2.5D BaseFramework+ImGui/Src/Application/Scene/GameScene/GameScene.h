#pragma once
#include"../BaseScene/BaseScene.h"

class Player;
class Stage;

class GameScene : public BaseScene
{
public :

	GameScene () noexcept;
	~GameScene() noexcept override = default;

private:

	void Event() override;
	void Init() override;

	void LoadResources() override;

	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector3 m_cameraPos;
	Math::Vector3 m_endStagePos;

	size_t m_objListLimSize;
	float  m_cameraDeg;
	float  m_stageDistance;
	float  m_stageHeight;
	float  m_stageDepth;
};
