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

std::vector<std::shared_ptr<Event>> Event::run() {
	throw std::logic_error("Event::run can not be called");
}

int Event::getTime() const {
	return time;
}

void Event::print() {
	std::cout << "Event. time: " << time << "\n";
}

CreateVehicleEv::CreateVehicleEv(int t, Source& f) :
	Event(t), Source(f) {}

RemoveVehicleEv::RemoveVehicleEv(int t, FadeOut& s) :
	Event(t), FadeOut(s) {}

ChangeRoadwayEv::ChangeRoadwayEv(int t, Roadway& p) :
	Event(t), Roadway(p) {}

OpenSemaphoreEv::OpenSemaphoreEv(int t, std::string m, semaphore& s, int f) :
	Event(t), msg(m), Semaphore(s), Frequency(f) {}

std::vector<std::shared_ptr<Event>> CreateVehicleEv::run() {
	bool worked = true;

	try {
		source.criaVehicle();
	} catch (std::runtime_error& err) {
		worked = false;
	}

	std::vector<std::shared_ptr<Event>> newEvents;

	if (worked) {
		int timeProx = source.timeProximoEvent(gettime());

		newEvents.push_back(std::make_shared<EventCriarVehicle>(timeProx, source));

		newEvents.push_back(std::make_shared<EventChegouNosemaphore>(timeProx, source));
	} else {
		newEvents.push_back(std::make_shared<EventCriarVehicle>(gettime()+5, source));
	}

	return newEvents;
}

std::vector<std::shared_ptr<Event>> RemoveVehicleEv::run() {
	sumidouro.retira();

	std::vector<std::shared_ptr<Event>> newEvents;

	return newEvents;
}

std::vector<std::shared_ptr<Event>> ChangeRoadwayEv::run() {
	std::vector<std::shared_ptr<Event>> newEvents;

	Roadway* saida;

	try {
		saida = &Roadway.moveVehicle();
	} catch (semaphoreNaoEstaNadirection& err) {
		newEvents.push_back(std::make_shared<EventChegouNosemaphore>(gettime()+5, Roadway));
		return newEvents;
	}

	if (Sumidouro* s = dynamic_cast<Sumidouro*>(saida)) {
		newEvents.push_back(std::make_shared<EventRemoverVehicle>(gettime()+s->timeParaPercorrer(), *s));
	} else {
		newEvents.push_back(std::make_shared<EventChegouNosemaphore>(gettime()+saida->timeParaPercorrer(), *saida));
	}

	return newEvents;

}

std::vector<std::shared_ptr<Event>> OpenSemaphoreEv::run() {
	std::cout << msg << "\n";

	semaphore.nextState();

	std::vector<std::shared_ptr<Event>> newEvents;

	newEvents.push_back(std::make_shared<EventAbrirsemaphore>(gettime()+frequencia, msg, semaphore, frequencia));

	return newEvents;
}

void CreateVehicleEv::print() {
	std::cout << "CreateVehicle\n";
}

void RemoveVehicleEv::print() {
	std::cout << "RemoveVehicle\n";
}

void ChangeRoadwayEv::print() {
	std::cout << "ChangeRoadway\n";
}

void OpenSemaphoreEv::print() {
	std::cout << "OpenSemaphore: " << msg << "\n";
}