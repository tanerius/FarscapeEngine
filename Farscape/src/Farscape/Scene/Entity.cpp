#include "fspch.h"
#include "Entity.h"

namespace Farscape {

    Entity::Entity(const std::string& name)
        : m_Name(name), m_Transform(1.0f)
    {

    }

    Entity::~Entity()
    {

    }

}