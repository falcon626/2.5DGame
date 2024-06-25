#include "Ban.h"
#include "../../../../Data/BinaryAccessor.hpp"

Ban::Ban(const std::shared_ptr<KdTexture>& spTex) noexcept
{
	// Local Declaration
	std::vector<float> parameter;
	auto counter(static_cast<size_t>(NULL));

	{
		// Load Initialization Value
#if _DEBUG
		const auto IsAssert = DATA.Load("Asset/Data/BanTextureParameter/Initial_Float.dat", parameter, counter);
		_ASSERT_EXPR(IsAssert, L"BinaryData Not Found");
#else
		DATA.Load("Asset/Data/BanTextureParameter/Initial_Float.dat", parameter, counter);
#endif // _DEBUG
	}

	auto x(parameter[--counter]);
	auto y(parameter[--counter]);

	SetTex(spTex);
	m_pos = { x,y };
}