#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
    virtual ~Entity() {};

    virtual void update() = 0;
    virtual void render() = 0;
};

#endif // ENTITY_HPP
