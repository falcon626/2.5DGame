#pragma once
#include "../../../BaseExtensionObject/BaseExtensionObject.h"

class PickaxeManager;
class Cart;

class Player : public BaseExtensionObject
{
public:
	Player () noexcept;
	~Player() noexcept override = default;


	void GenerateDepthMapFromLight() noexcept override;
	void DrawLit() noexcept override;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;

	inline auto SetStageDistance(const float& stageDistance) noexcept { m_stageDistance = stageDistance; }

	inline Math::Vector3 GetPos() const override { return m_pos; }

	inline auto const GetCombo() const { return m_comboNum; }

	inline auto ChainCombo() { ++m_comboNum; }

	inline auto ComboInterrupted() { m_comboNum -= m_comboNum; }

	inline auto  const IsTaking() const noexcept { return m_isTake; }

	inline auto        Move() noexcept { m_isMove = true; }
	inline auto  const IsMoveing() const noexcept { return m_isMove; }

	bool   const IsUsing () const noexcept;
	size_t const SwingPow() const noexcept;

private:
	void Init() override;

	void Take() noexcept;

	std::shared_ptr<PickaxeManager> m_spPickaxe;
	std::shared_ptr<Cart>           m_spCart;

	Math::Vector3 m_pos;
	Math::Vector3 m_startPos;

	size_t m_comboNum;
	float  m_stageDistance;
	float  m_speed;
	float  m_minSpeed;
	float  m_maxSpeed;
	bool   m_isMove;
	bool   m_isTake;

};