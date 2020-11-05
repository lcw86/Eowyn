//
//  ATDeviceUartInterface.h
//
//

#import "ATDeviceBusInterfaceBase.h"

@interface ATDeviceUartInterface : ATDeviceBusInterface


- (id)initWithDevPath:(NSString*)aPath;

- (id)initWithDevPath:(NSString*)aPath
    andInterCharDelay:(double)delay;

-(BOOL) readBytes : (NSData**)bytes
      withTimeout : (double)timeout
        withError : (NSError**)error;

@end
