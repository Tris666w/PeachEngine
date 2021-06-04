#pragma once
#include "SceneManager.h"
#include "Logger.h"

namespace peach
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);

		void Initialize();
		void PostInitialize();

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		std::vector<GameObject*> GetObjectsWithTag(const std::string& tag);

		const std::string& GetName()const { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < GameObject*> m_pObjects{};

		static unsigned int m_IdCounter;
	};
}
