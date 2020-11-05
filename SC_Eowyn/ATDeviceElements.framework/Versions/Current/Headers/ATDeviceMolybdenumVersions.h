//
//  ATDeviceMolybdenumVersions.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 12/21/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceVersions.h>

#define kATDMolybdenumAndCopperInfoSize 10
#define kATDMolybdenumInfoSize 5


@interface ATDeviceMolybdenumVersions : ATDeviceVersions
@property (nonatomic) uint32_t stmFwVersion;
@property (nonatomic) uint32_t hwVersion;
@property (nonatomic) uint32_t copperFwVersion;
@property (nonatomic) uint32_t copperhwVersion;
@end


