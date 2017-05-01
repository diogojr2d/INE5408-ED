// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

/**
 * @brief Class that represents a vehicle.
 */

class Vehicle {
private:
	int size;  // Vehicle's size
	const int SIZE_ = 5, SIZE_VAR = 4;  // Fixed and variable sizes
public:
	Vehicle();  // Constructor
	int getSize();  // Returns the vehicle's size
};

#endif  // VEHICLE_HPP