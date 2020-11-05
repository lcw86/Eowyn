//
//  ATDeviceMirage16.h
//  ATDeviceElements
//
//  Created by sai on 8/2/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceDust.h>

@interface ATDeviceMirage16 : ATDeviceDust

typedef NS_ENUM(uint32_t, ATDeviceMirage16USBPortMask) {
    
    ATDeviceMirage16USBPortAllOff    = 0x0000,
    ATDeviceMirage16USBPort_1_On     = 0x0001,
    ATDeviceMirage16USBPort_2_On     = 0x0002,
    ATDeviceMirage16USBPort_3_On     = 0x0004,
    ATDeviceMirage16USBPort_4_On     = 0x0008,
    ATDeviceMirage16USBPort_5_On     = 0x0010,
    ATDeviceMirage16USBPort_6_On     = 0x0020,
    ATDeviceMirage16USBPort_7_On     = 0x0040,
    ATDeviceMirage16USBPort_8_On     = 0x0080,
    ATDeviceMirage16USBPort_9_On     = 0x0100,
    ATDeviceMirage16USBPort_10_On    = 0x0200,
    ATDeviceMirage16USBPort_11_On    = 0x0400,
    ATDeviceMirage16USBPort_12_On    = 0x0800,
    ATDeviceMirage16USBPort_13_On    = 0x1000,
    ATDeviceMirage16USBPort_14_On    = 0x2000,
    ATDeviceMirage16USBPort_15_On    = 0x4000,
    ATDeviceMirage16USBPort_16_On    = 0x8000,
    ATDeviceMirage16USBPortAllOn     = 0xFFFF,
};


- (BOOL) mirageSetUSBOutputs: (uint32_t) usbPortsMask andError: (NSError**) aError;
- (BOOL) mirageGetUSBOutputs: (uint32_t*) usbPortsMask andError: (NSError**) aError;

@end
