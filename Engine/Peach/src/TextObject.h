#pragma once
#include "Transform.h"

namespace peach
{
	class ComponentBase;

	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		void Initialize() override;
		void FixedUpdate() override;
		void Update() override;
		void LateUpdate() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextObject();
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		//Component stuff
		void AddComponent(ComponentBase* newComponent);
		template<class T>
		T* GetComponent()const;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		std::vector<ComponentBase*> m_pComponents{};
	};

	template<class T>
	T* TextObject::GetComponent() const
	{
		for (ComponentBase* c : m_pComponents)
		{
			if (typeid(T) == typeid(*c))
			{
				return reinterpret_cast<T*>(c);
			}
		}
		return nullptr;
	}
}
