//
//  ATDPDControllerProtocols
//  ATDeviceElements
//
//  Created by Yuanyuan Tian on 12/6/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#ifndef ATDPDControllerProtocols_h
#define ATDPDControllerProtocols_h

#import <ATDeviceElements/ATDevicePDControllerParameter.h>

@protocol ATDPDControlCapable < NSObject >

/**
 Read USBC port Power status out of USBC device.
 
 @param portIndex   Port to read
 @param aError      aError return error from test device.
 @return            ATDevicePortsPowerStatus object
 */
-(ATDevicePortsPowerStatus*) powerStatusOnPort:(NSUInteger) portIndex
                                      andError:(out NSError **) aError;

@end
#endif /* ATDPDControllerProtocols_h */
