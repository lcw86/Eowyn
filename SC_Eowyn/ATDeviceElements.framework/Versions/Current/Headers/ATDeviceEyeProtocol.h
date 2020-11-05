//
//  ATDeviceEyeProtocol.h
//  ATDeviceElements
//
//  Created by sai on 10/29/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#ifndef ATDeviceEyeProtocol_h
#define ATDeviceEyeProtocol_h
#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

@protocol ATDeviceEyeCaptureCapable < NSObject >


- (ATDeviceEyeResult *) captureEyeOnPort: (uint8_t)  portNumber
                               andOnLane: (uint8_t)  lane
                      andNumberOfSamples: (uint32_t) numOfSamples
                       andErrorThreshold: (uint32_t) errorThreshold
                        andOpenThreshold: (uint32_t) openThreshold
                 andTimeOutInMilliSecond: (uint32_t) timeout
                                andError: (out NSError**) error;
@end
#endif /* ATDeviceEyeProtocol_h */
