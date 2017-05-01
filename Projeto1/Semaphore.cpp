#include "Semaphore.hpp"

Semaphore::Semaphore():
	open{false},
	nextSemaphore{nullptr}
	{}

explicit Semaphore::Semaphore(bool open_):
	open{open_},
	nextSemaphore{nullptr}
	{}

void Semaphore::nextState() {
	open = !open;
	nextSemaphore.nextState();
}

bool Semaphore::getOpen() const {
	return open;
}

void Semaphore::setNext(Semaphore* s_) {
	nextSemaphore = s_;
}