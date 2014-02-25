#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include "Entity.hpp"

class Paddle : public Entity
{
public:
    Paddle(float x, float y, float width, float height);
    ~Paddle();

    void update() override;
    void render() override;

    void moveUp();
    void moveDown();

private:
    void setupVertices();
    void setupColors();

private:
    GLuint m_VertexBuffer;
    GLuint m_ColorBuffer;

    float m_X;
    float m_Y;

    const float m_Width;
    const float m_Height;
};

#endif // PADDLE_HPP
