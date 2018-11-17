#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include "math/math.h"

class InputControl
{
private:
    float amt;

public:
    InputControl();

    void addAmt(float amtToAdd);
    float getAmt();
};

inline InputControl::InputControl() : amt(0.0f) {}

inline void InputControl::addAmt(float amtToAdd)
{
    amt += amtToAdd;
}
inline float InputControl::getAmt()
{
    return Math::clamp(amt, -1.0f, 1.0f);
}

#endif // INPUT_CONTROL_H
