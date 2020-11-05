//
//  ATDeviceIzzy.h
//  ATDeviceElements
//
//  Created by Sai on 5/10/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceNibbler.h>
#import <ATDeviceElements/ATDeviceADC.h>

NS_ASSUME_NONNULL_BEGIN

#define kATDIzzyProductID 0x1636
#define kATDIzzyVendorID 0x5AC
#define kATDIzzyEndPoint 0x83
@interface ATDeviceIzzy : ATDeviceNibbler <ATDeviceKeyboardCapable>


/**
 Set the target current on izzy's bias sinks.
 
 @param currentInMilliAmp current in mA
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setBiasCurrentInMilliAmp: (float) currentInMilliAmp
                         andError: (NSError**) anError;
/**
 Set the target current on izzy's bias sinks.
 
 @param currentInMilliAmp current in mA
 @param save set to yes if you want to save in eeprom
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setBiasCurrentInMilliAmp: (float) currentInMilliAmp
                  andSaveToEEPROM: (BOOL) save
                         andError: (out NSError**) anError;
/**
 Set the target current on izzy's LED current source.
 
 @param currentInMilliAmp current in mA
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setLEDCurrentInMilliAmp: (uint32_t) currentInMilliAmp
                        andError:(NSError**) anError;


/**
 Program the four low side pins for tentomon to start oscilloscope capture
 
 @param pin1 The index of pin you want as the  high  or Low side
 @param pin2 The index of pin you want as the  high  or Low side
 @param pin3 The index of pin you want as the  high  or Low side
 @param pin4 The index of pin you want as the  high  or Low side
 @param anError  when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) startTentoMonOnPin1:(NSInteger) pin1
                     andPin2: (NSInteger) pin2
                     andPin3: (NSInteger) pin3
                     andPin4: (NSInteger) pin4
                    andError: (NSError**) anError;

/**
 Write dut side izzy pin gpio state

 @param gpioState gpioState filled by function based on @sa ATDGpioState
 @param pin 0 - 3 of dut facing izzy pin
 @param anError anError  when there is error, anError will be set.
 @return YES = Successed and NO = Error
 */
-(BOOL) writeGPIOState:(ATDGpioState)gpioState forDutFacingPin: (uint8_t) pin
             withError:(out NSError**) anError;

/**
 Read dut side izzy pin gpio state

 @param gpioState filled by function based on ATDGpioState
 @param pin 0 - 3 of dut facing izzy pin
 @param anError anError  when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) gpioState:(out ATDGpioState *)gpioState forDutFacingPin: (uint32_t) pin withError:(out NSError**) anError;

/**
 Read led voltage after setting bias current on passed pin

 @param readVoltage voltage value in millivolts filled by function
 @param pin Hi side Izzy pin to which led connected
 @param current current value in milliAmp to be set
 @param anError anError  when there is error, anError will be set
 @return YES = Successed and NO = Error.
 */
- (BOOL) readLedVoltageValueInMilliVolts:(out uint16_t *) readVoltage
                            ForHiSidePin:(uint32_t)pin
              BySettingCurrentInMilliAmp:(uint32_t)current
                               withError:(out NSError**) anError;

/**
 set hi side pins in mask to be persistent high

 @param mask izzy pin mask example: 0x0200 for L09, 0x0003 for L00, L01
 @param anError anError anError  when there is error, anError will be set
 @return YES = Successed and NO = Error.
 */
-(BOOL) makeHiSidePinsPersistentHighForMask:(uint32_t) mask
                                  withError:(out NSError **) anError;

/**
 This value controls the number of consecutive test cycles that the voltage at the sense line must be above the threshold value for Izzy's output signal to be driven high. Users may disable debounce operation by setting the debounce variable to 1, since this will mean Izzy's output signal will be driven on the test cycle with the first detected make

 @param cycles Number of consecutive cycles voltage must be above threshold value for Izzy output signal to be driven high
 @param save save to eeprom if set
 @param anError anError  when there is error, anError will be set
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardDebounceCycles: (uint32_t) cycles
                   andSaveToEEPROM: (BOOL) save
                          andError: (out NSError**) anError;

/**
 Set sync pulse for passed vout and duration after passed in delay

 @param voltage voltage voltage in millivolts
 @param duration duration duration in milliseconds
 @param delay delay before sync pulse is sent
 @param anError when there is error, anError will be set
 @return YES = Success and NO = Error
 */
-(BOOL) setSyncPulseForVoltageInMilliVolts:(uint16_t) voltage
                 andDurationInMilliSeconds:(uint16_t)duration
                    andDelayInMilliSeconds:(uint32_t)delay
                                  andError: (out NSError**) anError;

/**
 Capture adc packets for specified time for passed location id

 @param time time interval to capture adc data
 @param locationID location id of izzy can be got from discover class apis
 @param delay additional delay to wait to capture packets in addition to theoretically calculated time
 @param error when there is error, error will be set
 @return YES = Success and NO = Error
 */
- (NSArray<ATDeviceSample*>*) gatherDataForTime: (NSTimeInterval)time
                                  andLocationID:(uint32_t) locationID
                                   andDelayInMilliseconds:(NSTimeInterval)delay
                                      withError: (out NSError**)error;

/**
 Read LS pin values

 @param lsValues fills the ls pin values
 @param anError hen there is error, anError will be set
 @return YES = Success and NO = Error
 */
-(BOOL) retrieveLSPinValues:(uint16_t *) lsValues withError:(out NSError**) anError;

/**
 Dump the currents read through the current sources that bias the various test lines

 @param currents array filled with current for each pin
 @param anError error when there is error, error will be set
 @return YES = Success and NO = Error
 */
-(BOOL) dumpIzzyCurrentsToDataBufferInMilliAmp:(NSMutableArray *) currents
                                     withError:(out NSError**) anError;
@end

NS_ASSUME_NONNULL_END
