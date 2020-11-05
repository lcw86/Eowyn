//
//  ATDeviceNibbler.h
//  ATDeviceElements
//
//  Created by Sai  on 8/17/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>
#import <ATDeviceElements/ATDeviceKeyboardProtocol.h>
#import <ATDeviceElements/ATDeviceParameters.h>



typedef NS_ENUM(uint8_t,ATDeviceNibblerMode){
    ATDNibblerKeyboardMode = 0,
    ATDNibblerWireMode
};


@interface ATDeviceNibbler : ATDeviceElement <ATDeviceKeyboardCapable>

/**
 Configure either High or Low Side pins to Low or High. You can configure multiple pins at once.
 
 @param side        ATDeviceLowSide or ATDeviceHighSide
 @param pinsMask    represent the 40 pins (0 to 39). Each bit represent each pin. Bit 0 = Pin 0, Bit 1 = Pin 1, so son
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @param anError     description of the error
 @return                YES when there is no  error.
 */
-(BOOL)           configure: (ATDeviceNibblerHighOrLowSide) side
                  onOffMask: (uint64_t) pinsMask
               atBoardIndex: (NSInteger) boardIndex
                   andError: (NSError**) anError;
/**
 Configure either High or Low Side single pin to Low or High. You can configure only one pin
 
 @param side        ATDeviceLowSide or ATDeviceHighSide
 @param pinIndex    The index of the pin. from 0 to 39
 @param isOn     YES = ON and  NO = OFF
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @param anError     description of the error
 @return            YES when there is no error.
 */
-(BOOL)           configure: (ATDeviceNibblerHighOrLowSide) side
                     forPin: (NSInteger) pinIndex
                    setItOn: (BOOL) isOn
               atBoardIndex: (NSInteger) boardIndex
                   andError: (NSError**) anError;

/**
 Configure both High and Low Side single pin to Low or High. You can configure both and all pins at once
 
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @param highSidePinsMask   represent the High Side 40 pins (0 to 39). Each bit represent each pin. Bit 0 = Pin 0, Bit 1 = Pin 1, so son
 @param lowSidePinsMask    represent the Low Side 40 pins (0 to 39). Each bit represent each pin. Bit 0 = Pin 0, Bit 1 = Pin 1, so son

 @param anError     description of the error
 @return            YES when there is no error.
 */
-(BOOL)     configureBoardIndex: (NSInteger) boardIndex
              highSideOnOffMask: (uint64_t) highSidePinsMask
               lowSideOnOffMask: (uint64_t) lowSidePinsMask
                       andError: (NSError**) anError;

/**
    get either High or Low Side pin's state (ON or OFF). You can configure multiple pins at once.
 
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @param side        ATDeviceLowSide or ATDeviceHighSide
 @param pinIndex    The index of the pin. from 0 to 39
 @param anError    description of the error
 @return            YES = On and NO = Off only valid if anError is not nil..
 */

-(BOOL)      isPinOnAtBoardIndex: (NSInteger) boardIndex
                         forSide: (ATDeviceNibblerHighOrLowSide) side
                          forPin: (NSInteger) pinIndex
                        andError: (NSError**) anError;


/**
    read bit mask of the pin states.
 
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @param side        ATDeviceLowSide or ATDeviceHighSide
 @param anError    description of the error
 @return            pin states
 */
- (uint64_t)   readPinsAtBoardIndex: (NSInteger) boardIndex
                            forSide: (ATDeviceNibblerHighOrLowSide) side
                           andError: (NSError**) anError;

/**
 set all High and Low Side pins to OFF
 
 @param boardIndex  Default is 0 if no other Nibbler connected to it.
 @return            YES when there is no error.
 */
-(BOOL) resetAllPinsAtBoardIndex: (NSInteger) boardIndex
                        andError: (NSError**) anError;

/**
 get the number of nibbler connected to the target nibller through CAN BUS all
 @param anError    description of the error
 @return           number of nibblers connected. Only valid if anError is not nil.
 */
-(NSInteger) numberOfBoardConnectedWithError: (NSError**) anError;

