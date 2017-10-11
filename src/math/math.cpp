#include "math.h"

#include <cmath>

double Math::Gauss2(double sigma, int x, int y)
{
    return (1.0/(2*PI*sigma*sigma))*exp(-(x*x+y*y)/(2*sigma*sigma));
}

double Math::ToRadians(double degrees)
{
    return PI*degrees/180.0;
}

double Math::ToDegrees(double radians)
{
    return 180.0*radians/PI;
}

double Math::Bisection(double a, double b, const Func &f, double eps)
{
    double x = (a + b)*0.5;
    float check = f(x)*f(a);
    if (check != 0)
    {
        while (fabs(b-a) > eps*fabs(x) + eps)
        {
            if (check < 0)
                b = x;
            else
                a = x;
            x = (a + b)*0.5;
            check = f(x)*f(a);
        }
        return x;
    }
    else
    {
        if (f(x) == 0)
            return x;
        else
            return a;
    }
}
