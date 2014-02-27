#ifndef BALL_HPP
#define BALL_HPP

#include "Entity.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

class Ball : public Entity
{
public:
    Ball(float centerX, float centerY, float radius);
    ~Ball();

    void update(int delta) override;
    void render() override;

    void hitPaddle();
    void hitHorizontalWall();
    void hitVerticalWall();

    void reset(bool fullReset = false);

private:
    void setupVertices();
    void setupColors();

    void setRandomVelocity();

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    float m_VelocityX;
    float m_VelocityY;

    float m_Speed;
    const float m_SpeedIncrease;

    float m_Rotation;
    float m_RotationDirection;
    float m_RotationSpeed;
    const float m_RotationSpeedIncrease;
};

#endif // BALL_HPP
