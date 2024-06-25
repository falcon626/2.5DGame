#include "Cart.h"
#include "../../../../Data/BinaryAccessor.hpp"

void Cart::Init()
{
	SetModelData("Cart/cart.gltf");

	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/CartParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/CartParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);
	auto z(parameter[--counter]);

	m_pos     = { x, y, z };
	m_scale   = parameter[--counter];
	m_mWorld *= Math::Matrix::CreateScale(m_scale);
	m_mWorld *= Math::Matrix::CreateTranslation(m_pos);
}