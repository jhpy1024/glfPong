#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
    Entity(float x, float y, float width, float height);
    virtual ~Entity() {};

    virtual void update() = 0;
    virtual void render() = 0;

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

protected:
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;
};

#endif // ENTITY_HPP
