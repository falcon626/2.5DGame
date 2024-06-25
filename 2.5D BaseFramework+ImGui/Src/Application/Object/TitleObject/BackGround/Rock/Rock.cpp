#include "Rock.h"
#include "../../../../Data/BinaryAccessor.hpp"

void Rock::Init()
{
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/TitleRockParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/TitleRockParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	SetModelData("Rock/Rock_05.gltf");
	SetScale(parameter[--counter]);
}