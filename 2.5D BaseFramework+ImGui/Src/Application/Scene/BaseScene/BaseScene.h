#pragma once

class BaseScene
{
public :

	BaseScene() { Init(); }
	virtual ~BaseScene() {}

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_objList.push_back(_obj);
	}

protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();
	virtual void Init();

	std::unique_ptr<KdCamera> m_camera = nullptr;

	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;

	// Add ObjctList Function (Emplace_Back)
	template <typename T, typename... Args>
	void AddObjList(Args&&... args) 
	{ m_objList.emplace_back(std::make_shared<T>(std::forward<Args>(args)...)); }

	// Add ObjctList And Create WeakPtr Function (Push_Back)
	template <typename _T, typename... _Args>
	void AddObjList(std::weak_ptr<_T>& wpObj ,_Args&&... args)
	{
		auto obj = std::make_shared<_T>(std::forward<_Args>(args)...);
		wpObj = obj;
		m_objList.push_back(obj);
	}
};
