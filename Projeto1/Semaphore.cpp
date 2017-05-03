#include "Semaphore.hpp"

Semaphore::Semaphore():
	open{false},
	nextSemaphore{nullptr}
	{}

Semaphore::Semaphore(bool open_):
	open{open_},
	nextSemaphore{nullptr}
	{}

Semaphore::~Semaphore() {
	if (nextSemaphore != nullptr) {
		delete nextSemaphore;
	}
}

void Semaphore::nextState() {
	open = !open;
	nextSemaphore->open = !(nextSemaphore->open);
}

bool Semaphore::getOpen() const {
	return open;
}

void Semaphore::setNext(Semaphore* s_) {
	nextSemaphore = s_;
}