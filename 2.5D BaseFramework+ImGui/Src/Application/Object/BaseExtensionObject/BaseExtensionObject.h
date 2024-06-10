#pragma once

class BaseExtensionObject : public KdGameObject
{
public:
	BaseExtensionObject() noexcept = default;
	virtual ~BaseExtensionObject() noexcept override = default;
	
	// Not Virtual Function
	void GenerateDepthMapFromLight() noexcept override;
	void DrawLit() noexcept override;
protected:
	// KdModelData
	void SetModelData(const std::string_view& path) noexcept;
private:
	// Class Or Struct Value
	std::shared_ptr<KdModelData> m_spModel;
};