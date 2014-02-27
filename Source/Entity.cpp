#include "Entity.hpp"

Entity::Entity(float x, float y, float width, float height)
    : m_X(x)
    , m_Y(y)
    , m_Width(width)
    , m_Height(height)
{

}

// == Getters ==
float Entity::getX() const
{
    return m_X;
}

float Entity::getY() const
{
    return m_Y;
}

float Entity::getWidth() const
{
    return m_Width;
}

float Entity::getHeight() const
{
    return m_Height;
}
// =============


// == Setters ==
void Entity::setX(float x)
{
    m_X = x;
}

void Entity::setY(float y)
{
    m_Y = y;
}

void Entity::setPosition(float x, float y)
{
    setX(x);
    setY(y);
}
// =============

