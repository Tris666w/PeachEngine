#pragma once
#include "ComponentBase.h"
namespace peach
{
	class Texture2D;
	class Font;
	class TextComponent final : public ComponentBase
	{
	public:
		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;

	};

}