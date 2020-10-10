#include "tweencurves.h"
#include <math.h>


lambda_float sin_in_out = [](float x)
{
    return sinf(x * M_PI - M_PI / 2) / 2 + 0.5;
};

lambda_float sin_out = [](float x)
{
    return sinf(x * M_PI / 2);
};

lambda_float linear = [](float x)
{
    return x;
};


