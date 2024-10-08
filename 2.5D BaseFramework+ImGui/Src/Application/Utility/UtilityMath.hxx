#pragma once

namespace Formula // Convenience Functions
{
	template<typename T>
	[[nodiscard(L"No Random Return Value")]] decltype(auto) Rand
	(const T& min, const T& max) noexcept
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
	[[nodiscard(L"No Random Return Value")]] decltype(auto) Rand
	(const _T& min, const _T& max, const std::initializer_list<_T>& exclusion) noexcept
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
		typedef union _tagResult
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
		template<class T>
		static auto Ray(Result::R_RayResult rayResult, 
			const std::list<std::shared_ptr<KdGameObject>>& objList,
			const Math::Vector3& rayDirection,  const KdCollider::Type& hitType, 
			const Math::Vector3& startPos,      const float& rayLength, 
			const Math::Vector3& correctionPos, const float& enableStepHigh = static_cast<float>(NULL),
			const bool& isSetMaxLength = false, const float& maxLength      = static_cast<float>(NULL),
			const T* pThat = nullptr) noexcept
		{
			if(pThat) static_assert(std::is_base_of<KdGameObject, T>::value, "T Must Be Derived From KdGameObject");

			KdCollider::RayInfo rayInfo;
			rayInfo.m_pos     = startPos;
			rayInfo.m_dir     = rayDirection;
			rayInfo.m_pos    += correctionPos;
			rayInfo.m_pos.y  += enableStepHigh;
			rayInfo.m_range   = rayLength + enableStepHigh + correctionPos.y;
			if (isSetMaxLength && maxLength < rayInfo.m_range) rayInfo.m_range = maxLength;
			rayInfo.m_type    = hitType;

			rayResult.isHit_  = false;
			rayResult.hitPos_ = Math::Vector3::Zero;

			std::list<KdCollider::CollisionResult> retRayList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == pThat) continue;
				obj->Intersects(rayInfo, &retRayList);
			}

			float maxOverLap(NULL);
			for (decltype(auto) ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					rayResult.isHit_  = true;
					rayResult.hitPos_ = ret.m_hitPos;
				}
			}
		}

		// Assignment RayInfo
		static auto Ray(KdCollider::RayInfo& rayInfoResult,
			const Math::Vector3& rayDirection, const KdCollider::Type& hitType,
			const Math::Vector3& startPos, const float& rayLength,
			const Math::Vector3& correctionPos, const float& enableStepHigh = static_cast<float>(NULL)) noexcept
		{
			rayInfoResult.m_pos    = startPos;
			rayInfoResult.m_dir    = rayDirection;
			rayInfoResult.m_pos   += correctionPos;
			rayInfoResult.m_pos.y += enableStepHigh;
			rayInfoResult.m_range  = rayLength + enableStepHigh + correctionPos.y;
			rayInfoResult.m_type   = hitType;
		}

		// KdGameObject Only Sphere Function
		template<class _T>
		static auto Sphere(Result::R_SphereResult sphereResult,
			const std::list<std::shared_ptr<KdGameObject>>& objList,
			const KdCollider::Type& hitType, const Math::Vector3& centerPos, 
			const float& sphereRadius,       const Math::Vector3& correctionPos,
			const _T* pThat = nullptr) noexcept
		{
			if (pThat) static_assert(std::is_base_of<KdGameObject, _T>::value, "_T Must Be Derived From KdGameObject");

			KdCollider::SphereInfo sphereInfo;
			sphereInfo.m_sphere.Center = centerPos + correctionPos;
			sphereInfo.m_sphere.Radius = sphereRadius;
			sphereInfo.m_type          = hitType;

			sphereResult.isHit_  = false;
			sphereResult.hitDir_ = Math::Vector3::Zero;

			std::list<KdCollider::CollisionResult> retSphereList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == pThat) continue;
				obj->Intersects(sphereInfo, &retSphereList);
			}

			float maxOverLap(NULL);
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

		// Assignment SphereInfo
		static auto Sphere(KdCollider::SphereInfo& sphereInfo,
			const KdCollider::Type& hitType, const Math::Vector3& centerPos,
			const float& sphereRadius, const Math::Vector3& correctionPos) noexcept
		{
			sphereInfo.m_sphere.Center = centerPos + correctionPos;
			sphereInfo.m_sphere.Radius = sphereRadius;
			sphereInfo.m_type          = hitType;
		}
	} // Name Space Collider
} // Name Space Formula