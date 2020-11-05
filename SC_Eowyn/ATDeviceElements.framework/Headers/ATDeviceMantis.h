//
//  ATDeviceMantis.h
//  ATDeviceElements
//
//  Created by Sai  on 2/16/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>
#import <ATDeviceElements/ATDeviceParameters.h>

@interface ATDeviceMantis : ATDeviceElement

/**
 legacy API for changing USB Speed. It doesn't support Eye Speed.
 To do Eye Speed to capture Eye, use toSpeed:disconnectTimeInMilliSec:andActualSpeed:andError

 @param targetSpeed ATDeviceUSBSpeed
 @param disconnectTime disconnectTime In Milli Seconds
 @param actualSpeed actual Speed after speed change
 @param aError description of the error
 @return YES if successed.
 */
- (BOOL)             configureAtSpeed: (ATDeviceUSBSpeed) targetSpeed
            disconnectTimeInMilliSec: (uint16_t) disconnectTime
                      andActualSpeed: (ATDeviceUSBSpeed*)actualSpeed
                           andError: (NSError**) aError;

/**
 New API that include Eye Speed  To put Mantis into Compliance Mode to capture Eye

 @param targetSpeed ATDeviceMantisUSBSpeed
 @param disconnectTime disconnectTime In Milli Seconds
 @param actualSpeed actual Speed after speed change
 @param aError description of the error
 @return YES if successed.
 */

- (BOOL)             toSpeed: (ATDeviceMantisUSBSpeed) targetSpeed
    disconnectTimeInMilliSec: (uint16_t) disconnectTime
              andActualSpeed: (ATDeviceMantisUSBSpeed*)actualSpeed
                    andError: (NSError**) aError;


- (BOOL) vbusShortforDurationInMilliSecond: (NSInteger) durationInMilliSec
                      andMeasuredMilliVolt: (NSUInteger*) milliVolt
                       andMeasuredMilliAmp: (NSUInteger*) milliAmp
                                 andError: (NSError**) aError;

-(BOOL) measureVBusMilliVolt:(NSUInteger*) milliVolt
          andMeasureMilliAmp: (NSUInteger*) milliAmp
                    andError: (NSError **)  aError;


- (BOOL) vbusLoadforDurationInMilliSecond: (NSInteger) durationInMilliSec
                        andTargetMilliAmp: (NSUInteger) milliAmp
                                andError: (NSError**) aError;

/**
 Reads back load value and actively works to align the measured value to what the user input as the target

 @param milliAmp load in milliAmp
 @param enableLoadAccuracyAlgorithm whether to enable a zeroing algorithm to run that will improve load accuracy
 @param loadWarning gives a warning if load is mantis returned a warning
 @param aError error if vbus load fails
 @return Yes if succesful, no if set load fails
 */
- (BOOL) vbusLoadForTargetMilliAmp:(NSUInteger) milliAmp
    andEnableLoadAccuracyAlgorithm:(BOOL) enableLoadAccuracyAlgorithm
                    andLoadWarning:(ATDeviceMantisLoadWarning *) loadWarning
                          andError: (out NSError**) aError;

- (BOOL) vbusLoadForTargetMilliAmp:(NSUInteger) milliAmp
                          andError: (NSError**) aError;

- (BOOL) stopVbusLoadWithError: (NSError**) aError;

- (BOOL) measureEyeHeight: (NSUInteger*) eyeHeight
              andEyeWidth: (NSUInteger*) eyeWidth
           andRisingSlope: (NSUInteger*) risingSlope
          andFallingSlope: (NSUInteger*) fallingSlope
                 andError: (NSError**) aError;

@end
