#pragma once
#include "Singleton.h"
#include <vector>

namespace peach
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager() = default;
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;


		Scene& CreateScene(const std::string& name);
		std::shared_ptr<Scene> GetScene(const std::string& name);

		void SetActiveGameScene(const std::string& sceneName);

		void Initialize();
		void PostInitialize();

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene>m_ActiveScene;
	};
}
