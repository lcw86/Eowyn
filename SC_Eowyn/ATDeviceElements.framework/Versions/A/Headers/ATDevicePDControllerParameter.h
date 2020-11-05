//
//  ATDevicePDControllerParameter.h
//  ATDeviceElements
//
//  Created by Yuanyuan Tian on 12/3/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(uint8_t,ATDevicePDControllerPowerStatus) {
    ATDTypeCCurrentDefault = 0,
    ATDTypeCCurrent1500MilliAmp = 0x4,
    ATDTypeCCurrent3000MilliAmp = 0x8,
    ATDTypeCPDContractNegociated = 0xC
};

typedef NS_ENUM(uint8_t,ATDevicePDCBatteryChargingStatus) {
    RESERVED = 0,
    ATDStandardDownstreamPortdetected = 0x20,
    ATDChargingDownstreamPortdetected = 0x40,
    ATDDedicatedDownstreamPortdetected = 0x60
};

@interface ATDevicePortsPowerStatus: NSObject

@property (nonatomic) BOOL powerConnection;
@property (nonatomic) BOOL isSink;
@property (nonatomic) ATDevicePDControllerPowerStatus typeCCurrentDetectedinMilliAmp;
@property (nonatomic) BOOL bc12Detection;
@property (nonatomic) ATDevicePDCBatteryChargingStatus bc12Status;
@property (nonatomic) BOOL usbEPNegotiated;


-(id) initWithPowerStatusRegisterData: (NSInteger) aPowerStatusData;

@end

NS_ASSUME_NONNULL_END
