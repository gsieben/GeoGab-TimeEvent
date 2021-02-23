

![GeoGab Logo](./images/GeoGab.svg)

#### Gabriel A. Sieben (Physicist)

# GeoGab TimeEvent Library
This is a simple library for timing a program in a loop. It is used to call functions or program parts in a certain periodic frequency. The prerequisite is of course that the periodicity is greater than the runtime of the entire loop. 

# Inizialization

## Constructor

`TimeEvent tevent(x);` while x is the number of timer slots.

## Loop

### Timer
The timer can be used in two variants:

- With direct call of a function without parameters. 
`uint8_t error=tevent.Check([time index],[offset],[function]);` 

- Inside an if condition. 
`if(tevent.Check([time index],[offset]))` or `if(tevent.Check([time index]))`  

It receives as passing parameter the time index, in which the function should be executed periodically. 

**Example** (an output is made every second):
```cpp
if(tevent.Check(1000)) {
    static uint8_t secconds++;
    Serial.println(secconds);
}
```

An offset can be specified as another passing parameter. The code will be executed shifted by the offset. This can be used to not start all functions that are called with the same periodicity at the same time. The offset should be used generously. If the runtime of the first call exceeds the offset, both calls are executed in the same loop.

**Example 1** (both parts are called in the same loop):
```cpp
loop {
    tevent.Check(1000,0,function1); // Executed every second. Runtime 100 milli seconds

    tevent.Check(1000,10,function2); // Will be executed every second. Executed in the same loop pass as function 1.
}
```

**Example 2** (This is how it would be correct);

```cpp
loop {
    tevent.Check(1000,0,function1); // Will be executed every second. Runtime 100 milli seconds

    tevent.Check(1000,500,function2); // Executed every second. But will be executed staggered by 500 millseconds. Therefore in another loop
}
```

The sense of the offset is that longer running program parts do not delay the shorter running ones too long. Program parts that require fast timing are not unnecessarily delayed. 

### Reset
The reset must always be at the beginning or end of a loop to reset the slot index. 
`tevent.Reset();` 
Optionally, the SlotIndex can also be reset directly.
`tevent.SlotIndex=0;`

### Error
An error occurs if more TimerEvents are set than were requested when the TimeEvent object was created. The functions will not be executed. 

Example:
```cpp
`TimeEvent tevent(2);`

loop{
 tevent.Check(1000,0,function1); // Will be listed every second
 tevent.Check(5000,0,function2); // Will be executed every 5 seconds

 tevent.Check(500,0,function3); // Will not be executed. Please use "TimeEvent tevent(3);".
}
```

## Runtime
The TimeEvent.Check which calls a function calculates the runtime of the called function.
`tevent.Check([time index],[offset],[function]);` 
 The runtime is stored in public variables. They can be retrieved via `tevent.Runtime[index]`. Where the index corresponds to the slot number of the runtime. The slot number is counted from zero. Each `tevent.Check` call increments the index. 

Example:
```cpp
`TimeEvent tevent(2);`

loop{
 tevent.Check(1000,0,function1); // Will be listed every second
 tevent.Check(5000,0,function2); // Will be executed every 5 seconds

 if(tevent.Check(1000)) {
    // Code of Function3
 }

 tevent.Check(500,0,function4); // Will not be executed. Please use "TimeEvent tevent(3);".
}
```

- tevent.Runtime[0]; // Runtime of Function1 in Micros Seconds
- tevent.Runtime[1]; // Runtime of Function2 in Micros Seconds
- tevent.Runtime[2]; // Zero as this is not calculated
- tevent.Runtime[3]; // Runtime of Function4 in Micros Seconds

Please note: when calling `if(tevent.Check(1000))` the runtime is not calculated. Probably the slot index is increased for it.

## Restrictions
To save unnecessary computing time the rollover of the millis variable is not taken into consideration. The variable is 32 bit large. Therefore it overflows after 2^32 milliseconds. That is 4.294.967.296 milli seconds -> 4.294.967 seconds -> 71.583 minutes -> 1.193 hours -> 49,7 days. At the event of the overflow the timing is not correct for a short moment. If this is a problem, it is mandatory to extend the library with the rollover handling, or to use other libraries. 
