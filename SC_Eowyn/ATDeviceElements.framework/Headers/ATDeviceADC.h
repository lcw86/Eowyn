//
//  ATDeviceIzzyADC.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 5/15/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATDeviceSample.h"
#import <ATDeviceElements/ATDeviceElement.h>

#define SetERROR(errorPtr, errorCode, formatStr, ...) {\
if ((errorPtr)) { \
*(errorPtr) = [NSError errorWithDomain:@"ATestDeviceErrorDomain" \
code:(errorCode) \
userInfo:@{NSLocalizedDescriptionKey : [NSString stringWithFormat:@"%@", [NSString stringWithFormat:(formatStr), ##__VA_ARGS__]]}]; \
} \
}

NS_ASSUME_NONNULL_BEGIN

@interface ATDeviceADC : NSObject

//@property (strong, nonatomic, readonly) ATDeviceBusInterface * communicationInterface;

-(id) initWithLocationID: (uint32_t)locationID;
         //andBusInterface:(ATDeviceBusInterface *)interface;

-(BOOL) openWithError: (out NSError**)error;

-(BOOL) close;

void readCallback(void *refcon, IOReturn result, void *arg0);
//-(void) readCallBackWithReference:(void *)refcon andResult:(IOReturn) result andArgument:(void *)arg0;

-(NSArray<ATDeviceSample*>*) gatherDataForTime: (NSTimeInterval)time
                                 andDelayInMilliseconds:(NSTimeInterval)delay
                                 withError: (out NSError**)error;

//-(BOOL) setSyncPulseForVoltageInMilliVolts:(uint16_t) voltage
 //                andDurationInMilliSeconds:(uint16_t)duration
  //                                andError: (out NSError**) anError;

@end

NS_ASSUME_NONNULL_END
