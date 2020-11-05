//
//  ATDeviceCanOpen.h
//  ATDeviceElements
//
//  Created by Sai  on 1/29/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#ifndef ATDeviceCanOpen_h
#define ATDeviceCanOpen_h

typedef NS_ENUM(uint16_t,ATDeviceCanOpenIndex){
    
    ATDeviceCanOpenName                 = 0x1008,
    ATDeviceCanOpenHardwareVersion      = 0x1009,
    ATDeviceCanOpenSoftwareVersion      = 0x100A,
    ATDeviceCanOpenControlWord          = 0x6040,
    ATDeviceCanOpenStatusWord           = 0x6041,
    ATDeviceCanOpenSetOperation         = 0x6060,
    ATDeviceCanOpenShowOperation        = 0x6061,
    ATDeviceCanOpenActualPosition       = 0x6064,
    ATDeviceCanOpenActualVelocity       = 0x606C,
    ATDeviceCanOpenSteps                = 0x607A,
    ATDeviceCanOpenHomingOffset         = 0x607C,
    ATDeviceCanOpenPositionModeVelocity = 0x6081,
    ATDeviceCanOpenAcceleration         = 0x6083,
    ATDeviceCanOpenDeceleration         = 0x6084,
    ATDeviceCanOpenHomingMethod         = 0x6098,
    ATDeviceCanOpenHomingVelocities     = 0x6099,
    ATDeviceCanOpenHomingAcceleration   = 0x609A,
    ATDeviceCanOpenVelocityModeVelocity = 0x60FF,
    ATDeviceCanOpenHomingSwitch         = 0x7001,
    ATDeviceCanOpenDriveStatus = 0x700B,
    ATDeviceCanOpenErrorStatus = 0x603F,
    ATDeviceCanOpenDriveInput = 0x7003,
    ATDeviceCanOpenDriveOutput = 0x60FE,
    ATDeviceCanOpenIdentity    = 0x1018,
};
typedef NS_ENUM(uint8_t,ATDeviceCanOpenSubIndex){
    ATDeviceCanOpenSubIndexHomingVelocity = 1,
    ATDeviceCanOpenSubIndexIndexVelocity = 2,
};
/*typedef NS_ENUM(uint8_t,ATDeviceCanOpenOperation){
    
    ATDeviceCanOpenOperationPosition = 0x01,
    ATDeviceCanOpenOperationVelocity = 0x03,
    ATDeviceCanOpenOperationHoming   = 0x06,
};*/
#endif /* ATDeviceCanOpen_h */
