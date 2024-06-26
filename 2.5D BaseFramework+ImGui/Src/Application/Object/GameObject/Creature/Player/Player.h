#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class Pickaxe;
class Cart;
class Timer;

class Player : public BaseExtensionObject
{
public:
	Player () noexcept;
	~Player() noexcept override = default;

	void GenerateDepthMapFromLight() noexcept override;
	void DrawLit()    noexcept override;
	void PreUpdate()  override;
	void Update()     override;
	void PostUpdate() override;
	
	inline auto SetStageDistance(const float& stageDistance) noexcept { m_stageDistance = stageDistance; }

	inline Math::Vector3 GetPos()  const noexcept override            { return m_pos; }

	inline auto const GetCombo()   const noexcept                     { return m_comboNum; }
	void              ChainCombo() noexcept;
	inline auto       ComboInterrupted() noexcept                     { m_comboNum -= m_comboNum; }

	inline auto const IsTaking()  const noexcept                      { return m_isTake; }

	inline auto       Move()      noexcept                            { m_isMove = true; }
	inline auto const IsMoveing() const noexcept                      { return m_isMove; }

	bool   const IsUsing ()       const noexcept;
	size_t const SwingPow()       const noexcept;

private:
	void Init() override;

	void Take() noexcept;

	std::shared_ptr<Pickaxe>         m_spPickaxe;
	std::shared_ptr<Cart>            m_spCart;
	std::shared_ptr<Timer>           m_spTimer;

	std::shared_ptr<KdSoundEffect>   m_spMoveSe;
	std::shared_ptr<KdSoundInstance> m_spMoveSeInfo;

	Math::Vector3 m_pos;
	Math::Vector3 m_startPos;

	size_t m_comboNum;
	size_t m_comboDuration;
	size_t m_comboDurationNormal;
	size_t m_comboDurationBorder;
	size_t m_comboDurationChange;
	float  m_stageDistance;
	float  m_speed;
	float  m_speedGear;
	float  m_minSpeed;
	float  m_maxSpeed;
	bool   m_isMove;
	bool   m_isTake;
};