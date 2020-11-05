//
//  ATDeviceDisplayPortProtocol.h
//  ATDeviceElements
//
//  Created by sai on 9/10/18.
//  Copyright © 2018 htwe. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

typedef NS_ENUM(uint8_t,ATDeviceDPRxPortType){
    ATDeviceDPRxPort0 = 0,
    ATDeviceDPRxPort1 = 1
};

typedef NS_ENUM(uint8_t,ATDeviceHPCDDPRxPortType){
    ATDeviceHPCD_DPRxPort0 = 0,
    ATDeviceHPCD_DPRxPort1,
    ATDeviceHPCD_HDMIPort,
    ATDeviceHPCD_MAXPort,
};
typedef NS_ENUM(uint8_t,ATDeviceDPTxPortType){
    ATDeviceDPTxPort0 = 0,
    ATDeviceDPTxPort1 = 1,
};

typedef NS_ENUM(uint8_t,ATDeviceInternalVideoPort){//These port namings are based on TestDevice FPGA I/O and are not compatible with 4CC command, API has to convert them to actual port number.
    ATDeviceInternalVideoPortRx0 = 0x10,
    ATDeviceInternalVideoPortRx1,
    ATDeviceInternalVideoPortHDMIRx,
    ATDeviceInternalVideoPortHDMITx,
    ATDeviceInternalVideoPortTx0,
    ATDeviceInternalVideoPortTx1
};

typedef NS_ENUM(uint8_t,ATDeviceHBRRateType){
    ATDeviceRateRBR  = 0,
    ATDeviceRateHBR  = 1,
    ATDeviceRateHBR2 = 2,
    ATDeviceRateHBR3 = 3
};

@protocol ATDeviceDisplayPortCapable < NSObject >


/** imageCRCWithNumberOfFrames
 * brief getting the CRC from the Test Device.
 *
 * param numFrames           Number frames to capture
 * param expectedDP0Red         expected DPRX0 Red
 * param expectedDP0Green       expected DPRX0 Green
 * param expectedDP0Blue        expected DPRX0 Blue
 * param expectedDP1Red         expected DPRX1 Red
 * param expectedDP1Green       expected DPRX1 Green
 * param expectedDP1Blue        expected DPRX1 Blue
 * param[out] aError nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval ATDeviceColor32bitCRC:             the Struct of the CRC
 *
 */
- (ATDeviceColor32bitCRC*)  imageCRCWithNumberOfFrames: (uint16_t) numFrames
                                        expectedDP0Red: (uint32_t) expectedDP0Red
                                      expectedDP0Green: (uint32_t) expectedDP0Green
                                       expectedDP0Blue: (uint32_t) expectedDP0Blue
                                        expectedDP1Red: (uint32_t) expectedDP1Red
                                      expectedDP1Green: (uint32_t) expectedDP1Green
                                       expectedDP1Blue: (uint32_t) expectedDP1Blue
                                                 error: (out NSError**) aError;


/**imageDPTXCRCWithDurationInSec
 calculate CRC during a given time， on DPTx0 and DPTx1. Both port can be enabled at the same time.
 
 @param durationInSec              Test duration in Sec.
 @param enableDPTx0                calculate CRC on DPTx0
 @param enableDPTx1                calculate CRC on DPTx1
 @param expectedDPTX0Red           expected DPTx0 Red
 @param expectedDPTX0Green         expected DPTx0 Green
 @param expectedDPTX0Blue          expected DPTx0 Blue
 @param expectedDPTX1Red           expected DPTx1 Red
 @param expectedDPTX1Green         expected DPTx1 Red
 @param expectedDPTX1Blue          expected DPTx1 Red
 @param[out] aError               nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 @return ATDeviceColor32bitCRC:     the Struct of the CRC
 */
- (ATDeviceColor32bitCRC*)  imageDPTxCRCWithDurationInSec: (uint16_t) durationInSec
                                           andEnableDPTx0: (BOOL) enableDPTx0
                                           andEnableDPTx1: (BOOL) enableDPTx1
                                         expectedDPTX0Red: (uint32_t) expectedDPTX0Red
                                       expectedDPTX0Green: (uint32_t) expectedDPTX0Green
                                        expectedDPTX0Blue: (uint32_t) expectedDPTX0Blue
                                         expectedDPTX1Red: (uint32_t) expectedDPTX1Red
                                       expectedDPTX1Green: (uint32_t) expectedDPTX1Green
                                        expectedDPTX1Blue: (uint32_t) expectedDPTX1Blue
                                                    error: (out NSError**) aError;




