#include "Vehicle.hpp"
#include <cstdlib>
#include <iostream>

Vehicle::Vehicle() {
	size = SIZE_ + SIZE_VAR * (double(rand()) / RAND_MAX);
}

int Velhicle::getSize() {
	return size;
}