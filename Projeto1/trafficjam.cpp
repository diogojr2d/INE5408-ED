// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include <ctime>
#include "Event.hpp"
#include "Roadway.hpp"
#include "Semaphore.hpp"
#include "Vehicle.hpp"
#include "doubly_linked_list.hpp"

// Global variables
int totalTime, semaphFrequency;

DoublyLinkedList<Event*> events;

int main(int argc, char const *argv[]) {
	srand(time(0));

	// Initialize totalTime and semaphFrequency
	if (argc != 3) {
		std::string totalTime_;
		std::string semaphFrequency_;
		std::cout << "Parâmetros incorretos." << std::endl;
		std::cout << "Digite o Tempo Total de Simulação: ";
		std::cin >> totalTime_;
		std::cout << "Digite a Frequencia do Semaforo: ";
		std::cin >> semaphFrequency_;
		totalTime = atoi(totalTime_);
		semaphFrequency = atoi(semaphFrequency_);
		exit(1);
	} else {
		totalTime = atoi(argv[1]);
		semaphFrequency = atoi(argv[2]);
	}

	if (totalTime < 1 || semaphFrequency < 1) {
		std::cout << "Tempo total ou Frequencia do semáforo inválidos.\n";
		exit(1);
	}

	// Create and set Semaphores
	Semaphore* S1west = new Semaphore(true);
	Semaphore* S1south = new Semaphore();
	Semaphore* S1east = new Semaphore();
	Semaphore* S1north = new Semaphore();
	Semaphore* S2west = new Semaphore(true);
	Semaphore* S2south = new Semaphore();
	Semaphore* S2east = new Semaphore();
	Semaphore* S2north = new Semaphore();

	S1west->setNext(S1south);
	S1south->setNext(S1east);
	S1east->setNext(S1north);
	S1north->setNext(S1west);

	S2west->setNext(S2south);
	S2south->setNext(S2east);
	S2east->setNext(S2north);
	S2north->setNext(S2west);

	// Create and set Roadways
	// Exit Roadways
	ExitRoadways W1west(*S1east, 2000, 80);
	ExitRoadways N1north(*S1south, 500, 60);
	ExitRoadways S1south(*S1north, 500, 60);
	ExitRoadways E2east(*S2west, 400, 30);
	ExitRoadways N2north(*S2south, 500, 40);
	ExitRoadways S2south(*S1north, 500, 40);

	// Central Roadways
	CentralRoadway C1west(*S1east, 300, 60, N1north, W1west, S1south, 0.3, 0.7);
	CentralRoadway C1east(*S2west, 300, 60, S2south, E2east, N2north, 0.3, 0.7);

	// Source Roadways
	Source W1east(*S1west, 2000, 80, 10, 2, S1south, C1east, N1north, 0.1, 0.9);
	Source N1south(*S1north, 500, 60, 20, 5, W1west, S1south, C1east, 0.1, 0.9);
	Source S1north(*S1south, 500, 60, 30, 7, C1east, N1north, W1west, 0.1, 0.9);
	Source E2west(*S2east, 400, 30, 10, 2, N2north, C1west, S2south, 0.3, 0.7);
	Source N2south(*S2north, 500, 40, 20, 5, C1west, S2south, E2east, 0.3, 0.7);
	Source S2north(*S2south, 500, 40, 60, 15, E2east, N2north, C1west, 0.3, 0.7);

	// Initial events
	events.insert_sorted(new CreateVehicleEv() );

	events.insert_sorted(new ChangeSemaphoreEv() );

	// Main loop of events
	int currentTime = 0;

	while (currentTime < totalTime) {
		auto currentEvent = events.pop_front();
		currentTime = currentEvent->getTime();

		auto newEvents = currentEvent->run();
		unsigned int size = newEvents.size();

		for (auto i = 0u; i < size; ++i) {
			events.insert_sorted( newEvents.at(i) );
		}
	}

	std::cout << "Fim do programa.\n";

	return 0;
}