#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/GameObject/BackGround/BackGround.h"
#include "../../Object/GameObject/Creature/Player/Player.h"
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
		auto counter = Def::SizTNull;

		{
			// Load Initialization Value
			const auto IsAssert = DATA.Load("Asset/Data/CameraParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		// Set Value
		m_cameraDeg   = parameter[--counter];
		m_cameraPos.x = parameter[--counter];
		m_cameraPos.y = parameter[--counter];
		m_cameraPos.z = parameter[--counter];
	}

	{
		//Initialization Camera
		m_camera = std::make_unique<KdCamera>();
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(m_cameraPos);
		m_camera->SetCameraMatrix((rotMat * traMat));

	}

	// Add Object
	AddObjList<BackGround>();
	AddObjList<Player>(m_wpPlayer);
}