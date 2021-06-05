#pragma once
#include "ComponentBase.h"

namespace peach
{
    class Texture2D;
    class TextureComponent final : public ComponentBase
    {
    public:
        TextureComponent() = default;
        TextureComponent(const std::string& assetPath, float width = -1, float height = -1);
        ~TextureComponent() override = default;

        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) = delete;

        void Initialize() override;
        void Update() override;
        void Render() const override;

        void SetTexture(const std::string& assetPath);
        void SetDimensions(float width, float height);
        SDL_Rect GetTextureDimensions() const;

        void SetSourceRect(SDL_Rect srcRect);

        SDL_Rect GetSourceRect()const { return m_SourceRect; }

    private:
        std::shared_ptr<Texture2D> m_Texture{};
        glm::vec3 m_Dimensions = { -1,-1 ,0 };
        SDL_Rect m_SourceRect{ -1,-1,-1,-1 };
        bool m_SourceRectSet = false;
    };
}