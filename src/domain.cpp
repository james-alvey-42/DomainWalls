/* Standard Includes */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "domain.h"
#include "potential.h"
#include "initial_conditions.h"

/* START: DomainWall Class Implementation */

DomainWall::DomainWall()
{
	L = 1.;
	N = 200;
	steps = 0;
	sigma = 0.01 * L;
	left = 0.25 * L;
	right = 0.75 * L;
	lambda = 2000.0;
	epsilon = -0.00001;
	eta = 0.01;
	alpha = 0.01;
	tmax = 1.0;

	potential.set_lambda(lambda);
	potential.set_eta(eta);
	potential.set_epsilon(epsilon);

	initial_conditions.set_L(L);
	initial_conditions.set_sigma(sigma);
	initial_conditions.set_left(left);
	initial_conditions.set_right(right);
	initial_conditions.set_eta(eta);

	dx = (float)L / N ;
	dt = alpha * dx;
	std::vector<float> cvec(N);
	current_state_phi = cvec;
	std::vector<float> nvec(N);
	new_state_phi = nvec;
	std::vector<float> cpvec(N);
	current_state_psi = cpvec;
	std::vector<float> npvec(N);
	new_state_psi = npvec;
};

void DomainWall::set_initial_conditions()
{
	if (steps == 0){

		for (int index = 0; index < N; index++){
			current_state_phi[index] = initial_conditions.phi0(index * dx);
			current_state_psi[index] = initial_conditions.psi0(index * dx);
			new_state_phi[index] = initial_conditions.phi0(index * dx);
			new_state_psi[index] = initial_conditions.psi0(index * dx);
		}
		steps = 1;
	}
};

void DomainWall::take_step()
{
	current_state_phi = new_state_phi;
	current_state_psi = new_state_psi;


	for (int index = 0; index < N; index++)
	{
		new_state_phi[index] = current_state_phi[index] + dt * current_state_psi[index];
		
		new_state_psi[index] = current_state_psi[index] + dt * alpha * (current_state_phi[(index + 1) % N] - 2 * current_state_phi[index] + current_state_phi[(N + index - 1) % N]) - potential.dVdphi(current_state_phi[index]);
	}
	steps += 1;
};

void DomainWall::write_x_array(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename);
	for (int index = 0; index < N; index++){
		outfile << index * dx << " ";
	}
	outfile << "\n";
}

void DomainWall::write_current_phi(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::app);
	for (int index = 0; index < N; index++){
		outfile << current_state_phi[index] << " ";
	}
	outfile << "\n";
}

void DomainWall::write_current_psi(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::app);
	for (int index = 0; index < N; index++){
		outfile << current_state_psi[index] << " ";
	}
	outfile << "\n";
}

void DomainWall::write_params(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::app);
	outfile << "steps" << " ";
	outfile << "dt" << " ";
	outfile << "dx" << " ";
	outfile << "L" << " ";
	outfile << "N" << " ";
	outfile << "lambda" << " ";
	outfile << "eta" << " ";
	outfile << "alpha" << " ";
	outfile << "tmax" << " ";
	outfile << "sigma" << " ";
	outfile << "left" << " ";
	outfile << "right" << "\n";

	outfile << steps << " ";
	outfile << dt << " ";
	outfile << dx << " ";
	outfile << L << " ";
	outfile << N << " ";
	outfile << lambda << " ";
	outfile << eta << " ";
	outfile << alpha << " ";
	outfile << tmax << " ";
	outfile << sigma << " ";
	outfile << left << " ";
	outfile << right << " ";
}

/* END: DomainWall Class Implementation */