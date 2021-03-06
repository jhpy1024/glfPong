#include "Paddle.hpp"

#include <iostream>

Paddle::Paddle(float x, float y, float width, float height)
    : Entity(x, y, width, height)
    , m_Speed(350.f / 1000.f) // pixels per second
    , m_VelocityY(0.f)
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
        // == Dark red ==
        0.5f, 0.f, 0.f,
        0.5f, 0.f, 0.f,
        // == Red ==
        1.f, 0.f, 0.f,
        1.f, 0.f, 0.f
    };

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);
}

void Paddle::update(int delta)
{
    if (atTop())
    {
        m_VelocityY = 0.f;
        m_Y = 0.f;
    }
    else if (atBottom())
    {
        m_VelocityY = 0.f;
        m_Y = 480.f - m_Height;
    }

    m_Y += (m_VelocityY * m_Speed * delta);
}

void Paddle::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glPushMatrix();
    glTranslatef(m_X, m_Y, 0.f);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glPopMatrix();
}

bool Paddle::atTop() const
{
    return m_Y < 0.f;
}

void Paddle::moveUp()
{
    m_VelocityY = -1.f;
}

bool Paddle::atBottom() const
{
    return (m_Y + m_Height) > 480.f;
}

void Paddle::moveDown()
{
    m_VelocityY = 1.f;
}

void Paddle::stopMoving()
{
    m_VelocityY = 0.f;
}

Paddle::~Paddle()
{
    std::cout << "Freeing paddle resources" << std::endl;

    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}
