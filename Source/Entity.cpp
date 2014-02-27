#include "Entity.hpp"

Entity::Entity(float x, float y, float width, float height)
    : m_X(x)
    , m_Y(y)
    , m_Width(width)
    , m_Height(height)
{

}

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
