//
//  ATDeviceGimliVersions.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 12/21/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceVersions.h>

#define kATDGimliInfoSize 5



@interface ATDeviceGimliVersions : ATDeviceVersions
@property (nonatomic) uint32_t stmFwVersion;
@property (nonatomic) uint32_t hwVersion;
@end
