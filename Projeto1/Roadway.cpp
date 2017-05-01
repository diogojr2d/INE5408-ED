// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include "Roadway.hpp"
#include <cstdlib>
#include <sstream>

int Roadway::totalIn = 0;
int Roadway::totalOut = 0;

Roadway::Roadway(semaphore& semaphore, int size, int velocity,
		double probLeft, double probRight):
	semaphore(semaphore),
	size(size),
	velocity(velocity),
	probLeft(probLeft),
	probRight(probRight) {}

void Roadway::add(Vehicle v) {
	if (v.getSize() > size) {
		throw std::runtime_error("Roadway currently full");
	}

	size -= v.getSize();
	++in;
	++totalIn;
	queue.enqueue(v);
}

Vehicle Roadway::pop() {
	auto v = queue.dequeue();
	size += v.getSize();
	++left;
	++totalOut;
	return v;
}

bool Roadway::empty() {
	return queue.empty();
}

Roadway& Roadway::moveVehicle() {
	throw std::logic_error("Roadway::moveVehicle not implemented");
}

int Roadway::timeToTravel() const {
	return size / velocity / 3.6;
}

int Roadway::entered() const {
	return in;
}

int Roadway::left() const {
	return left;
}

int Roadway::areIn() const {
	return entered-left;
}

int Roadway::totalIn() {
	return totalIn;
}

int Roadway::totalOut() {
	return totalOut;
}

CentralRoadway::CentralRoadway(semaphore& s, int size, int velocity,
		Roadway& rightExit, Roadway& straightExit, Roadway& leftExit):
	Roadway(semaphore, size, velicity),
	rightExit(rightExit),
	straightExit(straightExit),
	leftExit(leftExit) {}


Roadway& CentralRoadway::moveVehicle() {
	if (!semaphore.open())
		throw std::runtime_error("Red Semaphore");

	double r = (rand())/RAND_MAX;
	auto v = pop();

	if (r > probRight) {
		rightExit.add(v);
		return rightExit;
	} else if (r < probLeft) {
		leftExit.add(v);
		return leftExit;
	}  else {
		straightExit.add(v);
		return straightExit;
	}
}

Source::Source(semaphore& semaphore, int size, int velocity, int fixedFrequency,
		int variableFrequency, Roadway& rightExit, Roadway& straightExit,
		Roadway& leftExit, double probLeft, double probRight):
	Roadway(semaphore, size, velocity, probLeft, probRight),
	fixedFrequency(fixedFrequency - variableFrequency),
	variableFrequency(2*variableFrequency),
	rightExit(rightExit),
	straightExit(straightExit),
	leftExit(leftExit) {}

void Source::createVehicle() {
	Vehicle c;
	add(c);
}

Roadway& Source::moveVehicle() {
	if (!semaphore.open())
		throw std::runtime_error("Red Semaphore");

	double r = (rand())/RAND_MAX;
	auto v = pop();

	if (r > probRight) {
		rightExit.add(v);
		return rightExit;
	} else if (r < probLeft) {
		leftExit.add(v);
		return leftExit;
	}  else {
		straightExit.add(v);
		return straightExit;
	}
}

int Source::nextEventsTime(int time) {
	return time + fixedFrequency + variableFrequency * float(rand())/RAND_MAX;
}

ExitRoadway::ExitRoadway(semaphore& semaphore, int size, int velocity,
		double probLeft, double probRight):
	Roadway(size, size, velocity, probLeft, probRight) {}