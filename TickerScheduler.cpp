#include <Arduino.h>
#include "TickerScheduler.h"

void tickerFlagHandle(volatile bool * flag)
{
    if (!*flag)
        *flag = true;
}

TickerScheduler::TickerScheduler(uint size)
{
    this->items = new TickerSchedulerItem[size];
    this->size = size;
}

TickerScheduler::~TickerScheduler()
{
    for (uint i = 0; i < this->size; i++)
    {
        this->remove(i);
        yield();
    }

    delete[] this->items;
    this->items = NULL;
    this->size = 0;
}

void TickerScheduler::handleTicker(tscallback_t f, volatile bool * flag)
{
    if (*flag)
    {
        yield();
        *flag = false;
        yield();
        f();
        yield();
    }
}

boolean TickerScheduler::add(uint i, uint32_t period, tscallback_t f, boolean shouldFireNow)
{
    if (i >= this->size)
        return false;

    if (this->items[i].is_used)
        return false;

    this->items[i].cb = f;
    this->items[i].flag = shouldFireNow;
    this->items[i].t.attach_ms(period, tickerFlagHandle, &this->items[i].flag);
    this->items[i].is_used = true;

    return true;
}

boolean TickerScheduler::remove(uint i)
{
    if (i >= this->size)
        return false;

    if (!this->items[i].is_used)
        return false;

    this->items[i].is_used = false;
    this->items[i].t.detach();
    this->items[i].flag = false;
    this->items[i].cb = NULL;

    return true;
}

void TickerScheduler::update()
{
    for (uint i = 0; i < this->size; i++)
    {
        if (this->items[i].is_used)
            handleTicker(this->items[i].cb, &this->items[i].flag);
        
        yield();
    }
}
