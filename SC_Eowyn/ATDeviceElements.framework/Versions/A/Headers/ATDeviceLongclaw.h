//
//  ATDeviceLongclaw.h
//  ATDeviceElements
//
//  Created by Cody Shaw  on 7/22/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#import <ATDeviceElements/ATDeviceElements.h>
#import <ATDeviceElements/ATDeviceWirelessDebug.h>


@interface ATDeviceLongclaw : ATDeviceWirelessDebug

-(BOOL)                  setGreenLED: (BOOL) ledGreen
                        andYellowLED: (BOOL) ledYellow
                           andRedLED: (BOOL) ledRed
                            andError: (out NSError**) anError;

@end
