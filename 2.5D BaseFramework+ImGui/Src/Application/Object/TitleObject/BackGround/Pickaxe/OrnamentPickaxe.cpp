#include "OrnamentPickaxe.h"
#include "../../../../Data/BinaryAccessor.hpp"

void OrnamentPickaxe::Init()
{
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/OrnamentPickaxeParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/OrnamentPickaxeParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto rotX(parameter[--counter]);
	auto rotZ(parameter[--counter]);

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);
	auto z(parameter[--counter]);

	SetModelData("Pickaxe/pickaxe.gltf");
	m_mWorld = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rotX)) * Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotZ));
	SetPos({ x,y,z });
}