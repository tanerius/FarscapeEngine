#pragma once
#include "Core.h"

namespace Farscape {

    class Timestep : public ITimestep
    {
    public:
        Timestep() {}
        Timestep(float) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMiliseconds() const { return m_Time * 1000.0f; }
    private:
        float m_Time = 0.0f;
    };

}
