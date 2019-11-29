#ifndef _DOMAIN_WALL_
#define _DOMAIN_WALL_
#include <vector>
#include <string>
/* START: DomainWall Class Declaration */

#include "potential.h"
#include "initial_conditions.h"

class DomainWall
{
public:
	DomainWall();
	int get_L() { return L; };
	float get_dt() { return dt; };
	float get_dx() { return dx; };
	int get_N() { return N; };
	float get_lamda() { return lambda; };
	float get_eta() { return eta; };
	float get_alpha() { return alpha; };
	float get_tmax() { return tmax; };
	std::vector<float> get_current_phi() { return current_state_phi; };
	std::vector<float> get_new_phi() { return new_state_phi; };
	std::vector<float> get_current_psi() { return current_state_psi; };
	std::vector<float> get_new_psi() { return new_state_psi; };

	void set_initial_conditions();
	void take_step();
	void write_x_array(std::string);
	void write_current_phi(std::string);
	void write_current_psi(std::string);
	void write_params(std::string);

private:
	int N, steps;
	float L, lambda, eta, alpha, tmax, sigma, left, right, epsilon;
	float dt, dx;
	std::vector<float> current_state_phi;
	std::vector<float> new_state_phi;
	std::vector<float> current_state_psi;
	std::vector<float> new_state_psi;
	Potential potential;
	InitialConditions initial_conditions;
};

/* END: Domain Wall Class Declaration */

#endif