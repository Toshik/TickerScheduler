#include <Ticker.h>
#include <stdint.h>
#include <functional>

void tickerFlagHandle(volatile bool * flag);

typedef std::function<void(void)> tscallback_t;

struct TickerSchedulerItem
{
    Ticker t;
    volatile bool flag = false;
    tscallback_t cb;
    volatile bool is_used = false;
};

class TickerScheduler
{
private:
    uint size;
    TickerSchedulerItem *items = NULL;

    void handleTicker(tscallback_t, volatile bool * flag);

public:
    TickerScheduler(uint size);
    ~TickerScheduler();
    
    boolean add(uint i, uint32_t period, tscallback_t, boolean shouldFireNow = false);

    boolean remove(uint i);

    void update();
};
