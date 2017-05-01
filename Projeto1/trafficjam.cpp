// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include <ctime>
#include "doubly_linked_list.hpp"
#include "Event.hpp"

// Global variables
int totalTime, semaphFrequency;

DoublyLinkedList<Event*> events;

int main(int argc, char const **argv) {
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

	// Initial events
	events.insert_sorted(new CreateCarEv{} );

	events.insert_sorted(new ChangeSemaphoreEv{} );

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