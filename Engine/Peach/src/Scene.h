#pragma once
#include "SceneManager.h"

namespace peach
{
	class InputManager;
	class GameObject;
	class Scene
	{
	public:
		explicit Scene(const std::string& name);

		void Add(GameObject* object);
		void Remove(GameObject* object);

		void RootInitialize();
		void RootPostInitialize();
		void RootFixedUpdate();
		bool RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

		std::vector<GameObject*> GetObjectsWithTag(const std::string& tag);

		const std::string& GetName()const { return m_Name; }
		std::shared_ptr<InputManager> GetInputManager()const { return m_pInputManager; }

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		virtual void Initialize() {};
		virtual void PostInitialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

	private:

		std::string m_Name;
		std::vector < GameObject*> m_pObjects{};
		std::shared_ptr<InputManager> m_pInputManager = nullptr;
		static unsigned int m_IdCounter;
		bool m_IsInitialized = false;
	};
}
