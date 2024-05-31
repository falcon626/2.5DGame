#include "IronPickaxe.h"
#include "../../../../../Data/BinaryAccessor.hpp"
#include "../../../../../Utility/UtilityKey.hxx"

void IronPickaxe::Init()
{
	SetModel( TemplateModelPath + "pickaxe.gltf");
	m_dataPath = TemplateDataPath + "IronParameter.dat";
	BasePickaxe::Init();
}

void IronPickaxe::Use()
{
	BasePickaxe::Use();
	m_intervalTime = 30;
}
