#ifndef Roadway_HPP
#define Roadway_HPP

#include "linked_queue.h"
#include "Vehicle.hpp"
#include "Semaphore.hpp"

/**
 * @brief Class that represents a roadway
 */
class Roadway {
protected:
	semaphore& semaphore;
	LinkedQueue<Vehicle> queue;
	int size = 0, velocity = 0;
	int in = 0, out = 0;
	double probLeft, probRight;
	static int totalIn, totalOut;

public:
	Roadway(semaphore& semaphore, int size, int velocity, double probLeft, double probRight);
	void add(Vehicle vehicle);
	Vehicle pop();
	bool empty();
	virtual Roadway& moveVehicle();
	int timeToTravel() const;
	int entered() const;
	int left() const;
	int areIn() const;
	static int totalIn();
	static int totalOut();
};

/**
 * @brief Source Roadway -- creates vehicles
 */
class Source : public Roadway {
private:
	int fixedFrequency = 0, variableFrequency = 0;
	Roadway &rightExit, &straightExit, &leftExit;

public:
	Source(semaphore& semaphore, int size, int velocity, int fixedFrequency, 
		int variableFrequency, Roadway& rightExit, Roadway& straightExit, Roadway& leftExit,
		double probLeft, double probRight);

	void createsVehicle();
	virtual Roadway& moveVehicle();
	int nextEventsTime(int time);
};

/**
 * @brief Central Roadway
 */
class CentralRoadway : public Roadway {
private:
	Roadway &rightExit, &straightExit, &leftExit;

public:
	CentralRoadway(semaphore& semaphore, int size, int velocity,
		Roadway& rightExit, Roadway& straightExit, Roadway& leftExit,
		double probLeft, double probRight);
	virtual Roadway& moveVehicle();
};

/**
 * @brief Removes vehicles from the system
 */
class ExitRoadway : public Roadway {
public:
	ExitRoadway(semaphore& semaphore, int size, int velocity, 
		double probLeft, double probRight);
};

#endif  // Roadway_HPP