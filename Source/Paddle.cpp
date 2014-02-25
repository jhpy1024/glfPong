#include "Paddle.hpp"

#include <iostream>

Paddle::Paddle(float x, float y, float width, float height)
    : m_X(x)
    , m_Y(y)
    , m_Width(width)
    , m_Height(height)
{
    setupVertices();
    setupColors();
}

void Paddle::setupVertices()
{
    std::cout << "Setting up paddle vertices" << std::endl;

    float vertices[] =
    {
        m_X, m_Y, 0.f,                          // Bottom left
        m_X + m_Width, m_Y, 0.f,                // Bottom right
        m_X + m_Width, m_Y + m_Height, 0.f,     // Top right
        m_X, m_Y + m_Height, 0.f                // Top left
    };

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
}

void Paddle::setupColors()
{
    std::cout << "Setting up paddle colors" << std::endl;

    float colors[] =
    {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f
    };

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);
}

void Paddle::update()
{

}

void Paddle::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Paddle::moveUp()
{

}

void Paddle::moveDown()
{

}

Paddle::~Paddle()
{
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}
