//
//  ATDeviceIodine.h
//  ATDeviceElements
//
//  Created by Sai  on 2/13/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>

@interface ATDeviceIodine : ATDeviceElement



- (BOOL) writeBlockSerialNumber: (uint64_t) serialNumber WithError:(NSError**) error;

- (uint64_t) blockSerialNumberWithError:(NSError**) error;

- (BOOL) writeCalibrationData: (double) data  andAddress: (NSInteger) address  WithError  :(NSError**) error;

- (double) calibrationDataAtAddress:(NSInteger) address WithError:(NSError**) error;


@end
