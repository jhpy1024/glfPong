#define PI 3.1415926535

#include "Ball.hpp"

#include <iostream>
#include <ctime>
#include <random>

Ball::Ball(float centerX, float centerY, float radius)
    : Entity(centerX, centerY, radius, radius)
    , m_VelocityX(randomVelocity())
    , m_VelocityY(randomVelocity())
    , m_Speed(5.f)
    , m_Rotation(0.f)
    , m_RotationDirection(1.f)
    , m_RotationSpeed(4.f)
{
    setupVertices();
    setupColors();
}

float Ball::randomVelocity() const
{
    static bool engineSeeded = false;

    static std::default_random_engine randEng;
    std::uniform_real_distribution<float> distribution(-1.f, 1.f);

    if (!engineSeeded)
    {
        randEng.seed(time(NULL));
        engineSeeded = true;
    }

    return distribution(randEng);
}

void Ball::setupVertices()
{
    std::cout << "Setting up ball vertices" << std::endl;

    float vertices[360];

    for (unsigned i = 0; i < 360; i += 3)
    {
        float angleRads = (i * PI) / 180.f;

        vertices[i] = (std::cos(angleRads) * (m_Width / 2.f));      // X
        vertices[i + 1] = (std::sin(angleRads) * (m_Width / 2.f));  // Y
        vertices[i + 2] = 0.f;                                      // Z
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

void Ball::hitPaddle()
{
    m_VelocityX = -m_VelocityX;
}

void Ball::checkWallCollisions()
{
    // == Right wall
    if ((m_X + m_Width / 2.f) >= 640.f)
        m_VelocityX = -m_VelocityX;

    // == Bottom wall
    if ((m_Y - m_Height / 2.f) <= 0.f)
        m_VelocityY = -m_VelocityY;

    // == Top wall
    if ((m_Y + m_Height / 2.f) >= 480.f)
        m_VelocityY = -m_VelocityY;
}

void Ball::update()
{
    m_X += (m_VelocityX * m_Speed);
    m_Y += (m_VelocityY * m_Speed);

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
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_ColorBuffer);
}
