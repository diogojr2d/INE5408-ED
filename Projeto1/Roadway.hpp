#ifndef Roadway_HPP
#define Roadway_HPP

#include "FilaEnc.hpp"  // arrumar
#include "Vehicle.hpp"
#include "Semaphore.hpp"

/**
 * @brief Class that represents a roadway
 */
class Roadway {
protected:
	semaphore& semaphore;  // Referência para o semáforo no qual essa Roadway termina
	direction direction;  // Direção de rolamento
	FilaEnc<Vehicle> fila;  // Queue of Vehicles           ARRUMAR
	int size = 0, velocity = 0; // Size and velocity
	int entraram = 0, sairam = 0;  // Vehicles que entraram e sairam na instancia atual
	static int totalEntraram, totalSairam;  // Vehicles que entraram e sairam em
	                                        // todas as instâncias de Roadway

public:
	Roadway(semaphore& s, direction d, int size, int vel);  // Construtor da Roadway
	void add(Vehicle c);  // Add a vehicle at the start
	Vehicle remove();  // Removes a vehicle from the end
	bool empty();  // Verifies if the roadway is empty
	virtual Roadway& moveVehicle(); // Moves a vehicle to the next roadway
	int time() const;  // Time to travel the actual roadway
	int entered() const;  // Number of vehicles that entered the system
	int left() const;  // Number of vehicles that left the system
	int areIn() const;  // Number of vehicles that are inside the system
	static int totalIn();  // Total number of vehicles that entered the system
	static int totalOut();  // Total number of vehicles that left the system
};

/**
 * @brief  Classe que representa uma Fonte, Roadway que pode criar Vehicles
 */
class Source : public Roadway {
private:
	int frequenciaFixa = 0, frequenciaVariavel = 0;
	Roadway &saidaDir, &saidaReto, &saidaEsq;

public:
	Source(semaphore& s, direction d, int size, int vel, int fFixa, int fVar,
		Roadway& sDir, Roadway& sReto, Roadway& sEsq);

	void createsVehicle();  // Cria um Vehicle na Roadway atual
	virtual Roadway& moveVehicle();
	int timeNextEvent(int time);
};

/**
 * @brief Central Roadway -- neither FadeOut, neither Source
 */
class CentralRoadway : public Roadway {
private:
	Roadway &saidaDir, &saidaReto, &saidaEsq;

public:
	CentralRoadway(semaphore& s, direction d, int size, int vel,
		Roadway& sDir, Roadway& sReto, Roadway& sEsq);
	virtual Roadway& moveVehicle();
};

/**
 * @brief Removes vehicles from the system.
 */
class FadeOut : public Roadway {
public:
	FadeOut(semaphore& s, direction d, int size, int vel);
};

#endif  // Roadway_HPP