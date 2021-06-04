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

        void Render() const override;
        void SetTexture(const std::string& assetPath);
        void SetDimensions(float width, float height);

    private:
        std::shared_ptr<Texture2D> m_Texture{};
        glm::vec3 m_Dimensions = { -1,-1 ,0};
    };
}