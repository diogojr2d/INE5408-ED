// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include "Event.hpp"
#include <iostream>

bool Event::operator>(const Event& e) const {
	return time > e.time;
}

bool Event::operator<(const Event& e) const {
	return time < e.time;
}

bool Event::operator==(const Event& e) const {
	return time == e.time;
}

bool Event::operator!=(const Event& e) const {
	return time != e.time;
}

bool Event::operator>=(const Event& e) const {
	return time >= e.time;
}

bool Event::operator<=(const Event& e) const {
	return time <= e.time;
}

bool Event::operator>(int i) const {
	return time > i;
}

bool Event::operator<(int i) const {
	return time < i;
}

bool Event::operator==(int i) const {
	return time == i;
}

bool Event::operator!=(int i) const {
	return time != i;
}

bool Event::operator>=(int i) const {
	return time >= i;
}

bool Event::operator<=(int i) const {
	return time <= i;
}

Event::Event(int t) : time(t) {}

DoublyLinkedList<Event*> Event::run() {
	throw std::logic_error("Event::run can not be called");
}

int Event::getTime() const {
	return time;
}

void Event::print() {
	printf("Evento Geral.\n");
}

CreateVehicleEv::CreateVehicleEv(int t, Source& source_) :
	Event(t), source(source_) {}
	
void CreateVehicleEv::print() {
	printf("CreateVehicleEv (%d s).\n", getTime());
}

RemoveVehicleEv::RemoveVehicleEv(int t, ExitRoadway& exitRoadway_) :
	Event(t), exitRoadway(exitRoadway_) {}

void RemoveVehicleEv::print() {
	printf("RemoveVehicleEv (%d s).\n", getTime());
}

ChangeRoadwayEv::ChangeRoadwayEv(int t, Roadway& p_) :
	Event(t), roadway(p_) {}

void ChangeRoadwayEv::print() {
	printf("ChangeRoadwayEv (%d s).\n", getTime());
}

OpenSemaphoreEv::OpenSemaphoreEv(int t, Semaphore& s, int f) :
	Event(t), semaphore(s), frequency(f) {}

void OpenSemaphoreEv::print() {
	printf("OpenSemaphoreEv (%d s).\n", getTime());
}

DoublyLinkedList<Event*> CreateVehicleEv::run() {
	bool worked = true;

	try {
		source.createVehicle();
	} catch (std::runtime_error& err) {
		worked = false;
	}

	DoublyLinkedList<Event*> newEvents;

	if (worked) {
		int nextEventsTime = source.nextEventsTime(getTime());

		newEvents.push_back(new CreateVehicleEv(nextEventsTime, source));

		newEvents.push_back(new ChangeRoadwayEv(nextEventsTime+1, source));
	} else {
		newEvents.push_back(new CreateVehicleEv(getTime()+5, source));
	}

	return newEvents;
}

DoublyLinkedList<Event*> RemoveVehicleEv::run() {
	exitRoadway.pop();

	DoublyLinkedList<Event*> newEvents;

	return newEvents;
}

DoublyLinkedList<Event*> ChangeRoadwayEv::run() {
	DoublyLinkedList<Event*> newEvents;

	Roadway* nextRoadway;

	// Try to move vehicle, if not possible creates new event 5s later
	try {
		nextRoadway = &(roadway.moveVehicle());
	} catch (std::runtime_error& err) {
		newEvents.push_back(new ChangeRoadwayEv(getTime()+5, roadway));
		return newEvents;
	}

	// Check if nextRoadway is an ExitRoadway
	if (ExitRoadway* s = dynamic_cast<ExitRoadway*>(nextRoadway)) {
		newEvents.push_back(new RemoveVehicleEv(getTime()+s->timeToTravel(), *s));
	} else {
		newEvents.push_back(new ChangeRoadwayEv(getTime()+nextRoadway->timeToTravel(), *nextRoadway));
	}

	return newEvents;

}

DoublyLinkedList<Event*> OpenSemaphoreEv::run() {
	semaphore.nextState();

	DoublyLinkedList<Event*> newEvents;

	newEvents.push_back(new OpenSemaphoreEv(getTime()+frequency, semaphore, frequency));

	return newEvents;
}