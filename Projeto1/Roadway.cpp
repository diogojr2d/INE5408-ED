// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include "Roadway.hpp"
#include <cstdlib>

int Roadway::totalIn_ = 0;
int Roadway::totalOut_ = 0;

Roadway::Roadway(Semaphore& semaphore, int size, int velocity,
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
	in++;
	totalIn_++;
	queue.enqueue(v);
}

Vehicle Roadway::pop() {
	auto v = queue.dequeue();
	size += v.getSize();
	out++;
	totalOut_++;
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
	return out;
}

int Roadway::areIn() const {
	return in-out;
}

int Roadway::totalIn() {
	return totalIn_;
}

int Roadway::totalOut() {
	return totalOut_;
}

CentralRoadway::CentralRoadway(Semaphore& semaphore, int size, int velocity,
		Roadway& rightExit, Roadway& straightExit, Roadway& leftExit,
		double probLeft, double probRight):
    Roadway(semaphore, size, velocity, probLeft, probRight),
	rightExit(rightExit),
	straightExit(straightExit),
	leftExit(leftExit) {}


Roadway& CentralRoadway::moveVehicle() {
	if (!semaphore.getOpen())
		throw std::runtime_error("Red Semaphore");

	double r = rand()/RAND_MAX;
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

Source::Source(Semaphore& semaphore, int size, int velocity, int fixedFrequency,
		int variableFrequency, Roadway& rightExit, Roadway& straightExit,
		Roadway& leftExit, double probLeft, double probRight):
	Roadway(semaphore, size, velocity, probLeft, probRight),
	fixedFrequency(fixedFrequency - variableFrequency),
	variableFrequency(2*variableFrequency),
	rightExit(rightExit),
	straightExit(straightExit),
	leftExit(leftExit) {}

void Source::createVehicle() {
	Vehicle v;
	add(v);
}

Roadway& Source::moveVehicle() {
	if (!semaphore.getOpen())
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

ExitRoadway::ExitRoadway(Semaphore& semaphore, int size, int velocity):
	Roadway(semaphore, size, velocity, 0, 0) {}