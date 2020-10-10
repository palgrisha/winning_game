#ifndef TWEENCURVES_H
#define TWEENCURVES_H
#include <functional>

typedef std::function<float(float)> lambda_float;

extern lambda_float sin_in_out;
extern lambda_float sin_out;
extern lambda_float linear;

#endif // TWEENCURVES_H
