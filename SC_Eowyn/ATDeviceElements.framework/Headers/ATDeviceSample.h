//
//  ATDeviceSample.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 7/17/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATDeviceSample : NSObject
@property NSTimeInterval timestamp;
@property NSArray<NSNumber*>* samples;

+(ATDeviceSample*) sampleWithTimestamp: (NSTimeInterval) ts
                           andSamples: (NSArray<NSNumber*>*) samples;
-(id) initWithTimestamp: (NSTimeInterval) ts
             andSamples: (NSArray<NSNumber*>*) samples;
-(NSString*) sampleAsCsv;
@end

NS_ASSUME_NONNULL_END
