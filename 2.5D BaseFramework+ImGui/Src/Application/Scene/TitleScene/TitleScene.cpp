#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Data/ResourceManager.h"
#include "../../Data/BinaryAccessor.hpp"
#include "../../Utility/UtilityKey.hxx"
#include "../../Object/TitleObject/TitleBar/TitleBar.h"
#include "../../Object/TitleObject/TitleHelp/TitleHelp.h"
#include "../../Object/TitleObject/BackGround/Rock/Rock.h"
#include "../../Object/TitleObject/BackGround/Pickaxe/OrnamentPickaxe.h"
#include "../../Object/TitleObject/SelectMode/SelectMode.h"

void TitleScene::Event()
{
	if ((Key::IsPushing(Key::SideL_Click) || Key::IsPushing(Key::Space)) && !m_wpSelectMode.expired())
	{
		auto mode(m_wpSelectMode.lock()->GetMode());

		if      (mode == static_cast<size_t>(SelectMode::GameMode::Practice))
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::GamePractice);

		else if (mode == static_cast<size_t>(SelectMode::GameMode::Survival))
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::GameSurvival);

		else if (mode == static_cast<size_t>(SelectMode::GameMode::TimeAttack))
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::GameTimeAttack);

		else if (mode == static_cast<size_t>(SelectMode::GameMode::TimeLimit))
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::GameTimeLimit);

		KdAudioManager::Instance().Play("Asset/Sounds/Pickaxe/swing.wav");
	}
}

void TitleScene::Init()
{
	LoadResources();

	AddObjList<TitleBar>();
	AddObjList<TitleHelp>();
	AddObjList<Rock>();
	AddObjList<OrnamentPickaxe>();
	AddObjList<SelectMode>(m_wpSelectMode);

	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TitleSceneParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TitleSceneParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);
	auto z(parameter[--counter]);

	auto r(parameter[--counter]);
	auto g(parameter[--counter]);
	auto b(parameter[--counter]);

	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ x,y,z }, { r,g,b });

	x = parameter[--counter];
	y = parameter[--counter];
	z = parameter[--counter];

	m_camera = std::make_unique<KdCamera>();
	auto mRot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(parameter[--counter]));
	auto mTra = Math::Matrix::CreateTranslation({x,y,z});
	m_camera->SetCameraMatrix((mRot * mTra));
}

void TitleScene::LoadResources() noexcept
{
	RESOURCE.PreLoadModelsData({
		"Pickaxe/pickaxe.gltf",
		"Rock/Rock_05.gltf"
		});
	RESOURCE.PreLoadTextures({
		"Texts/miner.png",
		"Texts/titleHelp.png",
		"Texts/practice.png",
		"Texts/survival.png",
		"Texts/timeAttack.png",
		"Texts/timeLimit.png"
		});
}