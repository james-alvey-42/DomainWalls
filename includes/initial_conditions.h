#ifndef _INIT_CONDS_
#define _INIT_CONDS_
/* START: InitialiConditions Class Declaration */

class InitialConditions
{
public:
	InitialConditions();
	float phi0(float);
	float psi0(float);
	void set_L(float iL){ L = iL; };
	void set_eta(float iet){ eta = iet; };
	void set_sigma(float is){ sigma = is;};
	void set_left(float ll){ left = ll;};
	void set_right(float rr){ right = rr;};

private:
	float L, sigma, left, right, eta;
};

/* END: InitialConditions Class Declaration */

#endif