#pragma once

class BlueCrystal;
class GrayFlat;
class GrayHeavy;
class GrayProtrusion;
class GraySlanted;
class GrayTowering;

class BackGround : public KdGameObject
{
public:
	BackGround () noexcept { Init(); }
	~BackGround() noexcept override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit()    override;
	void DrawBright() override;
	void Update()     override;

	void KillExistence() noexcept { m_isExpired = true; }

	void SetPos(const Math::Vector3& stageZeroPoint) override;

private:

	typedef union _tagBackRock
	{
		enum class BlueCrystal
		{
			One,
			Two,
			Three,
			All
		};

		enum class GrayFlat
		{
			One,
			Two,
			Three,
			All
		};

		enum class GrayHeavy
		{
			One,
			Two,
			Three,
			All
		};

		enum class GrayProtrusion
		{
			One,
			Two,
			Three,
			All
		};

		enum class GraySlanted
		{
			One,
			Two,
			All
		};

		enum class GrayTowering
		{
			One,
			Two,
			Three,
			Four,
			Five,
			Six,
			All
		};
	}BackRock;

	std::array<std::shared_ptr<BlueCrystal>,    static_cast<size_t>(BackRock::BlueCrystal::All)>    m_spBlueCrystal;
	std::array<std::shared_ptr<GrayFlat>,       static_cast<size_t>(BackRock::GrayFlat::All)>       m_spGrayFlat;
	std::array<std::shared_ptr<GrayHeavy>,      static_cast<size_t>(BackRock::GrayHeavy::All)>      m_spGrayHeavy;
	std::array<std::shared_ptr<GrayProtrusion>, static_cast<size_t>(BackRock::GrayProtrusion::All)> m_spGrayProtrusion;
	std::array<std::shared_ptr<GraySlanted>,    static_cast<size_t>(BackRock::GraySlanted::All)>    m_spGraySlanted;
	std::array<std::shared_ptr<GrayTowering>,   static_cast<size_t>(BackRock::GrayTowering::All)>   m_spGrayTowering;
	
	template<typename T, size_t N>
	inline auto SetObjectProperties(const std::array<std::shared_ptr<T>, N>& objects, 
		const std::vector<float>& parameters, size_t& counter, 
		const Math::Vector3& stageZeroPoint)
	{
		Math::Vector3 pos;
		float scale;
		for (decltype(auto) obj : objects)
		{
			pos.x = parameters[--counter];
			pos.y = parameters[--counter];
			pos.z = parameters[--counter];
			scale = parameters[--counter];

			obj->SetPos(pos + stageZeroPoint);
			obj->SetScale(scale);
		}
	}

	void Init() override;

};