/**
 measure the voltage from High side pin to Low side pin
 @param boardIndex          Default is 0 if no other Nibbler connected to it. Both High and Low side will use this index
 @param highSidePinIndex    The index of the pin. from 0 to 39
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @return                    the measurement. /
 */
-(NSNumber*) measureVoltageAtBoardIndex: (NSInteger) boardIndex
                        fromHighSidePin: (NSInteger) highSidePinIndex
                           toLowSidePin: (NSInteger) lowSidePinIndex
                               andError: (NSError**) anError;

/**
 measure the voltage from High side pin to Low side pin

 @param highSidePinIndex    The index of the pin. from 0 to 39
 @param highBoardIndex      Default is 0 if no other Nibbler connected to it.
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @param lowBoardIndex       Default is 0 if no other Nibbler connected to it.
 @return                    the measurement. /
 */
-(NSNumber*) measureVoltagefromHighSidePin: (NSInteger) highSidePinIndex
                          atHighBoardIndex: (NSInteger) highBoardIndex
                              toLowSidePin: (NSInteger) lowSidePinIndex
                           atLowBoardIndex: (NSInteger) lowBoardIndex
                                  andError: (NSError**) anError;
/**
 measure the voltage from Low side pin to Ground
 @param boardIndex          Default is 0 if no other Nibbler connected to it.
 @param lowSidePinIndex     The index of the pin. from 0 to 39
 @return                    the measurement.
 */
-(NSNumber*) measureVoltageAtBoardIndex: (NSInteger) boardIndex
               fromLowSideToGroundAtPin: (NSInteger) lowSidePinIndex
                               andError: (NSError**) anError;

/**
 boardIndexWithError get the board Index (CAN bus Id)

 @param anError description of the error
 @return the board Index
 */
- (NSNumber*) boardIndexWithError: (NSError**) anError;

/**
 assignBoardIndexWithError set the board Index
 
 @param indexToSet  board Index to Set
 @param anError     description of the error
 @return            YES if successed.
 */
- (BOOL) assignBoardIndexTo: (NSInteger) indexToSet andError: (NSError**) anError;


/**
 enable or disasble High Current

 @param boardIndex Default is 0 if no other Nibbler connected to it.
 @param enableHC YES = enable , NO = disasble High Current
 @param anError description of the error
 @return YES if successed.
 */
- (BOOL) setupHighCurrentAtBoardIndex: (NSInteger) boardIndex
                               enable: (BOOL) enableHC
                              andError: (NSError**) anError;


/**
 set Nibbler Mode

 @param mode ATDeviceNibblerMode
 @param anError  description of the error
 @return YES if successed.
 */
- (BOOL) setMode: (ATDeviceNibblerMode) mode
        andError: (NSError**) anError;

- (BOOL) setKeyboardSide: (ATDeviceNibblerHighOrLowSide) side
                 andPin1: (NSInteger) pin1
                 andPin2: (NSInteger) pin2
                 andPin3: (NSInteger) pin3
                 andPin4: (NSInteger) pin4
                andError: (NSError**) anError;

- (BOOL) startKeyboardTestWithError: (NSError**) anError;

- (BOOL) stopKeyboardTestWithError:  (NSError**) anError;

/**
set Keyboard DAC Threshold
 
 @param threshold a value between 0 to 255. Voltage = 3.3v * threshold / 255.
 @param anError  description of the error
 @return YES if successed.
 */
- (BOOL) setKeyboardThreshold: (uint8_t) threshold  andError:(NSError**) anError;
/**
 set Keyboard TestPeriod In MilliSecond
 Period: 16-bit value to control test polling frequency. Based on 25MHz clock, 4 channels, 2 periods per channel.
 periodInMilliSecond = Polling rate = 0.04us * period * 2 * 4.
 
 @param periodInMilliSecond  Default is 64 milli seconds.  periodInMilliSecond not be less than 50ms.
 @param anError  description of the error
 @return YES if successed.
 */
- (BOOL) setKeyboardTestPeriodInMilliSecond: (uint16_t) periodInMilliSecond  andError:(NSError**) anError;
    


@end
