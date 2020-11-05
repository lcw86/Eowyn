//
//  ATDPDControllerRegisters.h
//  ATDeviceElements
//
//  Created by Yuanyuan Tian on 11/24/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#ifndef ATDPDControllerRegisters_h
#define ATDPDControllerRegisters_h

typedef NS_ENUM(uint32_t, ATDPDControllerRegisterOffset) {
    ATDPDCRegVendorID                  = 0,
    ATDPDCRegDeviceID                  = 0x01,
    ATDPDCRegPowerStatus               = 0x3F    
};

#endif /* ATDPDControllerRegisters_h */
