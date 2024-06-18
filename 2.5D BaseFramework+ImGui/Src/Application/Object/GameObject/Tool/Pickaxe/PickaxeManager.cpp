#include "PickaxeManager.h"
#include "BasePickaxe.h"
#include "IronPickaxe/IronPickaxe.h"
#include "GoldPickaxe/GoldPickaxe.h"
#include "DiamondPickaxe/DiamondPickaxe.h"

void PickaxeManager::GenerateDepthMapFromLight() noexcept
{
	m_spPickaxe->GenerateDepthMapFromLight();
}

void PickaxeManager::DrawLit() noexcept
{
	m_spPickaxe->DrawLit();
}

void PickaxeManager::PreUpdate() noexcept
{
	if (m_nowPickaxeType != m_nextPickaxeType) ChangeType(m_nextPickaxeType);
}

void PickaxeManager::Update() noexcept
{
	m_spPickaxe->Update();
}

void PickaxeManager::PostUpdate() noexcept
{
	m_spPickaxe->PostUpdate();
}

void PickaxeManager::SetPos(const Math::Vector3& playerZeroPoint) noexcept
{
	m_spPickaxe->SetPos(playerZeroPoint);
}

void PickaxeManager::Use() noexcept
{
	m_spPickaxe->Use();
}

bool const PickaxeManager::IsUsing() const noexcept
{
	return m_spPickaxe->IsUsing();
}

size_t const PickaxeManager::SwingPow() const noexcept
{
	return m_spPickaxe->SwingPow();
}

void PickaxeManager::ChangeType(PickaxeType type) noexcept
{
	switch (type)
	{
	case PickaxeManager::PickaxeType::Iron:
		m_spPickaxe = std::make_shared<IronPickaxe>();
		break;
	case PickaxeManager::PickaxeType::Gold:
		m_spPickaxe = std::make_shared<GoldPickaxe>();
		break;
	case PickaxeManager::PickaxeType::Diamond:
		m_spPickaxe = std::make_shared<DiamondPickaxe>();
		break;
	default:
		break;
	}
	m_spPickaxe->Init();
	m_nowPickaxeType = type;
}
