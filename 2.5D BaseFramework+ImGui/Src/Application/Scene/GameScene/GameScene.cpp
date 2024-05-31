#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/GameObject/Creature/Player/Player.h"
#include "../../Object/GameObject/Destructible/Crystal/Crystal.h"
#include "../../Data/BinaryAccessor.hpp"
#include "../../Utility/UtilityDefault.hxx"


void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	{
		// Local Declaration
		std::vector<float> parameter;

		// Load Initialization Value
		//DATA.Load("Asset/Data/CameraParameter/Initial.dat", parameter);

		//Initialization Camera
		m_camera = std::make_unique<KdCamera>();
		auto rollMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
		auto tranMat = Math::Matrix::CreateTranslation(0, 8.0f, 0);
		m_camera->SetCameraMatrix((rollMat * tranMat));
	}
	// Add Object
	AddObjList<Player>(m_wpPlayer);
	AddObjList<Crystal>();
}