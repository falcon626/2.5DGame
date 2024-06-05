#include "ResourceManager.h"
#include "../Utility/UtilityDefault.hxx"

std::shared_ptr<KdModelData> ResourceManager::GetModel(const std::string& path)
{
	auto it = m_models.find(path);
	if (it != m_models.end()) return it->second;

	std::shared_ptr<KdModelData> model = std::make_shared<KdModelData>();
	if (model->Load(path))
	{
		m_models[path] = model;
		return model;
	}
	// ModelData Not Found
	return nullptr;
}

void ResourceManager::ReleaseUnusedResources()
{
	for (auto it = m_models.begin(); it != m_models.end();) 
	{
		if (it->second.use_count() == Def::LongOne) it = m_models.erase(it);
		else ++it;
	}
}