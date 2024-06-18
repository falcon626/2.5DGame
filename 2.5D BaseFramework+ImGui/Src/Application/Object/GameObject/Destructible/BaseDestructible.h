#pragma once

class BaseDestructible
{
public:
	BaseDestructible() noexcept = default;
	virtual ~BaseDestructible() noexcept = default;

	virtual void OnBreak() noexcept { m_isBroken = true; }
	virtual inline bool const IsBroken() const { return m_isBroken; }

	virtual void OnCollect() noexcept { m_isCollect = true; }
	virtual inline bool const IsCollect() const { return m_isCollect; }
protected:

	size_t m_hp;
	size_t m_interval;
	float  m_dissolve;
	float  m_dissolveSpeed;
	bool   m_isBroken;
	bool   m_isCollect;
private:
};