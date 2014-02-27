#define PI 3.1415926535

#include "Ball.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

Ball::Ball(float centerX, float centerY, float radius)
    : Entity(centerX, centerY, radius * 2.f, radius * 2.f)
    , m_VelocityX(randomVelocity())
    , m_VelocityY(randomVelocity())
    , m_Speed(300.f / 1000.f)
    , m_Rotation(0.f)
    , m_RotationDirection(1.f)
    , m_RotationSpeed(5.f)
{
    setupVertices();
    setupColors();
}

float Ball::randomVelocity() const
{
    // Generate a random number between -1 and 1 inclusive
    float vel = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(1.f - (-1.f))));

    return vel;
}

void Ball::setupVertices()
{
    std::cout << "Setting up ball vertices" << std::endl;

    float vertices[360];

    for (unsigned i = 0; i < 360; i += 3)
    {
        float angleRads = (i * PI) / 180.f;

        vertices[i] = (cos(angleRads) * (m_Width / 2.f));       // X
        vertices[i + 1] = (sin(angleRads) * (m_Height / 2.f));  // Y
        vertices[i + 2] = 0.f;                                       // Z
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
        // == Yellow section
        else if (i >= 120 && i < 240)
        {
            colors[i] = 1.f;
            colors[i + 1] = 0.9f;
            colors[i + 2] = 0.f;
        }
        // == Cyan section
        else if (i >= 240 && i < 360)
        {
            colors[i] = 0.f;
            colors[i + 1] = 1.f;
            colors[i + 2] = 1.f;
        }
    }

    glGenBuffers(1, &m_ColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 360, colors, GL_STATIC_DRAW);
}

void Ball::hitPaddle()
{
    m_VelocityX = -m_VelocityX;
    m_RotationDirection = -m_RotationDirection;
}

void Ball::checkWallCollisions()
{
    // == Right wall
    if ((m_X + m_Width / 2.f) >= 640.f)
    {
        m_VelocityX = -m_VelocityX;
        m_RotationDirection = -m_RotationDirection;
    }

    // == Bottom wall
    if ((m_Y - m_Height / 2.f) <= 0.f)
    {
        m_VelocityY = -m_VelocityY;
        m_RotationDirection = -m_RotationDirection;
    }

    // == Top wall
    if ((m_Y + m_Height / 2.f) >= 480.f)
    {
        m_VelocityY = -m_VelocityY;
        m_RotationDirection = -m_RotationDirection;
    }
}

void Ball::update(int delta)
{
    m_X += (m_VelocityX * m_Speed * delta);
    m_Y += (m_VelocityY * m_Speed * delta);

    m_Rotation += (m_RotationSpeed * m_RotationDirection);

    checkWallCollisions();
}

void Ball::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glPushMatrix();

    glTranslatef(m_X, m_Y, 0.f);
    glRotatef(m_Rotation, 0.f, 0.f, 1.f);

    glDrawArrays(GL_POINTS, 0, 360);

    glPopMatrix();
}

Ball::~Ball()
{
    std::cout << "Freeing ball resources" << std::endl;

    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}
