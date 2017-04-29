#ifndef EVENT_HPP
#define EVENT_HPP


/**
 * @brief Base class for all Events
*/
class Event {
private:
	int time = 0; // time the event will run

public:
	explict Event(int t); // Constructor
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
};

/**
 * @brief Event to Create a Vehicle in a Source Lane
*/
class CreateCarEv : public Event {
private:
	Source& source;
public:
	CreateCarEv(int t, Source& source_);
	DoublyLinkedList<Event*> run();
};

/**
 * @brief Event to Remove a Vehicle out of an Exit Lane
*/
class RemoveCarEv : public Event {
private:
	ExitLane& exitLane;
public:
	CreateCarEv(int t, Source& source_);
	DoublyLinkedList<Event*> run();
};

#endif // EVENT_HPP