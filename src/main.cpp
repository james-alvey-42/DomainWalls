#include <iostream>
#include <string>
#include <fstream>

#include "domain.h"
#include "potential.h"
#include "initial_conditions.h"

int main(){
	DomainWall solution;
	solution.write_x_array("output/x.txt");

	solution.set_initial_conditions();
    solution.write_current_phi("output/phi.txt");
    solution.write_current_psi("output/psi.txt");

    int num_iterations = solution.get_tmax() / solution.get_dt();

    for (int step = 0; step < num_iterations; step++){
    	solution.take_step();
    	solution.write_current_phi("output/phi.txt");
    	solution.write_current_psi("output/psi.txt");
    }

    solution.write_params("output/params.txt");

	return 0;
}
