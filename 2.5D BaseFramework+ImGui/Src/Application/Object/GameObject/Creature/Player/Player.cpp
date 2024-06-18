#include "Player.h"
#include "../../Tool/Pickaxe/PickaxeManager.h"
#include "../../Tool/Cart/Cart.h"
#include "../../../../Utility/UtilityKey.hxx"
#include "../../../../Utility/UtilityDefault.hxx"

Player::Player() noexcept
	: m_comboNum(Def::SizTNull)
	, m_stageDistance(Def::FloatNull)
	, m_speed(Def::FloatNull)
	, m_minSpeed(Def::FloatNull)
	, m_maxSpeed(Def::FloatNull)
	, m_isMove(false)
	, m_isTake(false)
{ Init(); }

void Player::Init()
{
	m_spPickaxe = std::make_shared<PickaxeManager>();
	m_spCart    = std::make_shared<Cart>();

	m_spPickaxe->Init();
	m_minSpeed = -0.175f;
	m_speed    = m_minSpeed;
	m_maxSpeed = -0.68f;
}


void Player::GenerateDepthMapFromLight() noexcept
{
	if (!m_spPickaxe)return;
	m_spPickaxe->GenerateDepthMapFromLight();
	m_spCart->GenerateDepthMapFromLight();
}

void Player::DrawLit() noexcept
{
	if (!m_spPickaxe)return;
	m_spPickaxe->DrawLit();
	m_spCart->DrawLit();
}

void Player::PreUpdate()
{
	if (!m_spPickaxe)return;
	m_spPickaxe->PreUpdate();
	//if (m_comboNum > 0) m_spPickaxe->SetNextPickaxe(PickaxeManager::PickaxeType::Gold);
	auto speedUp(m_comboNum * -0.1f);
	m_speed  = m_minSpeed;
	m_speed += speedUp;
	if (m_speed < m_maxSpeed)m_speed = m_maxSpeed;
	
}

void Player::Update()
{
	if (m_isMove)
	{
		m_isTake = false;
		if (m_pos.x + m_speed <= m_startPos.x + m_stageDistance) m_pos.x = m_startPos.x + m_stageDistance;
		else m_pos.x += m_speed;
		if (m_pos.x == m_startPos.x + m_stageDistance) m_isMove = false;
	}
	else
	{
		m_startPos = m_pos;
		m_spPickaxe->Use();
		Take();
	}
	m_spPickaxe->SetPos(m_pos);
	m_spCart->SetPos(m_pos);
	m_spPickaxe->Update();
}

void Player::PostUpdate()
{
	m_spPickaxe->PostUpdate();
	m_mWorld.Translation(m_pos);
}

void Player::Take() noexcept
{
	if (Key::IsPushing(Key::SideR_Click) || Key::IsPushing(Key::E))
	{
		if (!Key::_flg) m_isTake  = true;
		Key::_flg = true;
	}
	else
	{
		Key::_flg = false;
		m_isTake  = false;
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
