#include "Cart.h"

void Cart::SetPos(const Math::Vector3& playerZeroPoint)
{
	m_mWorld.Translation((m_pos + playerZeroPoint));
}

void Cart::Init()
{
	SetModelData("Rail/cart.gltf");
	m_pos = { -1.5f, 0, 0 };
	m_scale = 3.0f;
	m_mWorld *= Math::Matrix::CreateScale(m_scale);
	m_mWorld *= Math::Matrix::CreateTranslation(m_pos);
}
