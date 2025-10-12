#pragma once

class Timer {
	float length, time;
	bool timeout = false;
public:
	Timer(float length) :length(length), time(0) {}

	void step(float deltaTime, bool loop) {
        time += deltaTime;
        if (loop) {
            if (time > length) {
                time -= length;
                timeout = true;
            }
        }
        else {
            if (time > length) {
                time = length; 
                timeout = true;
            }
        }
	};
	bool isTimeout() const { return timeout; }
	float getTime() const { return time; }
	float getLength() const { return length; }
	void reset() { time = 0; timeout = false; }



};