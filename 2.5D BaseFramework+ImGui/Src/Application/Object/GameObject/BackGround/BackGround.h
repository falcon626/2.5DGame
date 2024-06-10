#pragma once

class BlueCrystal;
class GrayFlat;
class GrayHeavy;
class GrayProtrusion;
class GraySlanted;
class GrayTowering;
class YellowBumpy;
class YellowSmooth;

class BackGround : public KdGameObject
{
public:
	BackGround() { Init(); }
	~BackGround() noexcept override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;
	void DrawBright() override;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;
private:
#define CAST_SIZE_T static_cast<size_t>
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
			Three,
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

		enum class YellowBumpy
		{
			One,
			Two,
			Three,
			All
		};

		enum class YellowSmooth
		{
			One,
			Two,
			Three,
			All
		};
	}BackRock;

	std::array<std::shared_ptr<BlueCrystal>,    CAST_SIZE_T(BackRock::BlueCrystal::All)>    m_spBlueCrystal;
	std::array<std::shared_ptr<GrayFlat>,       CAST_SIZE_T(BackRock::GrayFlat::All)>       m_spGrayFlat;
	std::array<std::shared_ptr<GrayHeavy>,      CAST_SIZE_T(BackRock::GrayHeavy::All)>      m_spGrayHeavy;
	std::array<std::shared_ptr<GrayProtrusion>, CAST_SIZE_T(BackRock::GrayProtrusion::All)> m_spGrayProtrusion;
	std::array<std::shared_ptr<GraySlanted>,    CAST_SIZE_T(BackRock::GraySlanted::All)>    m_spGraySlanted;
	std::array<std::shared_ptr<GrayTowering>,   CAST_SIZE_T(BackRock::GrayTowering::All)>   m_spGrayTowering;
	std::array<std::shared_ptr<YellowBumpy>,    CAST_SIZE_T(BackRock::YellowBumpy::All)>    m_spYellowBumpy;
	std::array<std::shared_ptr<YellowSmooth>,   CAST_SIZE_T(BackRock::YellowSmooth::All) >  m_spYellowSmooth;

	void Init() override;
};