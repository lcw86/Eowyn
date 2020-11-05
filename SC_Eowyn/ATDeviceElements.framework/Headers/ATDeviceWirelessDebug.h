//
//  ATDeviceWirelessDebug.h
//  ATDeviceElements
//
//  Created by Cody D Shaw on 7/23/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint8_t, StarkRole_t) {
    StarkRole_Local,
    StarkRole_Remote,
};

@interface ATDeviceWirelessDebug : ATDeviceElement

-(BOOL)           starkPowerEnable: (uint8_t) enable
                          andError: (out NSError**) anError;

-(BOOL)              starkRFEnable:  (uint8_t) enable
                          andError: (out NSError**) anError;

-(BOOL)             starkI2CTxn: (uint8_t*) withData
                    writeLength: (uint8_t) writeLength
                     readLength: (uint8_t) readLength
                       andError: (out NSError**) anError;

-(BOOL)           starkSetRole: (StarkRole_t) role
                      andError: (out NSError**) anError;

-(BOOL)           starkSetRoleDirect: (StarkRole_t) role
                            andError: (out NSError**) anError;

-(BOOL)           starkSetUARTBaud: (uint32_t) baud
                          andError: (out NSError**) anError;

-(BOOL)           starkEnableUartRx: (uint8_t) rxEnable
                           andError: (out NSError**) anError;

-(BOOL)           starkUartTxBytes: (uint32_t) length
                          withData: (uint8_t*) data
                             loops: (uint8_t)  loops
                         withDelay: (uint32_t) delayInMs
                          andError: (out NSError**) anError;

-(BOOL)           starkUartTxAbort: (out NSError**) anError;

-(BOOL)           parrotEnable: (uint8_t) enable
                      andError: (out NSError**) anError;

-(BOOL)           parrotI2CTxn: (uint8_t*) withData
                   writeLength: (uint8_t) writeLength
                    readLength: (uint8_t) readLength
                      andError: (out NSError**) anError;

-(BOOL)           parrotCross: (uint8_t) cross
                     andError: (out NSError**) anError;

@end

NS_ASSUME_NONNULL_END
