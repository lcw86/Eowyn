//
//  ATDeviceMantisVersions.h
//  ATDeviceElements
//
//  Created by Sai  on 2/16/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceVersions.h>

#define kATDeviceMantisInfoSize 13

@interface ATDeviceMantisVersions : ATDeviceVersions

@property (nonatomic) uint32_t stmFwVersion;
@property (nonatomic) uint32_t fx3FwVersion;
@property (nonatomic) uint32_t lowSpeedControllerFwVersion;
@property (nonatomic) uint32_t hwVersion;


-(id) initWithData:(NSData*) data;

@end