/**
 displayPortLinkStatusAt get Link Status from TX or RX
 
 @param aTxOrRx ATDDisplayPortTX or ATDDisplayPortRX
 @param aError nil = NO error, or error set.
 @return ATDeviceDisplayPortLinkStatus
 
 ATDeviceDisplayPortLinkStatus:
 BOOL      statusPassed;
 NSInteger DPTx0laneCount;
 NSInteger DPTx0linkBandwidthGbps;
 NSInteger DPTx0status;
 NSInteger DPTx1laneCount;
 NSInteger DPTx1linkBandwidthGbps;
 NSInteger DPTx1status;
 NSData * rawData; Data from back from the Palladium. They match what in the User Manual
 
 */
- (ATDeviceDisplayPortLinkStatus*) displayPortLinkStatusAt: (ATDDisplayPortTxRx) aTxOrRx
                                                  andError: (out NSError**) aError;



/**
 Change HBR rate on DP port so next time it link trains , it will choose this selected rate.
 This means you have to send a command to link train after setting this rate
 
 @param dpRxPort check @sa ATDeviceDPRxPortType
 @param rate check @sa ATDeviceHBRRateType
 @param persistence if set this rate will be set at next reboot
 @param aError error is set if there was an error changing rate
 @return yes if succesfuly set else no
 */
-(BOOL) changeHBRRateOnDPPort:(ATDeviceDPRxPortType) dpRxPort
                       toRate:(ATDeviceHBRRateType) rate
              withPersistence:(BOOL)persistence
                     andError:(out NSError **)aError;


- (ATDeviceVideoStatus*) videoStatusForDPRx: (NSInteger) dpIndex
                                   andError: (out NSError**) aError;

/** readDPCDRegisterAt
 * brief Read DPCD register
 *
 * param address           DP Address
 * param aTxOrRx:          Read DPTt or DPRx
 * param coreSpace         Set it to YES if reading DP core space
 * param DPRxIndex         DPRX0 or DPRX1.
 * param[out]               upperReg    upper 64bit of the DPCD register
 * param[out]               lowerReg    lower 64bit of the DPCD register
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval uint32_t:         value from DPCD register;
 *
 *
 */
- (BOOL)     readDPCDRegisterAt: (uint32_t) address
                      andTxOrRx: (ATDDisplayPortTxRx) aTxOrRx
                 andIsCoreSpace: (BOOL) coreSpace
                   andDPRXIndex: (NSInteger) DPRxIndex
               andUpperRegister: (out uint64_t*) upperReg
               andLowerRegister: (out uint64_t*) lowerReg
                       andError: (out NSError**) aError;


/** writeDPCDRegisterAt
 * brief write DPCD register
 *
 * param address           DP Address
 * param writeData         uint16_t data to write
 * param aTxOrRx           Read DPTt or DPRx
 * param coreSpace         Set it to YES if reading DP core space
 * param DPRxIndex         DPRX0 or DPRX1.
 * param[out] aError nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval BOOL:             Command Sucess or Fail
 *
 *
 */

- (BOOL)    writeDPCDRegisterAt: (uint32_t) address
                       withData: (uint32_t) writeData
                      andTxOrRx: (ATDDisplayPortTxRx) aTxOrRx
                 andIsCoreSpace: (BOOL) coreSpace
                   andDPRXIndex: (NSInteger) DPRxIndex
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

/**
 Set DPTx Link Delay
 
 @param delay        Link Delay in nano seconds
 @param save         0 = not saved, 1 = saved setting to EEpprom
 @param aError       when there is an error, this will be set
 @return             BOOL:    YES = successed with no Error.
 NO  = Error occured;
 */
- (BOOL)    dptxLinkDelayInNanoSecond: (uint32_t) delay
                     andSaveToEEpprom: (BOOL) save
                             andError: (out NSError**) aError;

/**
 Read EDID from the attached sink on the Titanium TBTC and TBTD ports.

 @param aPort DPTX0 = 0, DPTX1 = 1
 @param aError when there is an error, this will be set
 @return EDID value
 */
- (NSData*)    edidFromAttachedSinkOnPort: (NSInteger) aPort
                                 andError: (out NSError**) aError;

/**
 Read the currently loaded EDID for the Titanium DisplayPort ports and HDMI port.

 @param aPort DPRX0=0, DPRX1=1, HDMI RX=2
 @param aError when there is an error, this will be set
 @return EDID value
 */
- (NSData*)    edidFromFPGAOnPort: (NSInteger) aPort
                         andError: (out NSError**) aError;
@end

