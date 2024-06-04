#pragma once

namespace Formula // Convenience Functions
{
	template<typename T>
	decltype(auto) Rand(const T& min, const T& max) noexcept
	{
		static thread_local std::random_device rd;
		static thread_local std::mt19937 mt(rd());

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
		else static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Not A Valid Numeric Type");
	}

	template<typename _T>
	decltype(auto) Rand(const _T& min, const _T& max, const std::initializer_list<_T>& exclusion) noexcept
	{
		static thread_local std::random_device rd;
		static thread_local std::mt19937 mt(rd());

		// Exclusion Check Function (Lambda)
		auto isExcluded = [&exclusion](const _T& value) 
		{ return std::find(exclusion.begin(), exclusion.end(), value) != exclusion.end(); };

		if constexpr (std::is_integral<_T>::value)
		{
			std::uniform_int_distribution<_T> dist(min, max);
			_T value;
			do {
				value = dist(mt);
			} while (isExcluded(value));
			return value;
		}
		else if constexpr (std::is_floating_point<_T>::value)
		{
			std::uniform_real_distribution<_T> dist(min, max);
			_T value;
			do {
				value = dist(mt);
			} while (isExcluded(value));
			return value;
		}
		else static_assert(std::is_integral<_T>::value || std::is_floating_point<_T>::value, "Not A Valid Numeric Type");
	}

	namespace Collider // So Deep Nest
	{
		typedef union tagResult
		{
			typedef struct tagRayResult
			{
				bool isHit_ = false;
				Math::Vector3 hitPos_ = Math::Vector3::Zero;
			}RayResult, &R_RayResult;

			typedef struct tagSphereResult
			{
				bool isHit_ = false;
				Math::Vector3 hitDir_ = Math::Vector3::Zero;
			}SphereResult, &R_SphereResult;
		}Result;
		
		// KdGameObject Only Ray Function
		auto Ray(Result::R_RayResult rayResult, 
			const std::list<std::shared_ptr<KdGameObject>>& objList,
			const Math::Vector3& rayDirection,  const KdCollider::Type& hitType, 
			const Math::Vector3& startPos,      const float& rayLength, 
			const Math::Vector3& correctionPos, const float& enableStepHigh = NULL) noexcept
		{
			KdCollider::RayInfo rayInfo;
			rayInfo.m_pos     = startPos;
			rayInfo.m_dir     = rayDirection;
			rayInfo.m_pos    += correctionPos;
			rayInfo.m_pos.y  += enableStepHigh;
			rayInfo.m_range   = rayLength + enableStepHigh;
			rayInfo.m_type    = hitType;

			rayResult.isHit_  = false;
			rayResult.hitPos_ = Math::Vector3::Zero;

			std::list<KdCollider::CollisionResult> retRayList;
			for (decltype(auto) obj : objList)
				obj->Intersects(rayInfo, &retRayList);

			float maxOverLap = NULL;
			for (decltype(auto) ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					rayResult.isHit_ = true;
					rayResult.hitPos_ = ret.m_hitPos;
				}
			}
		}

		// KdGameObject Only Sphere Function
		auto Sphere(Result::R_SphereResult sphereResult,
			const std::list<std::shared_ptr<KdGameObject>>& objList,
			const KdCollider::Type& hitType, const Math::Vector3& centerPos, 
			const float& sphereRadius,       const Math::Vector3& correctionPos) noexcept
		{
			KdCollider::SphereInfo sphereInfo;
			sphereInfo.m_sphere.Center = centerPos + correctionPos;
			sphereInfo.m_sphere.Radius = sphereRadius;
			sphereInfo.m_type = hitType;

			sphereResult.isHit_ = false;
			sphereResult.hitDir_ = Math::Vector3::Zero;

			std::list<KdCollider::CollisionResult> retSphereList;
			for (decltype(auto) obj : objList)
				obj->Intersects(sphereInfo, &retSphereList);

			float maxOverLap = NULL;
			for (decltype(auto) ret : retSphereList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					sphereResult.isHit_  = true;
					sphereResult.hitDir_ = ret.m_hitDir;
				}
			}
		}
	} // Name Space Collider
} // Name Space Formula