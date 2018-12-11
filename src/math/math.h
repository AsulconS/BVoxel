#ifndef MATH_H
#define MATH_H

namespace Math
{
    template <typename T>
    T clamp(const T& val, const T& min, const T& max)
    {
        if(val > max)
            return max;
        else if(val > min)
            return val;
        else
            return min;
    }

    template <typename T>
    T max(const T& val1, const T& val2)
    {
        return (val1 > val2) ? val1 : val2;
    }

    template <typename T>
    T min(const T& val1, const T& val2)
    {
        return (val1 < val2) ? val1 : val2;
    }
}

#endif // MATH_H
