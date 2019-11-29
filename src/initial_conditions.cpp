#include <math.h>

#include "initial_conditions.h"

/* START: InitialConditions Class Implementation */

InitialConditions::InitialConditions()
{
	L = 1.;
	sigma = 0.01 * L;
	left = 0.25 * L;
	right = 0.75 * L;
	eta = 0.01;
};

float InitialConditions::phi0(float x)
{
	return eta * (-1 + tanhf((x - left)/sigma) - tanhf((x - right)/sigma));
};

float InitialConditions::psi0(float x)
{
	return 0.0;
};

/* END: InitialConditions Class Implementation */