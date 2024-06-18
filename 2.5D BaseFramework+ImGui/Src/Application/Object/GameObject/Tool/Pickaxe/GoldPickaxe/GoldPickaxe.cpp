#include "GoldPickaxe.h"
#include "../../../../../Data/BinaryAccessor.hpp"
#include "../../../../../Utility/UtilityDefault.hxx"

void GoldPickaxe::Init()
{
	{
		// Local Declaration
		auto counter(Def::SizTNull);
		std::vector<size_t>  parameter;

		{
			// Load Initialization Value
			const auto IsAssert = DATA.Load(TemplateDataPath + "Gold/Initial_Size_t.dat", parameter, counter);
			_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
		}

		// Set Value
		m_intervalTime = parameter[--counter];
		m_swingPow     = parameter[--counter];
	}

	// Load Model
	SetModelData(TemplateModelPath + "superPickaxe.gltf");

	// Common Init
	BasePickaxe::Init();
}
