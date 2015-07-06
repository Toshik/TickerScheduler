# TickerScheduler
Simple scheduler for ESP8266 Arduino based on Ticker

###Initialization###

```TickerScheduler(uint size); ```

| Param | Description | 
| --- | --- |
|  size  |  Amount of task Tickers to initialize  |

**Example**: 

```TickerScheduler ts(5)```


###Add task###

```boolean add(uint i, uint32_t period, void(*f)(void), boolean shouldFireNow = false)```

| Param | Description | 
| --- | --- |
|  i  |  Ticker ID  |
| period  | period in ms  |
| *f | task callback pointer |
| shouldFireNow|  true if you want to execute task right after adding |

**Example**:

```ts.add(0, 3000, &sendData)```

###Execute scheduler in ```loop()```###

``` ts.update() ```

###Remove task###

```boolean del(uint i)```

| Param | Description | 
| --- | --- |
|  i  |  Ticker ID  |
