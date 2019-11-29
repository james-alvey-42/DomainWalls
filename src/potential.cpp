#include "potential.h"

/* START: Potential Class Implementation */

Potential::Potential()
{
	lambda = 2000.0;
	eta = 0.01;
};

float Potential::dVdphi(float phi)
{
	return lambda * phi * (phi*phi - eta*eta) - (epsilon/(2.0 * eta));
};

/* END: Potential Class Implementation */