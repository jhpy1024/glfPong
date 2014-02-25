#define PI 3.1415926535

#include "Ball.hpp"

#include <iostream>
#include <cmath>

Ball::Ball(float centerX, float centerY, float radius)
    : m_Radius(radius)
    , m_X(centerX)
    , m_Y(centerY)
{
    setupVertices();
    setupColors();
}

void Ball::setupVertices()
{
    std::cout << "Setting up ball vertices" << std::endl;

    float vertices[360];

    for (unsigned i = 0; i < 360; i += 3)
    {
        float angleRads = (i * PI) / 180.f;

        vertices[i] = (std::cos(angleRads) * m_Radius);      // X
        vertices[i + 1] = (std::sin(angleRads) * m_Radius);  // Y
        vertices[i + 2] = 0.f;                               // Z
    }

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 360, vertices, GL_STATIC_DRAW);
}

void Ball::setupColors()
{
    std::cout << "Setting up ball colors" << std::endl;

    float colors[360];

    for (unsigned i = 0; i < 360; i += 3)
    {
        // == Red section
        if (i >= 0 && i < 120)
        {
            colors[i] = 1.f;
            colors[i + 1] = 0.f;
            colors[i + 2] = 0.f;
        }
        // == Green section
        else if (i >= 120 && i < 240)
        {
            colors[i] = 0.f;
            colors[i + 1] = 1.f;
            colors[i + 2] = 0.f;
        }
        // == Blue section
        else if (i >= 240 && i < 360)
        {
            colors[i] = 0.f;
            colors[i + 1] = 0.f;
            colors[i + 2] = 1.f;
        }
    }

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 360, colors, GL_STATIC_DRAW);
}

void Ball::update()
{

}

void Ball::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glPushMatrix();
    glTranslatef(m_X, m_Y, 0.f);

    glDrawArrays(GL_POINTS, 0, 360);

    glPopMatrix();
}

Ball::~Ball()
{
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}
