#pragma once
#include "../BaseScene/BaseScene.h"

class SelectMode;

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}


private :

	void Event() override;
	void Init()  override;

	void LoadResources() noexcept override;

	std::weak_ptr<SelectMode> m_wpSelectMode;
};
