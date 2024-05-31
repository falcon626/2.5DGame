#pragma once

class BasePickaxe :public KdGameObject
{
public:
	BasePickaxe() noexcept ;
	virtual ~BasePickaxe() noexcept override = default;

	virtual void Init() override;
	virtual void GenerateDepthMapFromLight() override;
	virtual void DrawLit() override;
	virtual void Update() override;
	virtual void PostUpdate() override;
	virtual void Use();

protected:
	// Not Virtual Function
	void SetModel(const std::string_view path) noexcept;

	// Constan Value
	const std::string TemplateDataPath  = "Asset/Data/PickaxeParameter/";
	const std::string TemplateModelPath = "Asset/Models/Pickaxe/";

	// Class Or Struct Value
	std::shared_ptr<KdModelData> m_spModel;

	// Other Value
	bool   m_isUse;
	size_t m_intervalTime;
	size_t m_swingPow;
	float  m_swingSpeed;
private:

	// Class Or Struct Value
	Math::Matrix  m_mScale;
	Math::Matrix  m_mRotation;
	Math::Matrix  m_mTrans;
	Math::Vector3 m_pos;

	// Other Value
	size_t m_swingTime;
	size_t m_swingFrame;
	float m_rollDegX;
	float m_rollDegZ;
	float m_scale;
};