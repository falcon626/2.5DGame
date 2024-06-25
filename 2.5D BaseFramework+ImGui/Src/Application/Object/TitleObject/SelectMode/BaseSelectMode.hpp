#pragma once
#include "SelectModeTag.hpp"

class BaseSelectMode : public KdGameObject, SelectModeTag
{
public:
	BaseSelectMode()noexcept = default;
	virtual ~BaseSelectMode()noexcept override = default;

	void DrawSprite() noexcept override
	{ KdShaderManager::Instance().m_spriteShader.DrawTex
	(m_spTex, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y)); }
protected:
	std::shared_ptr<KdTexture> m_spTex;
	Math::Vector2 m_pos;
};