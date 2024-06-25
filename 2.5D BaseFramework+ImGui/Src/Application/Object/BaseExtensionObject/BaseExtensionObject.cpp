#include "BaseExtensionObject.h"
#include "../../Data/ResourceManager.h"

void BaseExtensionObject::SetModelData(const std::string_view& path) noexcept
{
	if (path.empty()) return;

	std::string modelPath(path);

	m_spModel = std::make_shared<KdModelData>();
	m_spModel = RESOURCE.IndexModelData(modelPath);

	if (!m_spModel) _ASSERT_EXPR(false, L"ModelData Not Found");
}
