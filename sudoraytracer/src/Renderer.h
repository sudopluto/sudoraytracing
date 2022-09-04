#pragma once

#include "Walnut/Image.h"

#include <memory>
#include <glm/glm.hpp>

class Renderer
{
public:
    Renderer() = default;

    void OnResize(uint32_t width, uint32_t height);
    void Render();

    std::shared_ptr<Walnut::Image> GetImage() const {return m_Image;}
private:
    uint32_t PerPixel(glm::vec3 coord);

    std::shared_ptr<Walnut::Image> m_Image;
    uint32_t* m_ImageData = nullptr;
};
