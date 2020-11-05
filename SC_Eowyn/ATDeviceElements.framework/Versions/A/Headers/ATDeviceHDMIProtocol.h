//
//  ATDeviceHDMI.h
//  ATDeviceElements
//
//  Created by Sai  on 8/22/18.
//  Copyright © 2018 htwe. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

typedef NS_ENUM(uint8_t,ATDeviceHDMIEyeSampleRateType){
    ATDeviceHDMIEyeSampleRate127,
    ATDeviceHDMIEyeSampleRate1023,
    ATDeviceHDMIEyeSampleRate8191,
    ATDeviceHDMIEyeSampleRate65535
};

@protocol ATDeviceHDMICapable < NSObject >

/** HDMICRCWithNumberOfFrames
 * brief getting the CRC from the Test Device.
 *
 * param numFrames:                 Number frames to capture
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval ATDeviceColor32bitCRC:             the Struct of the CRC
 *
 */
- (ATDeviceRGBColorCRC*) hdmiCRCWithNumOfFrames: (NSInteger) numFrames
                                          error: (out NSError**) aError;

- (ATDeviceHDMIStatus*) videoStatusForHDMIWithError: (out NSError**) aError;

/**
 Grabs Eye Diagram of chosen HDMI lane at specified sample rate and gets width/height
 
 @param lane Specify the HDMI lane you want an eye diagram of
 @param width Determines how many samples you want to take for the eye
 @param height Rx eye height at the lane
 @param dumpLog Dump eye graph to debug port 4445 if TRUE
 @param aError error is set if there was an error reading rx eye
 @return yes if successfully read else no
 */
- (BOOL) readHDMIRxEyeAtLane: (NSInteger) lane
               andSampleRate: (ATDeviceHDMIEyeSampleRateType) sample
                    andWidth: (out NSInteger*) width
                   andHeight: (out NSInteger*) height
          dumpLogToDebugPort: (BOOL) dumpLog
                    andError: (out NSError**) aError;

/**
 Asserts HPD for passed duration on titanium port
 
 @param port check @sa ATDeviceTitaniumPortType
 @param duration time in milliseconds for which hpd is asserted
 @param aError error is set if there was an error asserting hpd
 @return yes if succesfuly asserted  else no
 */
-(BOOL)     assertHPDOnPort:(ATDeviceTitaniumPortType) port
      durationInMilliSecond:(NSInteger) duration
                   andError:(out NSError **)aError;


/**
 Force HPD level low on Titanium port.
 
 @param port check @sa ATDeviceTitaniumPortType
 @param aError error is set if there was an error asserting hpd
 @return yes if succesfuly asserted  else no
 */
-(BOOL)     forceHPDLowOnPort:(ATDeviceTitaniumPortType) port
                     andError:(out NSError **)aError;

@optional
/**
 Set HDMI CEC Low or High

 @param high set High to YES for (HIGH) or setHigh to NO (LOW)
 @param aError error is set if there was an error setting high/low
 @return yes if succesfuly set high/low else return no
 */
- (BOOL) assertHdmiCEC: (BOOL) high andError: (out NSError**) aError;


/**
 Query HDMI CEC state

 @param aError error is set if there was an error querying
 @return 0 = CEC Low, 1 = CEC High, 0xFF = Error
 */
- (NSInteger) hdmiCECStateWithError: (out NSError**) aError;


/**
Start send out ARC or EARC at specific I2S clock speed with pattern setting

 @param speed I2S clock speed setting
 @param arcType ARC or eARC
 @param transmitSize data size to be tranmitted
 @param hpdDisconnectTime hpd disconnect time
 @param arcRetryCount for retry for ARC
 @param delayBeforeReadMuteStateInSecond delay in second before reading the mute status
 @param delayBetweenTestDeviceInstructionInSecond delay in second between consecutive 4CC calls
 @param aError set if there any error in the send arc process setup
 @param sendStaticPattern set to send out static patter, default PRBS pattern
 @return yes if successfully start sending else return no
 */
- (BOOL) startSendArcAtSpeed: (ATDeviceArcI2SClockSpeed) speed
                  andArcType: (ATDeviceArcType) arcType
             andTransmitSize: (ATDeviceArcTransmitSize) transmitSize
andHPDDisconnectInMilliSecond: (NSInteger) hpdDisconnectTime
            andArcRetryCount: (NSInteger) arcRetryCount
 andDelayBeforeReadMuteStateInSecond: (NSInteger) delayBeforeReadMuteStateInSecond
          andDelayBetweenTestDeviceInstructionInSecond: (NSInteger) delayBetweenTestDeviceInstructionInSecond
            andSendStaticPattern: (BOOL) sendStaticPattern
                    andError: (out NSError **)aError;

/**
 Start send out ARC or EARC at specific I2S clock speed
 
 @param speed I2S clock speed setting
 @param arcType ARC or eARC
 @param transmitSize data size to be tranmitted
 @param hpdDisconnectTime hpd disconnect time
 @param arcRetryCount for retry for ARC
 @param delayBeforeReadMuteStateInSecond delay in second before reading the mute status
 @param delayBetweenTestDeviceInstructionInSecond delay in second between consecutive 4CC calls
 @param aError set if there any error in the send arc process setup
 @return yes if successfully start sending else return no
 */
- (BOOL) startSendArcAtSpeed: (ATDeviceArcI2SClockSpeed) speed
                  andArcType: (ATDeviceArcType) arcType
             andTransmitSize: (ATDeviceArcTransmitSize) transmitSize
andHPDDisconnectInMilliSecond: (NSInteger) hpdDisconnectTime
            andArcRetryCount: (NSInteger) arcRetryCount
andDelayBeforeReadMuteStateInSecond: (NSInteger) delayBeforeReadMuteStateInSecond
andDelayBetweenTestDeviceInstructionInSecond: (NSInteger) delayBetweenTestDeviceInstructionInSecond
                    andError: (out NSError **)aError;

/**
 Stop send out ARC or EARC
 
 @param aError error is set if error happen in the transaction
 @return yes if successfully start sending else no
 */
- (BOOL) stopSendArc: (out NSError **)aError;


@end
