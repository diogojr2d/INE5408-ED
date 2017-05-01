#include "Roadway.hpp"
#include "Exceptions.hpp"
#include <cstdlib>
#include <sstream>

int Roadway::totalIn = 0;
int Roadway::totalOut = 0;

Roadway::Roadway(semaphore& s, Direction d, int sz, int vel):
	semaphore(s),
	direction(d),
	size(sz),
	velocity(vel) {}

void Roadway::add(Vehicle c) {
	if (c.getSize() > size) {
		std::stringstream ss;
		ss << "Roadway full: " << direction << " size: " << size
			<< " vel: " << velocity << "\n";
		throw std::runtime_error(ss.str());
	}


	size -= c.getSize();

	++in;
	++totalIn;

	fila.inclui(c);
}

Vehicle Roadway::retira() {
	auto c = fila.retira();

	size += c.getSize();

	++out;
	++totalOut;

	return c;
}

bool Roadway::empty() {
	return queue.empty();
}

Roadway& Roadway::moveVehicle() {
	throw std::logic_error("Roadway::moveVehicle not implemented");
}

int Roadway::tempoParaPercorrer() const {
	return size / velocity / 3.6;
}

int Roadway::quantosEntraram() const {
	return entraram;
}

int Roadway::quantosSairam() const {
	return sairam;
}

int Roadway::estaoDentro() const {
	return entraram-sairam;
}

int Roadway::totalQuantosEntraram() {
	return totalEntraram;
}

int Roadway::totalQuantosSairam() {
	return totalSairam;
}

RoadwayCentro::RoadwayCentro(semaphore& s, direction d, int size, int vel,
		Roadway& sDir, Roadway& sReto, Roadway& sEsq):
	Roadway(s, d, size, vel),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}


Roadway& RoadwayCentro::moveVehicle() {
	if (semaphore.directionAtual() != direction)
		throw semaphoreNaoEstaNadirection();

	direction dir	= semaphore.decidedirection(direction);

	auto c = retira();

	if (dir == directionFunc::getDireita(direction)) {
		saidaDir.adiciona(c);
		return saidaDir;

	} else if (dir == directionFunc::getReto(direction)) {
		saidaReto.adiciona(c);
		return saidaReto;

	} else if (dir == directionFunc::getEsquerda(direction)) {
		saidaEsq.adiciona(c);
		return saidaEsq;

	} else
		throw std::logic_error("error in RoadwayCentro::moveVehicle");
}

Fonte::Fonte(semaphore& s, direction d, int size, int vel, int fFixa, int fVar,
	Roadway& sDir, Roadway& sReto, Roadway& sEsq):
	Roadway(s, d, size, vel),
	frequenciaFixa(fFixa - fVar),
	frequenciaVariavel(2*fVar),
	saidaDir(sDir),
	saidaReto(sReto),
	saidaEsq(sEsq) {}

void Fonte::createVehicle() {
	Vehicle c;

	std::cout << "Vehiclegetting in the system. size: " << c.getSize() << "\n";

	add(c);
}

Roadway& Fonte::moveVehicle() {
	if (semaphore.directionAtual() != direction)
		throw semaphoreNaoEstaNadirection();

	direction dir	= semaphore.decidedirection(direction);

	auto c = retira();

	if (dir == directionFunc::getDireita(direction)) {
		saidaDir.adiciona(c);
		return saidaDir;

	} else if (dir == directionFunc::getReto(direction)) {
		saidaReto.adiciona(c);
		return saidaReto;

	} else if (dir == directionFunc::getEsquerda(direction)) {
		saidaEsq.adiciona(c);
		return saidaEsq;
	} else
		throw std::logic_error("error in Fonte::moveVehicle");
}

int Fonte::timeNextEvent(int time) {
	return time + fixedFrequency + variableFrequency * float(rand())/RAND_MAX;
}

FadeOut::FadeOut(semaphore& s, direction d, int size, int vel):
	Roadway(s, d, size, vel) {}