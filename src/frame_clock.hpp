#ifndef CORE_FRAME_CLOCK_HPP
#define CORE_FRAME_CLOCK_HPP

#include <chrono>
#include <thread>

class FrameClock {
	using Clock = std::chrono::steady_clock;

  private:
	const Clock::duration interval;
	const Clock::time_point start;

  public:
	explicit FrameClock(const int fps)
	    : interval{Clock::duration{Clock::duration::period::den / fps}},
	      start{Clock::now()} {}

	~FrameClock() { std::this_thread::sleep_until(start + interval); }
};

#endif // CORE_FRAME_CLOCK_HPP