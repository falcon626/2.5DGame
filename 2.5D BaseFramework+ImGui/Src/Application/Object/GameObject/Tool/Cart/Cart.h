#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Cart : public BaseExtensionObject
{
public:
	Cart ()noexcept { Init(); }
	~Cart()noexcept = default;

	void SetPos(const Math::Vector3& playerZeroPoint);
private:
	void Init() override;
	Math::Vector3 m_pos;
	float m_scale;
};