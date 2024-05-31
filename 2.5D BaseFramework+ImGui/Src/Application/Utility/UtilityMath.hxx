#pragma once

namespace Formula // Convenience Functions
{
	template<typename T>
	decltype(auto) constexpr Rand(T min, T max) noexcept
	{
		static std::random_device rd;
		static std::mt19937 mt(rd());
		if constexpr (std::is_integral<T>::value)
		{
			std::uniform_int_distribution<T> dist(min, max);
			return dist(mt);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			std::uniform_real_distribution<T> dist(min, max);
			return dist(mt);
		}
		else static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, L"Not Number");
	}

	namespace Collider // Prototype
	{
		typedef struct
		{
			bool isHit = false;
			Math::Vector3 hitPos = Math::Vector3::Zero;
		}RayResult, &R_RayResult;

		// KdGameObject Only Ray Function
		void Ray(R_RayResult rayResult, 
			const std::list<std::shared_ptr<KdGameObject>>& objList,
			const Math::Vector3& rayVector,     const KdCollider::Type& hitType, 
			const Math::Vector3& startPos,      const float& rayLength, 
			const Math::Vector3& correctionPos, const float& enableStepHigh = NULL) noexcept
		{
			KdCollider::RayInfo rayInfo;
			rayInfo.m_pos = startPos;
			rayInfo.m_dir = rayVector;
			rayInfo.m_pos += correctionPos;
			rayInfo.m_pos.y += enableStepHigh;
			rayInfo.m_range = rayLength + enableStepHigh;
			rayInfo.m_type = hitType;

			std::list<KdCollider::CollisionResult> retRayList;
			for (decltype(auto) obj : objList){ obj->Intersects(rayInfo, &retRayList); }

			float maxOverLap = NULL;
			for (decltype(auto) ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					rayResult.hitPos = ret.m_hitPos;
					rayResult.isHit = true;
				}
			}
		}
	}
}