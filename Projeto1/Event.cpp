// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include "Event.hpp"
#include "Exceptions.hpp"
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

CreateVehicleEv::CreateVehicleEv(int t, Source& source_) :
	Event(t), source(source_) {}

RemoveVehicleEv::RemoveVehicleEv(int t, ExitRoadway& exitRoadway_) :
	Event(t), exitRoadway(exitRoadway_) {}

ChangeRoadwayEv::ChangeRoadwayEv(int t, Roadway& p_) :
	Event(t), roadway(p_) {}

OpenSemaphoreEv::OpenSemaphoreEv(int t, std::string m, Semaphore& s, int f) :
	Event(t), msg(m), semaphore(s), frequency(f) {}

DoublyLinkedList<Event*> CreateVehicleEv::run() {
	bool worked = true;

	try {
		source.createsVehicle();
	} catch (std::runtime_error& err) {
		worked = false;
	}

	DoublyLinkedList<Event*> newEvents;

	if (worked) {
		int nextEventsTime = source.nextEventsTime(getTime());

		newEvents.push_back(new CreateVehicleEv(nextEventsTime, source));

		newEvents.push_back(new ChangeRoadwayEv(nextEventsTime, source));
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
		nextRoadway = Roadway.moveVehicle();
	} catch (semaphoreNaoEstaNadirection& err) { // Corrigir Exceção *******
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

	newEvents.push_back(new OpenSemaphoreEv(getTime()+frequency, msg, semaphore, frequency));

	return newEvents;
}