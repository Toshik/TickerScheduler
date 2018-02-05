#ifndef TICKERSCHEDULER_H
#define TICKERSCHEDULER_H

#include <arduino.h>
#include <stdint.h>


#ifdef ARDUINO_ARCH_AVR
class Ticker
{
	typedef void(*ticker_callback_t)(bool*);

private:
	bool is_attached = false;
	uint32_t period = 0;
	uint32_t last_tick = 0;
	ticker_callback_t callback;
	bool *callback_argument;
public:
	void Tick()
	{
		if (is_attached && millis() - last_tick >= period)
		{
			callback(callback_argument);
			last_tick = millis();
		}
	}

	void detach()
	{
		this->is_attached = false;
	}

	template<typename TArg> void attach_ms(uint32_t milliseconds, void(*callback)(TArg), TArg arg)
	{
		this->period = milliseconds;
		this->callback = callback;
		this->callback_argument = arg;
		this->is_attached = true;
	}
};
#endif

#ifdef ARDUINO_ARCH_ESP8266
#include <Ticker.h>
#include <functional>
#endif

void tickerFlagHandle(volatile bool * flag);

#ifdef _GLIBCXX_FUNCTIONAL
typedef std::function<void(void*)> tscallback_t;
#else
typedef void(*tscallback_t)(void*);
#endif

struct TickerSchedulerItem
{
    Ticker t;
    volatile bool flag = false;
    tscallback_t cb;
	void * cb_arg;
    uint32_t period;
    volatile bool is_used = false;
    volatile bool repeat = true;
};

class TickerScheduler
{
private:
	uint8_t size;
    TickerSchedulerItem *items = NULL;

    void handleTicker(tscallback_t, void *, volatile bool * flag);
    void handleTicker(TickerSchedulerItem * item);
	static void handleTickerFlag(volatile bool * flag);

public:
    TickerScheduler(uint8_t size);
    ~TickerScheduler();
    
    bool add(uint8_t i, uint32_t period, tscallback_t, void *, boolean repeat = true);
    bool remove(uint8_t i);
    bool enable(uint8_t i);
    bool disable(uint8_t i);
    void enableAll();
    void disableAll();
    void update();
};

#endif
