#include <Ticker.h>
#include <stdint.h>

void tickerFlagHandle(volatile bool * flag);

struct TickerSchedulerItem
{
    Ticker t;
    volatile bool flag = false;
    void(*cb)(void);
    volatile bool is_used = false;
};

class TickerScheduler
{
private:
    uint size;
    TickerSchedulerItem *items = NULL;

    void handleTicker(void(*f)(void), volatile bool * flag);

public:
    TickerScheduler(uint size);
    ~TickerScheduler();
    
    boolean add(uint i, uint32_t period, void(*f)(void), boolean shouldFireNow = false);

    boolean del(uint i);

    void update();
};
