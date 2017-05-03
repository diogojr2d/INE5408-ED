#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

class Semaphore {
private:
	Semaphore* nextSemaphore;
	bool open;

public:
	Semaphore();
	Semaphore(bool open_);
	~Semaphore();
	void nextState();
	bool getOpen() const;
	void setNext(Semaphore* s_);
};

#endif // SEMAPHORE_HPP