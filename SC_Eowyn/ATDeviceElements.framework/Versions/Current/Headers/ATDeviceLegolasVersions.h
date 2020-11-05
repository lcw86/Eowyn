//
//  ATDeviceLegolasVersions.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 12/21/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceVersions.h>

#define kATDLegolasInfoSize 5



@interface ATDeviceLegolasVersions : ATDeviceVersions
@property (nonatomic) uint32_t stmFwVersion;
@property (nonatomic) uint32_t hwVersion;
@end
