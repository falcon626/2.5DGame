#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/GameObject/Stage/Stage.h"
#include "../../Object/GameObject/Creature/Player/Player.h"
#include "../../Data/BinaryAccessor.hpp"
#include "../../Data/ResourceManager.h"
#include "../../Utility/UtilityDefault.hxx"
#include "../../Utility/UtilityKey.hxx"


GameScene::GameScene() noexcept
	: m_objListLimSize(Def::SizTNull)
	, m_cameraDeg(Def::FloatNull)
	, m_stageDistance(Def::FloatNull)
	, m_stageHeight(Def::FloatNull)
	, m_stageDepth(Def::FloatNull)
{ Init(); }

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
		auto traMat = Math::Matrix::CreateTranslation(-30, 10, 0);
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

	if (!m_wpPlayer.expired())
	{
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(m_cameraPos + m_wpPlayer.lock()->GetPos());
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	if (m_objListLimSize > m_objList.size())
	{
		m_endStagePos += { m_stageDistance, m_stageHeight, m_stageDepth};
		auto stage = std::make_shared<Stage>();
		stage->Init();
		stage->AddStage();
		stage->SetPos(m_endStagePos, m_stageDistance);
		stage->SetPlayerWeakPtr(m_wpPlayer.lock());
		m_objList.push_back(stage);
	}
}

void GameScene::Init()
{	 
	LoadResources();

	KdShaderManager::Instance().WorkAmbientController().SetDirLight({0,5.0f,100.0f}, {0.5f,0,0});
	
	// Add Object
	AddObjList<Player>(m_wpPlayer);

	{
		// Local Declaration
		std::vector<float> parameter;
		auto counter (Def::SizTNull);

		{
			// Load Camera Initialization Value
			const auto IsAssert = DATA.Load("Asset/Data/CameraParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		// Set Value
		m_cameraDeg   = parameter[--counter];
		m_cameraPos.x = parameter[--counter];
		m_cameraPos.y = parameter[--counter];
		m_cameraPos.z = parameter[--counter];

		{
			// Load BackGround Initialization Value
			const auto IsAssert = DATA.Load("Asset/Data/BackGroundParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		auto stageMax    (parameter[--counter]);
		m_stageDistance = parameter[--counter];
		m_stageHeight   = parameter[--counter];
		m_stageDepth    = parameter[--counter];

		for (auto i(Def::SizTNull); i < static_cast<size_t>(stageMax); ++i)
		{
			auto stage = std::make_shared<Stage>();
			stage->Init();
			stage->AddStage(i);
			stage->SetPos({ static_cast<float>(i) * m_stageDistance, m_stageHeight, m_stageDepth }, m_stageDistance);
			stage->SetPlayerWeakPtr(m_wpPlayer.lock());
			m_objList.push_back(stage);
			m_endStagePos = stage->GetPos();
		}
	}

	if (!m_wpPlayer.expired()) m_wpPlayer.lock()->SetStageDistance(m_stageDistance);

	{
		// Initialization Camera
		m_camera    = std::make_unique<KdCamera>();
		auto rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto traMat = Math::Matrix::CreateTranslation(m_cameraPos);
		m_camera->SetCameraMatrix((rotMat * traMat));
	}
	m_objListLimSize = m_objList.size();
}

void GameScene::LoadResources()
{
	RESOURCE.PreLoadModelsData({
		"Pickaxe/pickaxe.gltf",
		"Pickaxe/superPickaxe.gltf",
		"Pickaxe/hyperPickaxe.gltf",
		"Rail/cart.gltf",
		"Crystal/purple/crystals.gltf",
		"Rock/Rock_01.gltf",
		"Rock/Rock_02.gltf",
		"Rock/Rock_03.gltf",
		"Rock/Rock_04.gltf",
		"Rock/Rock_05.gltf",
		"Crystal/biggestblue/crystalexport.gltf",
		"Treasure/Treasure_Chest.gltf"
		});

	RESOURCE.PreLoadTextures({
		"Coin/coin.png",
		"Numbers/numbers.png",
		"Numbers/numbersBox.png",
		"Ban/ban.png"
		});
}