#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Crystal : public BaseExtensionObject
{
public:
	Crystal() { Init(); }
	~Crystal() noexcept override {}

	void Update()override;

private:
	void Init()override;
	std::shared_ptr<KdModelData> m_spModel;
};