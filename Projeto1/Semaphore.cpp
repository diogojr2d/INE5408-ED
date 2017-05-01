#include "Semaphore.hpp"

Semaphore::Semaphore():
	nextSemaphore{nullptr}
	{}

void Semaphore::nextState() {
	open = !open;
	nextSemaphore.nextState();
}

bool Semaphore::getOpen() const {
	return open;
}