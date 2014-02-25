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

    void update() override;
    void render() override;

private:
    void setupVertices();
    void setupColors();

    float randomVelocity() const;

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    float m_VelocityX;
    float m_VelocityY;

    const float m_Speed;

    float m_Rotation;
    float m_RotationDirection;
    const float m_RotationSpeed;
};

#endif // BALL_HPP
