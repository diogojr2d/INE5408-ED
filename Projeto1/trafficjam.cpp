// Copyright 2017
// Diogo Junior de Souza
// Leticia do Nascimento

#include <ctime>
#include "Event.hpp"
#include "Roadway.hpp"
#include "Semaphore.hpp"
#include "Vehicle.hpp"
#include "doubly_linked_list.h"

// Global variables
int totalTime, semaphFrequency;

DoublyLinkedList<Event*> events;

int main(int argc, char const *argv[]) {
	srand(time(0));

	// Initialize totalTime and semaphFrequency
	if (argc != 3) {
		std::string totalTime_;
		std::string semaphFrequency_;
		std::cout << "Digite o Tempo Total de Simulação: ";
		std::cin >> totalTime_;
		std::cout << "Digite a Frequencia do Semaforo: ";
		std::cin >> semaphFrequency_;
		totalTime = std::stoi(totalTime_);
		semaphFrequency = std::stoi(semaphFrequency_);
	} else {
		totalTime = atoi(argv[1]);
		semaphFrequency = atoi(argv[2]);
	}

	if (totalTime < 1 || semaphFrequency < 1) {
		std::cout << "Tempo total ou Frequencia do semáforo inválidos.\n";
		exit(1);
	}

	// Create and set Semaphores
	Semaphore* S1w = new Semaphore(true);
	Semaphore* S1s = new Semaphore();
	Semaphore* S1e = new Semaphore();
	Semaphore* S1n = new Semaphore();
	Semaphore* S2w = new Semaphore(true);
	Semaphore* S2s = new Semaphore();
	Semaphore* S2e = new Semaphore();
	Semaphore* S2n = new Semaphore();

	S1w->setNext(S1s);
	S1s->setNext(S1e);
	S1e->setNext(S1n);
	S1n->setNext(S1w);

	S2w->setNext(S2s);
	S2s->setNext(S2e);
	S2e->setNext(S2n);
	S2n->setNext(S2w);

	// Create and set Roadways
	// Exit Roadways
	ExitRoadway W1west(*S1e, 2000, 80);
	ExitRoadway N1north(*S1s, 500, 60);
	ExitRoadway S1south(*S1n, 500, 60);
	ExitRoadway E2east(*S2w, 400, 30);
	ExitRoadway N2north(*S2s, 500, 40);
	ExitRoadway S2south(*S1n, 500, 40);

	// Central Roadways
	CentralRoadway C1west(*S1e, 300, 60, N1north, W1west, S1south, 0.3, 0.7);
	CentralRoadway C1east(*S2w, 300, 60, S2south, E2east, N2north, 0.3, 0.7);

	// Source Roadways
	Source W1east(*S1w, 2000, 80, 10, 2, S1south, C1east, N1north, 0.1, 0.9);
	Source N1south(*S1n, 500, 60, 20, 5, W1west, S1south, C1east, 0.1, 0.9);
	Source S1north(*S1s, 500, 60, 30, 7, C1east, N1north, W1west, 0.1, 0.9);
	Source E2west(*S2e, 400, 30, 10, 2, N2north, C1west, S2south, 0.3, 0.7);
	Source N2south(*S2n, 500, 40, 20, 5, C1west, S2south, E2east, 0.3, 0.7);
	Source S2north(*S2s, 500, 40, 60, 15, E2east, N2north, C1west, 0.3, 0.7);
	// Initial events
	
	events.insert_sorted( new CreateVehicleEv(0, W1east) );
	events.insert_sorted( new CreateVehicleEv(0, N1south) );
	events.insert_sorted( new CreateVehicleEv(0, S1north) );
	events.insert_sorted( new CreateVehicleEv(0, E2west) );
	events.insert_sorted( new CreateVehicleEv(0, N2south) );
	events.insert_sorted( new CreateVehicleEv(0, S2north) );

	events.insert_sorted( new OpenSemaphoreEv(semaphFrequency, *S1w, semaphFrequency) );
	events.insert_sorted( new OpenSemaphoreEv(semaphFrequency, *S2w, semaphFrequency) );
	
	// Main loop of events
	int currentTime = 0;
	//printf("Vai entrar no loop.\n");
	while ( (currentTime <= totalTime) && !(events.empty()) ) {
		//printf("Começou evento: ");
		auto currentEvent = events.pop_front();

		currentTime = currentEvent->getTime();
		//currentEvent->print();
		//printf("currentTime: %d\n", currentTime);

		auto newEvents = currentEvent->run();
		unsigned int size = newEvents.size();
		//printf("newEvents size: %d\n", size);

		for (auto i = 0u; i < size; ++i) {
			events.insert_sorted( newEvents.at(i) );
		}
		//printf("Lista de eventos atual:\n");
		//events.printAll();		
	}
	//printf("Saiu do loop.\n");

	// Print output
	std::cout << "--------------------\n"
	<< "   RELATÓRIO FINAL\n"
	<< "Entraram: " << Roadway::totalIn()
	<< "\nSaíram: " << Roadway::totalOut()
	<< "\nPermanecem dentro: " << (Roadway::totalIn() - Roadway::totalOut())
	<< "\n--------------------\n" << std::endl;
 
	// Delete all objects
	delete S1w;
	delete S1s;
	delete S1e;
	delete S1n;
	delete S2w;
	delete S2s;
	delete S2e;
	delete S2n;

		std::cout << "Relatório:\n" <<

	"\nFontes do Semáforo 1\n" <<

	"N1sul { Entraram: "   << N1south.entered() <<
	" Sairam: " 		   << N1south.left() <<
	" Estão dentro: " 	   << N1south.areIn() << " }\n"

	"O1leste { Entraram: " << W1east.entered() <<
	" Sairam: " 		   << W1east.left() <<
	" Estão dentro: " 	   << W1east.areIn() << " }\n"

	"S1n { Entraram: " 	   << S1north.entered() <<
	" Sairam: " 		   << S1north.left() <<
	" Estão dentro: " 	   << S1north.areIn() << " }\n"


	"\nFontes do Semáforo 2\n" <<

	"N2sul { Entraram: "   << N2south.entered() <<
	" Sairam: " 		   << N2south.left() <<
	" Estão dentro: " 	   << N2south.areIn() << " }\n"

	"L1oeste { Entraram: " << E2west.entered() <<
	" Sairam: " 		   << E2west.left() <<
	" Estão dentro: " 	   << E2west.areIn() << " }\n"

	"S2norte { Entraram: " << S2north.entered() <<
	" Sairam: " 		   << S2north.left() <<
	" Estão dentro: " 	   << S2north.areIn() << " }\n"


	"\nPistas centrais\n"  <<

	"C1oeste { Entraram: " << C1west.entered() <<
	" Sairam: " 		   << C1west.left() <<
	" Estão dentro: " 	   << C1west.areIn() << " }\n"

	"C1leste { Entraram: " << C1east.entered() <<
	" Sairam: " 		   << C1east.left() <<
	" Estão dentro: " 	   << C1east.areIn() << " }\n"


	"\nSumidouros do Semáforo 1\n" <<

	"O1oeste { Entraram: " << W1west.entered() <<
	" Sairam: " 		   << W1west.left() <<
	" Estão dentro: " 	   << W1west.areIn() << " }\n"

	"N1norte { Entraram: " << N1north.entered() <<
	" Sairam: " 		   << N1north.left() <<
	" Estão dentro: " 	   << N1north.areIn() << " }\n"

	"S1s { Entraram: "     << S1south.entered() <<
	" Sairam: " 		   << S1south.left() <<
	" Estão dentro: " 	   << S1south.areIn() << " }\n"


	"\nSumidouros do Semáforo 2\n" <<

	"N2norte { Entraram: " << N2north.entered() <<
	" Sairam: " 		   << N2north.left() <<
	" Estão dentro: " 	   << N2north.areIn() << " }\n"

	"L1leste { Entraram: " << E2east.entered() <<
	" Sairam: " 		   << E2east.left() <<
	" Estão dentro: " 	   << E2east.areIn() << " }\n"

	"S2sul { Entraram: "   << S2south.entered() <<
	" Sairam: " 		   << S2south.left() <<
	" Estão dentro: " 	   << S2south.areIn() << " }\n\n"


	"Total { Entraram: " << Roadway::totalIn() <<
	" Sairam: " 		 << Roadway::totalOut() <<
	" Estão dentro: "
	<< Roadway::totalIn() - Roadway::totalOut() << " }\n"

	<< std::endl;

	std::cout << "Fim do programa.\n";

	return 0;
}
