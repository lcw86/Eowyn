//
//  ATDeviceSmartCableProtocol.h
//  ATDeviceElements
//
//  Created by Sai  on 8/22/18.
//  Copyright © 2018 htwe. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

@protocol ATDeviceSmartCableCapable < NSObject >


/**
 Increement cable count for attached neuton cable. Titanium needs to be vconn src to do this
 
 @param port This port is based on @sa ATDeviceTitaniumPortType
 @param aError error if increementing count didnt work
 @return Yes if cable count was increemented
 */
- (BOOL) IncrementCycleCountForPort:(NSInteger) port
                          andError:(out NSError**) aError;

/**
 Get cable count for attached neuton cable. Titanium needs to be vconn src to do this
 
 @param port his port is based on @sa ATDeviceTitaniumPortType
 @param aError error if getting count didnt work
 @return return cycle count
 */
- (NSInteger) cycleCountForPort:(NSInteger) port
                       andError:(out NSError**) aError;


@end
