#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/GameObject/GameUi/GameUi.h"
#include "../../Object/GameObject/Stage/Stage.h"
#include "../../Object/GameObject/Creature/Player/Player.h"
#include "../../Object/GameObject/TotalizationResult/TotalizationResult.h"
#include "../../Data/BinaryAccessor.hpp"
#include "../../Data/ResourceManager.h"
#include "../../Utility/UtilityDefault.hxx"
#include "../../Utility/UtilityMath.hxx"
#include "../../Utility/UtilityKey.hxx"


GameScene::GameScene(const ModeFlg& mode) noexcept
	: m_mode          (mode)
	, m_objListLimSize(Def::SizTNull)
	, m_cameraDeg     (Def::FloatNull)
	, m_stageDistance (Def::FloatNull)
	, m_stageHeight   (Def::FloatNull)
	, m_stageDepth    (Def::FloatNull)
	, m_minWidthRange (Def::FloatNull)
	, m_maxWidthRange (Def::FloatNull)
	, m_minHighRange  (Def::FloatNull)
	, m_maxHighRange  (Def::FloatNull)
	, m_lightZ        (Def::FloatNull)
	, m_isClear       (false)
{ Init(); }

void GameScene::Event()
{
	if (Key::IsPushing(Key::Wheel_Click) || Key::IsPushing(Key::Shift)) SceneManager::Instance().SetNextScene (SceneManager::SceneType::Title);

	if (!m_wpPlayer.expired())
	{
		auto player = m_wpPlayer.lock();

		auto mRot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto mTra = Math::Matrix::CreateTranslation(m_cameraPos + player->GetPos());
		m_camera->SetCameraMatrix((mRot * mTra));

		if (m_objListLimSize > m_objList.size() && !m_wpGameUi.expired())
		{
			m_endStagePos += { m_stageDistance, m_stageHeight, m_stageDepth};
			auto stage = std::make_shared<Stage>();
			stage->Init();
			stage->AddStage();
			stage->SetPos(m_endStagePos, m_stageDistance);
			stage->SetWeakPtr(player, m_wpGameUi.lock());
			m_objList.push_back(stage);
		}
	
		if (!m_wpGameUi.expired() && !m_isClear)
		{
			auto result(m_wpGameUi.lock());
			if ((result->IsTired() || result->IsComboOver() || result->IsLimitOver()) && !player->IsMoveing())
			{
				auto survival(false), timeAttack(false), timeLimit(false);

				switch (m_mode)
				{
				case BaseScene::ModeFlg::Survival:
					survival = true;
					break;
				case BaseScene::ModeFlg::TimeAttack:
					timeAttack = true;
					break;
				case BaseScene::ModeFlg::TimeLimit:
					timeLimit = true;
					break;
				}

				AddObjList<TotalizationResult>(survival,timeAttack,timeLimit,
					result->GetMaxCombo(),result->GetTime(),result->GetScore(),player->GetPos());

				m_isClear = true;
			}
		}
	}

	auto x(Formula::Rand(m_minWidthRange, m_maxWidthRange));
	auto y(Formula::Rand(m_minHighRange,  m_maxHighRange));

	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ x,y,m_lightZ }, m_lightStrength);
}

void GameScene::Init()
{
	LoadResources();

	// Add Object
	AddObjList<Player>(m_wpPlayer);
	AddObjList<GameUi>(m_wpGameUi);

	{
		// Local Declaration
		std::vector<float> parameter;
		auto counter(Def::SizTNull);

		{
			// Load Camera Initialization Value
#if _DEBUG
			const auto IsAssert = DATA.Load("Asset/Data/CameraParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
			DATA.Load("Asset/Data/CameraParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
		}

		// Set Value
		m_cameraDeg   = parameter[--counter];
		m_cameraPos.x = parameter[--counter];
		m_cameraPos.y = parameter[--counter];
		m_cameraPos.z = parameter[--counter];

		{
			// Load BackGround Initialization Value
#if _DEBUG
			const auto IsAssert = DATA.Load("Asset/Data/BackGroundParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
			DATA.Load("Asset/Data/BackGroundParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
		}

		auto stageMax(parameter[--counter]);
		m_stageDistance = parameter[--counter];
		m_stageHeight   = parameter[--counter];
		m_stageDepth    = parameter[--counter];

		for (auto i(Def::SizTNull); i < static_cast<size_t>(stageMax); ++i)
		{
			auto stage = std::make_shared<Stage>();
			stage->Init();
			stage->AddStage(i);
			stage->SetPos({ static_cast<float>(i) * m_stageDistance, m_stageHeight, m_stageDepth }, m_stageDistance);
			stage->SetWeakPtr(m_wpPlayer.lock(), m_wpGameUi.lock());
			m_objList.push_back(stage);
			m_endStagePos = stage->GetPos();
		}

		{
			// Load Light Initialization Value
#if _DEBUG
			const auto IsAssert = DATA.Load("Asset/Data/StageLightParameter/Initial_Float.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
			DATA.Load("Asset/Data/StageLightParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
		}

		auto r(parameter[--counter]);
		auto g(parameter[--counter]);
		auto b(parameter[--counter]);

		m_lightStrength = { r,g,b };

		m_minWidthRange = parameter[--counter];
		m_maxWidthRange = parameter[--counter];

		m_minHighRange  = parameter[--counter];
		m_maxHighRange  = parameter[--counter];

		m_lightZ        = parameter[--counter];
	}

	if (!m_wpPlayer.expired()) m_wpPlayer.lock()->SetStageDistance(m_stageDistance);

	{
		// Initialization Camera
		m_camera = std::make_unique<KdCamera>();
		auto mRot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_cameraDeg));
		auto mTra = Math::Matrix::CreateTranslation(m_cameraPos);
		m_camera->SetCameraMatrix((mRot * mTra));
	}
	m_objListLimSize = m_objList.size();

	if (!m_wpGameUi.expired() && !m_wpPlayer.expired())
	{
		switch (m_mode)
		{
		case BaseScene::ModeFlg::Practice:
			m_wpGameUi.lock()->SetModePractice();
			break;
		case BaseScene::ModeFlg::Survival:
			m_wpGameUi.lock()->SetModeSurvival();
			break;
		case BaseScene::ModeFlg::TimeAttack:
			m_wpGameUi.lock()->SetModeTimeAttack();
			break;
		case BaseScene::ModeFlg::TimeLimit:
			m_wpGameUi.lock()->SetModeTimeLimit();
			break;
		}
	}
}

void GameScene::LoadResources() noexcept
{
	RESOURCE.PreLoadModelsData({
		"Pickaxe/pickaxe.gltf",
		"Pickaxe/superPickaxe.gltf",
		"Pickaxe/hyperPickaxe.gltf",
		"Cart/cart.gltf",
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
		"Ban/ban.png",
		"Gauge/gauge.png"
		});
}