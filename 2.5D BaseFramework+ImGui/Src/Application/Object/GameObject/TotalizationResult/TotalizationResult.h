#pragma once
#include "../../BaseExtensionObject/BaseExtensionObject.h"

class GameUi;

class TotalizationResult : public BaseExtensionObject
{
public:
	explicit TotalizationResult (const bool& isModeSurvival,const bool& isModeTimeAttack,const bool& isModeTimeLimit,
		const size_t& maxCombo, const size_t& time, const size_t& score, const Math::Vector3& pos) noexcept;
	~TotalizationResult()noexcept override = default;

	void Update()override;

	void SetUiWeakPtr(const std::shared_ptr<GameUi>& spGameUi) noexcept { m_wpGameUi = spGameUi; }
private:
	void Init()override;

	void AwardGold  () noexcept { SetModelData("Awardcup/gold/awardcupgold.gltf");     }
	void AwardSilver() noexcept { SetModelData("Awardcup/silver/awardcupsilver.gltf"); }
	void AwardBronze() noexcept { SetModelData("Awardcup/bronze/awardcupBronze.gltf"); }

	std::weak_ptr<GameUi> m_wpGameUi;

	Math::Vector3 m_pos;
	Math::Vector3 m_correctionPos;

	size_t m_maxCombo;
	size_t m_time;
	size_t m_score;
	size_t m_maxPercentage;
	size_t m_randomization;

	float  m_rotX;
	float  m_rotY;
	float  m_rotZ;
	float  m_rotSpeed;
	float  m_maxRot;
	float  m_scale;

	bool m_isModeSurvival;
	bool m_isModeTimeAttack;
	bool m_isModeTimeLimit;
};