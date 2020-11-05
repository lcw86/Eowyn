//
//  ATDeviceErrors.h
//  ATDeviceElements
//
//  Created by Sai  on 9/22/16.
//  Copyright © 2016 htwe. All rights reserved.
//

#ifndef ATDeviceErrors_h
#define ATDeviceErrors_h



typedef NS_ENUM(int, ATDErrorCode) {
    
    ATDHDMIDeviceError               = -12,
    ATDeviceRegisterReadError       = -11,
    ATDeviceVersionFailed           = -10,
    ATDeviceNotSupportFunction      = -9,
    ATDeviceUSBCPowerContractError  = -8,
    ATDeviceTimedOut                = -7,
    ATDeviceUSBMUxNotSetRight       = -6,
    ATDDeviceNotOpened              = -5,
    ATDTBTDeviceError               = -4,
    ATDUSBDeviceError               = -3,
    ATDUserError                    = -2,
    ATDSystemError                  = -1,
    ATDeviceSuccess                 =  0,
   
};

typedef NS_ENUM(int32_t,ATDeviceFixtureErrors){
    
    ATDeviceFixtureIntefaceBadState = -256,
    ATDeviceFixtureInterfaceFailedTX = -257,
    ATDeviceFixtureInterfaceRxFIFOFull = -258,
    ATDeviceFixtureInterfaceRxFIFOEmpty = -259,
    ATDeviceFixtureInterfaceNotOperational = -260,
    ATDeviceFixtureInterfaceSDOAborted = -261,
    ATDeviceFixtureInterfaceUnExpectedResponse = -262,
    ATDeviceFixtureInterfaceTimeout = -263
};

#endif /* ATDeviceErrors_h */
