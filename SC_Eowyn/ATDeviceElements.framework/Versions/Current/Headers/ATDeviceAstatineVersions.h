//
//  ATDeviceAstatineVersions.h
//  ATDeviceAtlasBundle
//
//  Created by Clark on 2019/6/19.
//  Copyright © 2019 kenneth leung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceVersions.h>

@interface ATDeviceAstatineVersions : ATDeviceVersions

@property (nonatomic) uint32_t stmFwVersion;
@property (nonatomic) uint64_t fpgaFwVersion;
@property (nonatomic) uint32_t hwVersion;

-(id) initWithData:(NSData*) data;

@end

