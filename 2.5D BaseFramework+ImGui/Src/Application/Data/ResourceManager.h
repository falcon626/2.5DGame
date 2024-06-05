#pragma once

class ResourceManager {
public:

	std::shared_ptr<KdModelData> GetModel(const std::string& path);

	void ReleaseUnusedResources();

	static auto& Instance() { static ResourceManager instance; return instance; }
private:
	ResourceManager() {}
	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_models;
};