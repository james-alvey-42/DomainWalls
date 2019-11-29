#ifndef _POTENTIAL_
#define _POTENTIAL_
/* START: Potential Class Declaration */

class Potential
{
public:
	Potential();
	float dVdphi(float);
	void set_lambda(float il){ lambda = il; };
	void set_eta(float ie) { eta = ie; };
	void set_epsilon(float iep) { epsilon = iep; };

private:
	float lambda, eta, epsilon;
};

/* END: Potential Class Declaration */

#endif