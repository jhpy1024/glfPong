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

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    const float m_Radius;

    float m_X;
    float m_Y;

    float m_VelocityX;
    float m_VelocityY;
};

#endif // BALL_HPP
