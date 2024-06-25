#pragma once

class BaseExtensionObject : public KdGameObject
{
public:
	BaseExtensionObject() noexcept = default;
	virtual ~BaseExtensionObject() noexcept override = default;
	
	// Not Virtual Function
	inline void GenerateDepthMapFromLight() noexcept override { KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }
	inline void DrawLit() noexcept override { KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }
protected:
	// KdModelData
	void SetModelData(const std::string_view& path) noexcept;

	// Ius Vitae Necisque
	auto KillExistence() noexcept { m_isExpired = true; }
private:
	// Class Or Struct Value
	std::shared_ptr<KdModelData> m_spModel;
};