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
|  i  |  Task ID  |
| period  | Task execution eriod in ms  |
| *f | Task callback pointer |
| shouldFireNow|  ```true``` if you want to execute task right after first scheduler update |

**Returns**:

```true``` - task added sucessfully

```false``` - task was not added 

**Example**:

```ts.add(0, 3000, &sendData)```

###Execute scheduler in ```loop()```###

``` ts.update() ```

###Remove task###

```boolean del(uint i)```

**Returns**:

```true``` - task removed sucessfully

```false``` - task was not removed

| Param | Description | 
| --- | --- |
|  i  |  Task ID  |

###TODO###
* Task callback parameters support
* ...
