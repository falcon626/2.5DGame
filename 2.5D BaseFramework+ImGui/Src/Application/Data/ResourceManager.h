#pragma once

class ResourceManager 
{
public:

	// Common Path For All Omitted Models
	std::shared_ptr<KdModelData> IndexModelData(const std::string& path) noexcept;

	// Common Path For All Omitted Textures
	std::shared_ptr<KdTexture> IndexTexture(const std::string& path) noexcept;

	// Exclusive To KdModelData
	// Cache Of Resource
	void PreLoadModelsData(const std::vector<std::string>& paths) noexcept;

	// Exclusive To KdTexture
	// Cache Of Resource
	void PreLoadTextures(const std::vector<std::string>& paths) noexcept;

	// Dump Old Resource
	void ReleaseUnusedResources() noexcept;

	static auto& Instance() noexcept { static ResourceManager instance; return instance; }
private:
	// Singleton Class
	ResourceManager () noexcept = default;
	~ResourceManager() noexcept = default;

	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_models;
	std::unordered_map<std::string, std::shared_ptr<KdTexture>> m_textures;

	const std::string TemplateModelsPath   = "Asset/Models/";
	const std::string TemplateTexturesPath = "Asset/Textures/";
};

#define RESOURCE ResourceManager::Instance()