/**
 * @file TimeEvent.h
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 1.0.3
 * @date 19-February-2021
 * 
 * @copyright (c) 2021 - MIT License (see license file)
 * 
 */
#ifndef TimeEvent_h
#define TimeEvent_h

#include <Arduino.h>            // Standard Library
#include <functional>           // To overhand a "function" to another as parameter
#include <vector>               // Vector Library 

using namespace std;

#define TIMEEVENT_VERSION "1.0.3"

enum  {
  TE_ERROR_NONE=0,                        // 0000 0000: Perfect :-)           
  TE_ERROR_NO_SLOTS_FREE=1                // 0000 0001: Reverse more slots on init    
};


class TimeEvent {
    public:
    uint8_t error;                        // Error Number
    uint8_t SlotIndex=0;                  // Index of the actual slot
    vector<uint32_t> Runtime;             // Init: 1 - Previous runtime of the slot

    TimeEvent(uint8_t size);              // Constructor with timer slots

    void Reset();
    bool Check(const uint32_t &every, const uint32_t &offset, function<void (void)> funct);
    bool Check(const uint32_t &every, const uint32_t &offset);
    
    private:
    uint8_t SlotMax;                      // Init: 2 - Maximal Slots available (must be defined while object creation)
    vector<uint32_t> PrevStamp;           // Init: 3 - Previous runtime of the slot
    uint32_t ActStamp;                    // actual loop time stamp
};


#endif
