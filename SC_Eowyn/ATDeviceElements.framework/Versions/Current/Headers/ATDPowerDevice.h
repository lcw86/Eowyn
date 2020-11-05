//
//  ATDPowerDevice.h
//  ATDeviceElements
//
//  Created by Sai  on 3/26/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>
#import <ATDeviceElements/ATDeviceParameters.h>
#define kPDStateAddress          69
#define kPulseLengthAddress     117
#define kCurrentLimitAddress    118
#define kVoltageLimitAddress    119
#define kPowerLimitAddress      120
#define kResistanceLimitAddress 121
#define kCurrentAddress         128
#define kVoltageAddress         129
#define kPowerAddress           130
#define kCalibratedDate         242
#define KMaxChannels             16
#define KNumberOfChannelsAddress 97

typedef NS_ENUM(uint32_t, ATDPowerDeviceMode) {
    ATDPowerDeviceModeChannelModeOff = 0x00,
    ATDPowerDeviceModeChannelModeReset = 0x01,
    ATDPowerDeviceModeChannelModeConstantCurrentVoltagePowerResistanceLoad = 0x10,
    ATDPowerDeviceModeChannelModeConstantCurrentLoad = 0x11,
    ATDPowerDeviceModeChannelModeConstantVoltageLoad = 0x12,
    ATDPowerDeviceModeChannelModeConstantPowerLoad = 0x13,
    ATDPowerDeviceModeChannelModeConstantResistanceLoad = 0x14,
    ATDPowerDeviceModeChannelModeConstantCurrentVoltagePowerSource = 0x20,
    ATDPowerDeviceModeChannelModeConstantCurrentSource = 0x21,
    ATDPowerDeviceModeChannelModeConstantVoltageSource = 0x22,
    ATDPowerDeviceModeChannelModeConstantPowerSource = 0x23,
    ATDPowerDeviceModeChannelModeConstantVoltageBiDirectional= 0x80,
    ATDPowerDeviceModeChannelModeCalibration = 0xF0,
    ATDPowerDeviceModeChannelModeError = 0xFD,
    ATDPowerDeviceModeChannelModeDebug = 0xFE
    
};
typedef NS_ENUM(uint8_t, ATDPowerDeviceChannel) {
    ATDPowerDeviceChannel1=1,
    ATDPowerDeviceChannel2=2,
    ATDPowerDeviceChannel3=3,
    ATDPowerDeviceChannel4=4,
    ATDPowerDeviceChannel5=5,
    ATDPowerDeviceChannel6=6,
    ATDPowerDeviceChannel7=7,
    ATDPowerDeviceChannel8=8,
    ATDPowerDeviceChannel9=9,
    ATDPowerDeviceChannel10=10,
    ATDPowerDeviceChannel11=11,
    ATDPowerDeviceChannel12=12,
    ATDPowerDeviceChannel13=13,
    ATDPowerDeviceChannel14=14,
    ATDPowerDeviceChannel15=15,
    ATDPowerDeviceChannel16=16
};

@interface ATDPowerDevice : ATDeviceElement

-(BOOL) emergencyStopOnAllChannelsWithError:(NSError **)error;

-(BOOL) changeModeOnChannelsForIndex:(uint16_t) channelIndex
                     toMode:(ATDPowerDeviceMode) mode
                  withError:(NSError **) aError;

- (NSNumber *) temperatureOfSensorAtIndex: (NSInteger) sensorIndex
                                 andError: (NSError**) anError;


/*-(BOOL) switchOffModeOnChannel:(uint16_t) channelIndex
                     withError:(NSError **) aError;*/

/*-(BOOL) enableConstantCurrentModeOnChannel:(ATDPowerDeviceChannel) channel
                           withError:(NSError **) aError;*/


-(BOOL) changeParametersOnChannel:(ATDPowerDeviceChannel) channel
               withCurrentLimitInAmps:(float) currentLimit
               andVoltageLimitInVolts:(float) voltageLimit
                 andPowerLimitInWatts:(float) powerLimit
         andResistanceLimitInOhms:(float) resistanceLimit
                andDurationInMilliSec:(NSUInteger) duration
                            withError:(NSError **) aError;

-(BOOL) writeClockOnChannel:(ATDPowerDeviceChannel) channel
                    toValueInMilliSeconds:(NSUInteger) value
                  withError:(NSError **) aError;

-(BOOL) writeCurrentLimitOnChannel:(ATDPowerDeviceChannel) channel
                    withValueInAmps:(float) currentValue
                    withError:(NSError **) aError;
-(float) readCurrentLimitInAmpsOnChannel:(ATDPowerDeviceChannel)channel
                         withError:(NSError **) aError;
-(float) readCurrentInAmpsOnChannel:(ATDPowerDeviceChannel)channel
                    withError:(NSError **) aError;

-(float) readVoltageLimitInVoltsOnChannel:(ATDPowerDeviceChannel)channel
                         withError:(NSError **) aError;
-(float) readVoltageInVoltsOnChannel:(ATDPowerDeviceChannel)channel
                    withError:(NSError **) aError;
-(BOOL) writeVoltageLimitOnChannel:(ATDPowerDeviceChannel) channel
                    withValueInVolts:(float) voltageValue
                    withError:(NSError **) aError;


-(BOOL) writePowerLimitOnChannel:(ATDPowerDeviceChannel) channel
                  withValueInWatts:(float) powerValue
                  withError:(NSError **) aError;
-(float) readPowerInWattsOnChannel:(ATDPowerDeviceChannel)channel
                  withError:(NSError **) aError;
-(float) readPowerLimitInWattsOnChannel:(ATDPowerDeviceChannel)channel
                       withError:(NSError **) aError;

-(BOOL) isCalibratedOnChannel:(ATDPowerDeviceChannel)channel withError:(NSError **) aError;

-(NSUInteger) numberOfChannelswithError:(NSError **) aError;

-(NSUInteger) readPulseLengthOnChannelInMilliSeconds:(ATDPowerDeviceChannel)channel
                             withError:(NSError **) aError;
-(BOOL) writePulseLengthOnChannel:(ATDPowerDeviceChannel) channel
                        withValueInMilliSeconds:(NSUInteger) pulseLength
                        withError:(NSError **) aError;

-(BOOL) writeResistanceLimitOnChannel:(ATDPowerDeviceChannel) channel
                withValueInOhms:(float) resistanceValue
                       withError:(NSError **) aError;

//-(ATDevicePowerParameters *) readPowerDeviceParametersOnChannel:(ATDPowerDeviceChannel) channel
//withError:(NSError **)aError;

@end
