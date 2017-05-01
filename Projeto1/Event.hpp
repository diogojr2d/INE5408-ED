// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <memory>
#include "Roadway.hpp"
#include "Semaphore.hpp"
#include "Vehicle.hpp"
#include <vector>

/**
 * @brief Base class for all Events
*/
class Event {
private:
	int time = 0; // time the event will run

public:
	explict Event(int t); // Constructo
	virtual ~Event() {}

	/**
	 * @brief Run Event
	 * 
	 * @return List of new events to be inserted in main Events List
	*/
	virtual DoublyLinkedList<Event*> run();
	int getTime() const;

	// Overloading operators
	bool operator >(const Event& e) const;
	bool operator <(const Event& e) const;
	bool operator ==(const Event& e) const;
	bool operator !=(const Event& e) const;
	bool operator >=(const Event& e) const;
	bool operator <=(const Event& e) const;

	bool operator >(int i) const;
	bool operator <(int i) const;
	bool operator ==(int i) const;
	bool operator !=(int i) const;
	bool operator >=(int i) const;
	bool operator <=(int i) const;
};

/**
 * @brief Event to Create a Vehicle in a Source Lane
*/
class CreateVehicleEv : public Event {
private:
	Source& source;
public:
	CreateVehicleEv(int t, Source& source_);
	DoublyLinkedList<Event*> run();
};

/**
 * @brief Event to Remove a Vehicle out of an Exit Lane
*/
class RemoveVehicleEv : public Event {
private:
	ExitLane& exitLane;
public:
	CreateVehicleEv(int t, Source& source_);
	DoublyLinkedList<Event*> run();
};

/**
 * @brief Event to change a semaphore's state
 */
class OpenSemaphoreEv : public Event {
private:
	std::string msg;
	Semahpore& semaphore;
	int frequency;
public:
	OpenSemaphoreEv(int t, std::string msg, semaphore& s, int f);
	DoublyLinkedList<Event*> run();
};

/**
 * @brief Event to change a vehicle's roadway, when it gets to a semaphore
 */
class ChangeRoadwayEv : public Event {
private:
	Roadway& roadway;
public:
	ChangeRoadwayEv(int t, Roadway& p);
	DoublyLinkedList<Event*> run();
};

#endif // EVENT_HPP