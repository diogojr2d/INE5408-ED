#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

class Semaphore {
private:
	Semaphore* nextSemaphore;
	bool open;

public:
	Semaphore();
	void nextState();
	bool getOpen() const;
};

#endif // SEMAPHORE_HPP