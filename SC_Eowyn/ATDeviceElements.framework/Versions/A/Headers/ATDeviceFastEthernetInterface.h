//
//  ATDeviceFastEthernetInterface.h
//  ATDeviceElements
//
//  Created by sai on 10/24/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATDeviceFastEthernetInterface : NSObject



@property (copy) NSString * IPaddress;

- (BOOL)   exchangeWithType: (NSInteger) type
           andPayloadToSend: (uint8_t*) outData
              andToSendSize: (uint32_t) outDataSize
andSendTimeOutInMilliSecond: (uint32_t) txTimeout
            anyTypeReceived: (NSInteger*) rxType
        andPayloadToReceive: (uint8_t*) inData
           andToReceiveSize: (uint32_t) inDataSize
    andTimeOutInMilliSecond: (uint32_t) timeout
                   andError: (NSError **) error;


- (id)initWithIPAddress:(NSString*)aIP;
-(BOOL) close;
// Open or Reopen the Interface.
-(BOOL) openWithError:(NSError **) error;

@end

NS_ASSUME_NONNULL_END
