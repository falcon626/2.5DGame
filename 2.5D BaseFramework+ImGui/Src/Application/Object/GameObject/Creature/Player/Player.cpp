#include "Player.h"
#include "../../Tool/Pickaxe/Pickaxe.h"
#include "../../Tool/Cart/Cart.h"
#include "../../../../Utility/UtilityKey.hxx"
#include "../../../../Utility/UtilityDefault.hxx"
#include "../../../../Data/BinaryAccessor.hpp"
#include "../../../../System/Timer/Timer.h"

Player::Player() noexcept
	: m_comboNum           (Def::SizTNull)
	, m_comboDuration      (Def::SizTNull)
	, m_comboDurationNormal(Def::SizTNull)
	, m_comboDurationBorder(Def::SizTNull)
	, m_comboDurationChange(Def::SizTNull)
	, m_stageDistance      (Def::FloatNull)
	, m_speed              (Def::FloatNull)
	, m_speedGear          (Def::FloatNull)
	, m_minSpeed           (Def::FloatNull)
	, m_maxSpeed           (Def::FloatNull)
	, m_isMove             (false)
	, m_isTake             (false)
{ Init(); }

void Player::Init()
{
	m_spPickaxe = std::make_shared<Pickaxe>();
	m_spCart    = std::make_shared<Cart>();
	m_spTimer   = std::make_shared<Timer>();
	
	m_spMoveSe  = std::make_shared<KdSoundEffect>();
	m_spMoveSe  ->Load("Asset/Sounds/Move/move.wav",KdAudioManager::Instance().GetAudioEngine());
	
	m_spMoveSeInfo  = std::make_shared<KdSoundInstance>(m_spMoveSe);
	m_spMoveSeInfo  ->CreateInstance();

	KdAudioManager::Instance().AddPlayList(m_spMoveSeInfo);

	m_spPickaxe->Init();

	std::vector<float> parameter;
	auto counter (Def::SizTNull);

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/PlayerParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/PlayerParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	m_comboDuration       = static_cast<size_t>(parameter[--counter]);
	m_comboDurationNormal = m_comboDuration;
	m_comboDurationBorder = static_cast<size_t>(parameter[--counter]);
	m_comboDurationChange = static_cast<size_t>(parameter[--counter]);

	m_minSpeed  = parameter[--counter];
	m_speed     = m_minSpeed;
	m_maxSpeed  = parameter[--counter];
	m_speedGear = parameter[--counter];
}


void Player::GenerateDepthMapFromLight() noexcept
{
	if (!m_spPickaxe)return;
	m_spPickaxe->GenerateDepthMapFromLight();
	m_spCart   ->GenerateDepthMapFromLight();
}

void Player::DrawLit() noexcept
{
	if (!m_spPickaxe)return;
	m_spPickaxe->DrawLit();
	m_spCart   ->DrawLit();
}

void Player::PreUpdate()
{
	if (!m_spPickaxe)return;

	m_spPickaxe->SetComboNum(m_comboNum);
	m_spPickaxe->PreUpdate();

	auto speedUp(static_cast<float>(m_comboNum) * m_speedGear);
	m_speed  = m_minSpeed;
	m_speed += speedUp;
	if (m_speed < m_maxSpeed)m_speed = m_maxSpeed;

	m_comboDuration = m_comboDurationNormal;
	if (m_comboNum > m_comboDurationBorder) m_comboDuration -= m_comboDurationChange;
}

void Player::Update()
{
	if (m_isMove)
	{
		if (!m_spMoveSeInfo->IsPlaying()) m_spMoveSeInfo->Play();

		m_isTake = false;
		
		m_spTimer->Reset();

		if  (m_pos.x +  m_speed <= m_startPos.x + m_stageDistance) m_pos.x = m_startPos.x + m_stageDistance;
		else m_pos.x += m_speed;
		if  (m_pos.x == m_startPos.x + m_stageDistance) m_isMove = false;
	}
	else
	{
		if (m_spMoveSeInfo->IsPlaying()) m_spMoveSeInfo->Stop();

		m_startPos = m_pos;

		// Player's Action
		m_spPickaxe->Use();
		if(!m_spPickaxe->IsUsing()) Take();

		// Combo Duration
		m_spTimer->Start();
		if(static_cast<size_t>(m_spTimer->ElapsedSeconds()) > m_comboDuration)
		{
			m_spTimer  ->Reset();
			m_comboNum = Def::SizTNull;
		}
	}

	m_spPickaxe->SetPos(m_pos);
	m_spCart   ->SetPos(m_pos);
	m_spPickaxe->Update();
}

void Player::PostUpdate()
{
	m_spPickaxe  ->PostUpdate();
	m_mWorld.Translation(m_pos);
}

void Player::ChainCombo() noexcept
{
	++m_comboNum;
	if (m_comboNum > m_comboDurationBorder) KdAudioManager::Instance().Play("Asset/Sounds/Combo/highCombo.wav");
}

void Player::Take() noexcept
{
	if (Key::IsPushing(Key::R_Click) || Key::IsPushing(Key::E))
	{
		if (!Key::_isPush) m_isTake = true;
		Key::_isPush = true;
	}
	else
	{
		Key::_isPush = false;
		m_isTake     = false;
	}
}

bool const Player::IsUsing() const noexcept
{
	return m_spPickaxe->IsUsing();
}

size_t const Player::SwingPow() const noexcept
{
	return m_spPickaxe->SwingPow();
}
