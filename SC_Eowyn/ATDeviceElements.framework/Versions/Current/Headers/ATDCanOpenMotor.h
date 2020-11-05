//
//  ATDCanOpenMotor.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 1/23/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceFixtureProtocols.h>
#import <ATDeviceElements/ATDFixtureController.h>
#import <ATDeviceElements/ATDeviceCanOpen.h>

#define kVelocityMultiplier 240
#define kAccelerationMultiplier 6


@interface ATDCanOpenMotor : ATDFixtureController <ATDeviceMotionCapable,ATDeviceFixtureCapable>


@end
