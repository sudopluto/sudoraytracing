#include "Renderer.h"

#include "Walnut/Random.h"

void Renderer::OnResize(uint32_t width, uint32_t height) {
    
    if (!m_Image) {
        m_Image = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
    } else {
        //exit early, no new image buff needed
        if (width == m_Image->GetWidth() && height == m_Image->GetHeight()) {
            return;
        }
        m_Image->Resize(width, height);
    }

    delete[] m_ImageData;
    m_ImageData = new uint32_t[width * height];
}

void Renderer::Render() {
    for (uint32_t y = 0; y < m_Image->GetHeight(); ++y) {
        for (uint32_t x = 0; x < m_Image->GetWidth(); ++x) {
            glm::vec3 coord = { x / (float)m_Image->GetWidth(), y / (float)m_Image->GetHeight(), -1.0f};
            // remap 0->1, -1->1
            coord *= 2.0f;
            coord -= 1.0f;
            m_ImageData[(y * m_Image->GetWidth()) + x] = PerPixel(coord);
        }
    }

    m_Image->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec3 coord) {

    glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
    glm::vec3 rayDirection = coord;
    float radius = 0.5f;
    //rayDirection = glm::normalize(rayDirection);

    // inserting our quadratic circle intersection calculation here
    // where:
    // a(x,y) = ray origin
    // b(x,y) = ray direction
    // r      = radius
    // t      = hit distance
    // (bx^2 + by^2)*t^2 + (ax*bx + ay*by)*2*t + (ax^2 + ay^2 - r^2) = 0

    
    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - (radius * radius);

    //quadradic formuala discrim
    // b^2 - 4*a*c

    float discrim = (b * b) - (4.0f * a * c);

    if (discrim >- 0.0f)
        return 0xffff00ff;

    return 0xff000000;
}

