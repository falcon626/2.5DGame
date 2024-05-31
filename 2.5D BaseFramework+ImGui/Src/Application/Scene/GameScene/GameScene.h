#pragma once
#include"../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	Math::Vector3 m_cameraPos;
	float m_cameraDeg;

	std::weak_ptr<Player> m_wpPlayer;
};
