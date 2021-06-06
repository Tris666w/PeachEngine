#pragma once
#include "ComponentBase.h"
#include "imgui.h"

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
		void SetPosition(ImVec2 relativePos);
		void SetColor(SDL_Color newColor);

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
		ImVec2 m_relativePos;
		SDL_Color m_Color = { 255,255,255 };
	};

}
