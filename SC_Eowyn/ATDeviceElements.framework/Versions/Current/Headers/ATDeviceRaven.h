//
//  ATDeviceRaven.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 2/27/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>

@interface ATDeviceRaven : ATDeviceElement

- (BOOL) stopCurrentWithError:(NSError**) error;
- (BOOL) setCurrent:(uint16_t) current forChannel:(ATDChannelType) channel withPolarity:(ATDPolarityType) polarity andError:(NSError **)error;
-(BOOL) setCurrentToFloatValue:(float) current forChannel:(ATDChannelType) channel withPolarity:(ATDPolarityType) polarity andError:(NSError **)error;
@end
