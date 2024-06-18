#include "IronPickaxe.h"
#include "../../../../../Data/BinaryAccessor.hpp"
#include "../../../../../Utility/UtilityDefault.hxx"

void IronPickaxe::Init()
{
	{
		// Local Declaration
		auto counter(Def::SizTNull);
		std::vector<size_t>  parameter;
		
		{
			// Load Initialization Value
			const auto IsAssert = DATA.Load(TemplateDataPath + "Iron/Initial_Size_t.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		// Set Value
		m_intervalTime = parameter[--counter];
		m_swingPow     = parameter[--counter];
	}

	// Load Model
	SetModelData( TemplateModelPath + "pickaxe.gltf");

	// Common Init
	BasePickaxe::Init();
}