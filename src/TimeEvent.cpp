/**
 * @file TimeEvent.cpp
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 0.1.0
 * @date 19-February-2021
 * 
 * @copyright (c) 2021 - MIT License (see license file)
 * 
 */

#include <TimeEvent.h>

TimeEvent::TimeEvent(uint8_t size) : SlotMax (size), PrevStamp (size)  {
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
bool TimeEvent::Check(const uint16_t &every, const uint16_t &offset, function<void (void)> funct) {
    if(error) return error;                                         // Do nothing once there is a error
    ActStamp=millis();
    if (ActStamp - offset - PrevStamp[SlotIndex] >= every) {
        funct();                                                    // Execute the function
        PrevStamp[SlotIndex] = ActStamp - offset;
    }
    SlotIndex++;
    if (SlotIndex==SlotMax) {
        error+=TE_ERROR_NO_SLOTS_FREE;
        Serial.println("ERROR (TimeEvent): No slots free! -> The execution will be terminated.");
    }
    return error;
}

/**
 * @brief Returns the value ture when the time mark is reached.
 * @param every Timeframe in millis. e.g. 1000 means every seccond
 * @param offset Delays the execution by x milliseconds.
 * @return true 
 * @return false 
 */
bool TimeEvent::Check(const uint16_t &every, const uint16_t &offset=0) {
    uint8_t retval=0;
    if(error) return 0;                                             // Do nothing once there is a error
    ActStamp=millis();
    if (ActStamp - offset - PrevStamp[SlotIndex] >= every) {
        PrevStamp[SlotIndex] = ActStamp - offset;
        retval=1;
    }
    SlotIndex++;
    if (SlotIndex==SlotMax) {
        error+=TE_ERROR_NO_SLOTS_FREE;
        Serial.println("ERROR (TimeEvent): No slots free! -> The execution will be terminated.");
    }
    return retval;
}
