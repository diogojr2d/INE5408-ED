#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

class Semaphore {
private:
	Semaphore* nextSemaphore;
	bool open;

public:
	Semaphore();
	explicit Semaphore(bool open_);
	void nextState();
	bool getOpen() const;
	void setNext(Semaphore* s_);
};

#endif // SEMAPHORE_HPP