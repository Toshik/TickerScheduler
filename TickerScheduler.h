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
    uint32_t period;
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
    
    bool add(uint i, uint32_t period, tscallback_t, boolean shouldFireNow = false);
    bool remove(uint i);
    bool enable(uint i);
    bool disable(uint i);
    void enableAll();
    void disableAll();
    void update();
};
