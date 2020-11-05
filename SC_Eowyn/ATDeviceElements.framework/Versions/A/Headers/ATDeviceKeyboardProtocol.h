//
//  ATDeviceKeyboardProtocol.h
//  ATDeviceElements
//
//  Created by Sai on 5/10/19.
//  Copyright © 2019 htwe. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

typedef NS_ENUM(uint8_t,ATDeviceNibblerHighOrLowSide){
    ATDeviceLowSide = 0,
    ATDeviceHighSide
};
typedef NS_ENUM(uint8_t,ATDeviceKeyBoardType){
    ATDeviceKeyBoardJIS = 0,
    ATDevicekeyBoardISO,
    ATDevicekeyBoardANSI
};

@protocol ATDeviceKeyboardCapable < NSObject >


/**
 measure the voltage from High side pin to Low side pin
 @param boardIndex          Default is 0 if no other Nibbler connected to it. Both High and Low side will use this index
 @param highSidePinIndex    The index of the pin. from 0 to 39
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @param anError when there is error, anError will be set.
 @return                    the measurement. /
 */
-(NSNumber*) measureVoltageAtBoardIndex: (NSInteger) boardIndex
                        fromHighSidePin: (NSInteger) highSidePinIndex
                           toLowSidePin: (NSInteger) lowSidePinIndex
                               andError: (out NSError**) anError;

/**
 measure the voltage from High side pin to Low side pin
 
 @param highSidePinIndex    The index of the pin. from 0 to 39
 @param highBoardIndex      Default is 0 if no other Nibbler connected to it.
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @param lowBoardIndex       Default is 0 if no other Nibbler connected to it.
 @param anError when there is error, anError will be set.
 @return                    the measurement. /
 */
-(NSNumber*) measureVoltagefromHighSidePin: (NSInteger) highSidePinIndex
                          atHighBoardIndex: (NSInteger) highBoardIndex
                              toLowSidePin: (NSInteger) lowSidePinIndex
                           atLowBoardIndex: (NSInteger) lowBoardIndex
                                  andError: (out NSError**) anError;
/**
 measure the voltage from Low side pin to Ground
 @param boardIndex          Default is 0 if no other Nibbler connected to it.
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @param anError when there is error, anError will be set.
 @return                    the measurement.
 */
-(NSNumber*) measureVoltageAtBoardIndex: (NSInteger) boardIndex
               fromLowSideToGroundAtPin: (NSInteger) lowSidePinIndex
                               andError: (out NSError**) anError;

/**
 start keyboard testing
 Only high signal is captured. Wont detect if signal drops and comes back
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) startKeyboardTestWithError: (out NSError**) anError;
/**
 start keyboard testing with bounce capture to record multiple events including in case signal goes low.
 Normally only high signal from switch is captured
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) startKeyboardTestWithBounceCaptureAndError: (out NSError**) anError;

/**
 stop current keyboard testing by setting fpga back to known mode

 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) stopKeyboardTestWithError:  (out NSError**) anError;


/**
 Program the four high side or low side pins for keybaord test

 @param side High or low side
 @param pin1 The index of pin you want as the  high  or Low side
 @param pin2 The index of pin you want as the  high  or Low side
 @param pin3 The index of pin you want as the  high  or Low side
 @param pin4 The index of pin you want as the  high  or Low side
 @param anError  when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardSide: (ATDeviceNibblerHighOrLowSide) side
                 andPin1: (NSInteger) pin1
                 andPin2: (NSInteger) pin2
                 andPin3: (NSInteger) pin3
                 andPin4: (NSInteger) pin4
                andError: (out NSError**) anError;

/**
 Update the trigger threshold for keyboard tests.

 @param thresholdMilliVolt threshold in mV
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardThresholdInMilliVolt: (uint32_t) thresholdMilliVolt
                                andError:(out NSError**) anError;

/**
 Update the trigger threshold for keyboard tests.
 
 @param thresholdMilliVolt threshold in mV
 @param save when set, it will save to eeprom.
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardThresholdInMilliVolt: (uint32_t) thresholdMilliVolt
                         andSaveToEEPROM: (BOOL) save
                                andError:(out NSError**) anError;

/**
 Update the test period for keyboard tests.

 @param periodInMilliSecond period in millisecond
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardTestPeriodInMilliSecond: (uint16_t) periodInMilliSecond
                                   andError: (out NSError**) anError;



/**
 Update the test period for keyboard tests.
 
 @param periodInMilliSecond period in millisecond
 @param save when set, it will save to eeprom.
 @param anError when there is error, anError will be set.
 @return YES = Successed and NO = Error.
 */
- (BOOL) setKeyboardTestPeriodInMilliSecond: (uint16_t) periodInMilliSecond
                            andSaveToEEPROM: (BOOL) save
                                   andError: (out NSError**) anError;

/**
 Get the keyboard type based on gpio state of passed pin
 Only valid if dut is connected which can detected by @sa readLedVoltageValueInMilliVolts function

 @param keyBoardType This value is updated by this fucntion and is based on ATDeviceKeyBoardType
 @param pin pin value to find what keyboard type is connected to it
 @param anError  when there is error, anError will be set
 @return YES = Success and NO = Error.
 */
-(BOOL) readKeyBoardType:(out ATDeviceKeyBoardType *)keyBoardType
                fromPin : (uint32_t) pin
                andError: (out NSError**) anError;
@end

