#include "PickaxeManager.h"
#include "BasePickaxe.h"
#include "IronPickaxe/IronPickaxe.h"
#include "GoldPickaxe/GoldPickaxe.h"
#include "DiamondPickaxe/DiamondPickaxe.h"

void PickaxeManager::GenerateDepthMapFromLight()
{
	m_spPickaxe->GenerateDepthMapFromLight();
}

void PickaxeManager::DrawLit()
{
	m_spPickaxe->DrawLit();
}

void PickaxeManager::PreUpdate()
{
	if (m_nowPickaxeType != m_nextPickaxeType) ChangeType(m_nextPickaxeType);
}

void PickaxeManager::Update()
{
	m_spPickaxe->Use();
	m_spPickaxe->Update();
}

void PickaxeManager::PostUpdate()
{
	m_spPickaxe->PostUpdate();
}

void PickaxeManager::ChangeType(PickaxeType type)
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
