// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include "Vehicle.hpp"
#include <cstdlib>
#include <iostream>

Vehicle::Vehicle() {
	size = SIZE_ + SIZE_VAR * (double(rand()) / RAND_MAX);
}

int Vehicle::getSize() {
	return size;
}