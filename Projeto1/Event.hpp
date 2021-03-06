// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include "Roadway.hpp"
#include "Semaphore.hpp"
#include "Vehicle.hpp"
#include "doubly_linked_list.h"

/**
 * @brief Base class for all Events
*/
class Event {
private:
	int time = 0; // time the event will run

public:
	explicit Event(int t); // Constructor
	virtual ~Event() {}
	virtual void print();

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
 * @brief Event to Create a Vehicle in a Source Roadway
*/
class CreateVehicleEv : public Event {
private:
	Source& source;
public:
	CreateVehicleEv(int t, Source& source_);
	DoublyLinkedList<Event*> run();
	void print();
};

/**
 * @brief Event to Remove a Vehicle out of an Exit Roadway
*/
class RemoveVehicleEv : public Event {
private:
	ExitRoadway& exitRoadway;
public:
	RemoveVehicleEv(int t, ExitRoadway& exitRoadway_);
	DoublyLinkedList<Event*> run();
	void print();
};

/**
 * @brief Event to change a vehicle's roadway, when it gets to a semaphore
 */
class ChangeRoadwayEv : public Event {
private:
	Roadway& roadway;
public:
	ChangeRoadwayEv(int t, Roadway& p_);
	DoublyLinkedList<Event*> run();
	void print();
};

/**
 * @brief Event to change a semaphore's state
 */
class OpenSemaphoreEv : public Event {
private:
	Semaphore& semaphore;
	int frequency;
public:
	OpenSemaphoreEv(int t, Semaphore& s, int f);
	DoublyLinkedList<Event*> run();
	void print();
};

#endif // EVENT_HPP