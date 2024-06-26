#include "SceneManager.h"

#include "../Utility/UtilityKey.hxx"
#include "../Data/ResourceManager.h"
#include "../Data/BinaryAccessor.hpp"

#include "BaseScene/BaseScene.h"
#include "GameScene/GameScene.h"
#include "TitleScene/TitleScene.h"

void SceneManager::Init()
{
	// 開始シーンに切り替え
	ChangeScene(m_currentSceneType);

	m_spSoundTex = std::make_shared<KdTexture>();
	m_spSoundTex->Load("Asset/Textures/Sound/sound.png");

	// Local Declaration
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/SoundParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/SoundParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_masterVolume  = parameter[--counter];
	m_changeVol     = parameter[--counter];

	m_soundTexPos.x = parameter[--counter];
	m_soundTexPos.y = parameter[--counter];

	KdAudioManager::Instance().Play("Asset/Sounds/Stage/torch.wav", true);
}

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();

	SoundUpdate();
}

void SceneManager::SoundUpdate() noexcept
{
	if (Key::IsPushing(Key::Up))
	{
		if (!m_volUpKeyFlg)
		{
			m_masterVolume += m_changeVol;
			m_volUpKeyFlg   = true;
		}
	}
	else m_volUpKeyFlg = false;

	if (Key::IsPushing(Key::Down))
	{
		if (!m_volDownKeyFlg)
		{
			m_masterVolume -= m_changeVol;
			if (m_masterVolume < static_cast<float>(NULL)) m_masterVolume = static_cast<float>(NULL);
			m_volDownKeyFlg = true;
		}
	}
	else m_volDownKeyFlg = false;

	if (Key::IsPushing(Key::M))
	{
		if (!m_volMuteKeyFlg)
		{
			m_muteFlg       = !m_muteFlg;
			m_volMuteKeyFlg = true;
		}
	}
	else m_volMuteKeyFlg = false;

	if (m_muteFlg) KdAudioManager::Instance().SetVolume(static_cast<float>(NULL));
	else           KdAudioManager::Instance().SetVolume(m_masterVolume);
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();

	SoundSpriteDraw();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

void SceneManager::SoundSpriteDraw() noexcept
{
	m_soundTexRect =
	{ static_cast<long>(NULL), static_cast<long>(NULL),
	  static_cast<long> (m_spSoundTex->GetWidth() / SoundType::TypeMax), static_cast<long>(m_spSoundTex->GetHeight()) };

	if      (m_volDownKeyFlg) m_soundTexRect.x = static_cast<long>((m_spSoundTex->GetWidth() / SoundType::TypeMax) * SoundType::VolumeDown);

	else if (m_volUpKeyFlg)   m_soundTexRect.x = static_cast<long>((m_spSoundTex->GetWidth() / SoundType::TypeMax) * SoundType::VolumeUp);

	else if (m_muteFlg || m_masterVolume <= static_cast<float>(NULL)) m_soundTexRect.x = static_cast<long>((m_spSoundTex->GetWidth() / SoundType::TypeMax) * SoundType::VolumeMute);

	else m_soundTexRect.x = static_cast<long>((m_spSoundTex->GetWidth() / SoundType::TypeMax) * SoundType::Normal);

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spSoundTex, static_cast<int>(m_soundTexPos.x), static_cast<int>(m_soundTexPos.y), static_cast<int>(m_spSoundTex->GetHeight()), static_cast<int>(m_spSoundTex->GetHeight()), &m_soundTexRect);
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::GamePractice:
		m_currentScene = std::make_shared<GameScene>(BaseScene::ModeFlg::Practice);
		break;
	case SceneType::GameSurvival:
		m_currentScene = std::make_shared<GameScene>(BaseScene::ModeFlg::Survival);
		break;
	case SceneType::GameTimeAttack:
		m_currentScene = std::make_shared<GameScene>(BaseScene::ModeFlg::TimeAttack);
		break;
	case SceneType::GameTimeLimit:
		m_currentScene = std::make_shared<GameScene>(BaseScene::ModeFlg::TimeLimit);
		break;
	}

	RESOURCE.ReleaseUnusedResources();

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;
}