//
//  ATDFixtureController.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 1/26/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATDeviceFixtureProtocols.h"
#import <ATDeviceElements/ATDeviceExtensionBoard.h>


@interface ATDFixtureController : NSObject < ATDeviceFixtureCapable>


-(id _Nullable ) initWithExtensionBoard:(nonnull ATDeviceExtensionBoard *) aExtensionBoard;
@property (nonatomic, strong)  ATDeviceExtensionBoard* _Nullable extensionBoard;

@end
