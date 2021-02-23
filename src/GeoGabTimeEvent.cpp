/**
 * @file TimeEvent.cpp
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 1.0.4
 * @date 19-February-2021
 * 
 * @copyright (c) 2021 - MIT License (see license file)
 * 
 */

#include <GeoGabTimeEvent.h>

TimeEvent::TimeEvent(uint8_t size) : Runtime (size), SlotMax (size), PrevStamp (size)  {
}

/**
 * @brief Must be executed at the beginning or end of the loop
 * 
 */
void TimeEvent::Reset() {
    SlotIndex=0;
    error=0;
}

/**
 * @brief Executes the function when the time mark is reached.
 * @param every Timeframe in millis. e.g. 1000 means every seccond
 * @param offset Delays the execution by x milliseconds.
 * @param funct Function that is to be executed. No parameters are passed. 
 * @return Error Value; 0=No Error
 */
bool TimeEvent::Check(const uint32_t &every, const uint32_t &offset, function<void (void)> funct) {
    if (SlotIndex==SlotMax) {
        error+=TE_ERROR_NO_SLOTS_FREE;
        Serial.println("ERROR (TimeEvent): No slots free! -> The execution will be terminated.");
        return error; 
    }
    ActStamp=millis();
    if (ActStamp - offset - PrevStamp[SlotIndex] >= every) {
        funct();                                                    // Execute the function
        Runtime[SlotIndex]=millis()-ActStamp;                       // Rollover is ignored as this happens once ever 45 days
        PrevStamp[SlotIndex] = ActStamp - offset;
    }
    SlotIndex++;
    return 0;
}

/**
 * @brief Returns the value ture when the time mark is reached.
 * @param every Timeframe in millis. e.g. 1000 means every seccond
 * @param offset Delays the execution by x milliseconds.
 * @return true 
 * @return false 
 */
bool TimeEvent::Check(const uint32_t &every, const uint32_t &offset=0) {
    if(error) return 0;
    if (SlotIndex==SlotMax) {
        error+=TE_ERROR_NO_SLOTS_FREE;
        Serial.println("ERROR (TimeEvent): No slots free! -> The execution will be terminated.");
        return 0; 
    }
    uint8_t retval=0;
    ActStamp=millis();
    if (ActStamp - offset - PrevStamp[SlotIndex] >= every) {
        PrevStamp[SlotIndex] = ActStamp - offset;
        retval=1;
    }
    SlotIndex++;
    return retval;
}
