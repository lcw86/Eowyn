//
//  ATDCTDRegisters.h
//  ATDeviceElements
//
//  Created by Sai  on 9/7/16.
//  Copyright © 2016 htwe. All rights reserved.
//

#ifndef ATDCTDRegisters_h
#define ATDCTDRegisters_h



typedef NS_ENUM(uint32_t, ATDCTDIRegsitersMap) {
    //CTDI
    ATDCTDIRegVendorID                  = 0x00,
    ATDCTDIRegDeviceID                  = 0x01,
    ATDCTDIRegProtoVer                  = 0x02,
    ATDCTDIRegCTDISpecVersion           = 0x02,
    ATDCTDIRegMode                      = 0x03,
    ATDCTDIRegType                      = 0x04,
    ATDCTDIRegUUID                      = 0x05,
    ATDCTDIRegTypeSpecVersion           = 0x06,
    ATDCTDIDataReadActualLengthReg      = 0x0A,
    ATDCTDIRegVersion                   = 0x0F,
    ATDCTDIRegCommand                   = 0x10,
    ATDCTDIRegCommandArguments          = 0x11,
    ATDCTDIRegDataBuffer1               = 0x12,
    ATDCTDIRegDataBuffer2               = 0x13,
    ATDCTDIRegDataBuffer3               = 0x14,
    ATDCTDIRegDataBuffer4               = 0x15,
    ATDCTDIRegIDPageLock                = 0x16,
    ATDCTDIRegVendorSerialNum           = 0x17,
    ATDCTDIRegBuildDate                 = 0x18,
    ATDCTDIRegDeviceUpTime              = 0x19,
    ATDCTDIRegLifeTimeUpTime            = 0x1A,
    ATDCTDIRegBoardTemperature          = 0x1B,
    ATDCTDIRegModeStatus                = 0x1C,
    ATDCTDIRegFCTStatus                 = 0x1D,
    ATDCTDIRegMACAddress                = 0x1E,
    ATDCTDIRegIPAddress                 = 0x1F,
    ATDCTDIRegSubnetMask                = 0x20,
    ATDCTDIRegIPGateway                 = 0x21,
    ATDCTDIRegHardwareVersion           = 0x22,
    ATDCTDIRegAppleSerialNum            = 0x23,
    ATDCTDIRegUserPageSize              = 0x24,
    
    //USB-C TDI
    ATDCTDIRegGalliumPresence           = 0x40,
    ATDCTDIRegPortStatus                = 0x41,
    ATDCTDIRegVBUSLowVoltageSetting     = 0x42,
    ATDCTDIRegVBUSHighVoltageSetting    = 0x43,
    ATDCTDIRegVCONNVoltageSetting       = 0x44,
    ATDCTDIRegVBUSLoadSetting           = 0x45,
    ATDCTDIRegVCONNLoadSetting          = 0x46,
    ATDCTDIRegNegotiatedContract        = 0x47,
    ATDCTDIRegCCLineConfig              = 0x48,
    ATDCTDIRegExtraP1SourceCapability   = 0x50,
    ATDCTDIRegExtraP1SinkCapability     = 0x51,
    ATDCTDIRegExtraP2SourceCapability   = 0x52,
    ATDCTDIRegExtraP2SinkCapability     = 0x53,
    
    //Titanium Specific
    ATDCTDIRegTBTMModeSetting           = 0x6C,
    ATDCTDIRegTBTCModeSetting           = 0x6D
   
};


typedef NS_ENUM(uint32_t, ATDCTDIRadonRegsitersMap) {

    ATDCTDIVideoModeState = 0x6E,
    
};

#define kATDCTDIRegDefaultSize 4

#endif /* ATDCTDRegisters_h */
