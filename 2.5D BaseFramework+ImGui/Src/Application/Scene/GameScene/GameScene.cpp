#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/GameObject/BackGround/BackGround.h"
#include "../../Object/GameObject/Destructible/Crystal/Crystal.h"
#include "../../Object/GameObject/Creature/Player/Player.h"
#include "../../Data/BinaryAccessor.hpp"
#include "../../Utility/UtilityDefault.hxx"
#include "../../Utility/UtilityKey.hxx"


void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
	if (Key::IsPushing(Key::Up))
	{
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(m_cameraPos);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	if (Key::IsPushing(Key::Left))
	{
		auto rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
		auto traMat = Math::Matrix::CreateTranslation(-30,10,0);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	if (Key::IsPushing(Key::Right))
	{
		auto rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(270));
		auto traMat = Math::Matrix::CreateTranslation(30, 10, 0);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	static Math::Vector3 pos = m_cameraPos;
	if (Key::IsPushing(Key::A))
	{
		pos.x -= 0.5f;
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(pos);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}

	if (Key::IsPushing(Key::D))
	{
		pos.x += 0.5f;
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(pos);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	if (Key::IsPushing(Key::Q))
	{
		AddObjList<Crystal>();
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
		// Initialization Camera
		m_camera = std::make_unique<KdCamera>();
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(m_cameraPos);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}

	// Add Object
	AddObjList<BackGround>();
	AddObjList<Crystal>();
	AddObjList<Player>(m_wpPlayer);
}