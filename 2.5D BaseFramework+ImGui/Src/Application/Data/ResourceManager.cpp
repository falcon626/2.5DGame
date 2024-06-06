#include "ResourceManager.h"
#include "../Utility/UtilityDefault.hxx"

std::shared_ptr<KdModelData> ResourceManager::IndexModelData(const std::string& path) noexcept
{
	auto it = m_models.find(TemplateModelsPath + path);
	if (it != m_models.end()) return it->second;
	// ModelData Not Found
	return nullptr;
}

std::shared_ptr<KdTexture> ResourceManager::IndexTexture(const std::string& path) noexcept
{
	auto it = m_textures.find(TemplateTexturesPath + path);
	if (it != m_textures.end()) return it->second;
	// TextureData Not Found
	return nullptr;
}

void ResourceManager::PreLoadModelsData(const std::vector<std::string>& paths) noexcept
{
	for (const auto& path : paths)
	{
		auto model = std::make_shared<KdModelData>();
		if (model->Load(TemplateModelsPath + path)) m_models.emplace(TemplateModelsPath + path, model);
		else _ASSERT_EXPR(false, L"ModelData Not Found");
	}
}

void ResourceManager::PreLoadTextures(const std::vector<std::string>& paths) noexcept
{
	for (const auto& path : paths)
	{
		auto texture = std::make_shared<KdTexture>();
		if (texture->Load(TemplateTexturesPath + path)) m_textures.emplace(TemplateTexturesPath + path, texture);
		else _ASSERT_EXPR(false, L"TextureData Not Found");
	}
}

void ResourceManager::ReleaseUnusedResources() noexcept
{
	for (auto it = m_models.begin(); it != m_models.end();) 
	{
		if (it->second.use_count() == Def::LongOne) it = m_models.erase(it);
		else ++it;
	}
	for (auto it = m_textures.begin(); it != m_textures.end();)
	{
		if (it->second.use_count() == Def::LongOne) it = m_textures.erase(it);
		else ++it;
	}
}