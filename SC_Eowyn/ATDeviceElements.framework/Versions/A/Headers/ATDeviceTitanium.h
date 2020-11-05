//
//  ATDeviceTitanium.h
//  ATDeviceElements
//
//  Created by Sai  on 8/14/17.
//  Copyright © 2017 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDevicePalladium.h>
#import <ATDeviceElements/ATDeviceParameters.h>
#import <ATDeviceElements/ATDeviceHDMIProtocol.h>
#import <ATDeviceElements/ATDeviceSmartCableProtocol.h>
#import <ATDeviceElements/ATDeviceDisplayPortProtocol.h>
#import <ATDeviceElements/ATDevicePatternGeneratorProtocol.h>
#import <ATDeviceElements/ATDeviceEyeProtocol.h>

typedef NS_ENUM(uint8_t,ATDeviceTBTPortModeType){
    ATDeviceModeUSB = 255,
    ATDeviceModeTBT = 0,
    ATDeviceModeDP = 1,
    ATDeviceModeDaisyChain = 2,
    ATDeviceModeDisableUSB = 8
};

typedef NS_ENUM(uint8_t,ATDeviceUSB2HostPortType){
    ATDeviceUSB2HostDPRx1Port = 0,
    ATDeviceUSB2HostTBTAPort = 1
};


typedef NS_ENUM(uint8_t,ATDeviceTBTPortUSBPassThroughSpeedType){
    ATDeviceTBTPortUSBPassThroughSpeedTypeSuperSpeed = 3,
    ATDeviceTBTPortUSBPassThroughSpeedTypeSuperSpeedPlus = 4,
    ATDeviceTBTPortUSBPassThroughSpeedTypeHighSpeed = 5,
    ATDeviceTBTPortUSBPassThroughSpeedTypeFullSpeed = 6,
    ATDeviceTBTPortUSBPassThroughSpeedTypeLowSpeed = 7,
    ATDeviceTBTPortUSBPassThroughSpeedTypeDisableUSB = 8,
};



/**
 TBTM mode options

 - ATDeviceTBTPortOnePlugTunnelMode: Set titanium to TBT single stream mode
 - ATDeviceTBTPortOnePlugAltMode: Set titanium to Native DP alternative mode
 - ATDeviceTBTPortOnePlugDaisyChain: Set titanium to daisy chain dp configuration mode. UUT will see 2 displays from one Titanium.
 - ATDeviceTBTPortOnePlugUSBSuperSpeed: Set titanium to usb super speed pass through mode. Tx/Rx will be SS only and USB2.0 connected to the Ti USB hub
 - ATDeviceTBTPortOnePlugUSBSuperSpeedPlus: Set titanium to usb super speed plus pass through mode
 - ATDeviceTBTPortOnePlugUSBHighSpeed: Set titanium to usb high speed pass through mode
 - ATDeviceTBTPortOnePlugUSBFullSpeed: Set titanium to usb full speed pass through mode
 - ATDeviceTBTPortOnePlugLowSpeed: Set titanium to usb low speed pass through mode
 - ATDeviceTBTPortOnePlugDisableUSB: Set titanium to disable usb mode. No USB and no TBT/DP at all. For Sleep Wake test only.
 - ATDeviceTBTPortOnePlugTunnelAndSuperSpeed: Set titanium to TBT mode with usb super speed pass through enabled. cio and USB SS mode.  DP is on.
 - ATDeviceTBTPortOnePlugTunnelAndSuperSpeedPlus: Set titanium to TBT mode with usb super speed plus pass through enabled.cio and USB SS+ mode.  DP is on.
 - ATDeviceTBTPortOnePlugTunnelAndHighSpeed: Set titanium to TBT mode with usb high speed pass through enabled. cio and USB HS mode.  DP is on.
 - ATDeviceTBTPortOnePlugTunnelAndFullSpeed: Set titanium to TBT mode with usb full speed pass through enabled. cio and USB FS mode.  DP is on.
 - ATDeviceTBTPortOnePlugTunnelAndLowSpeed: Set titanium to TBT mode with usb low speed pass through enabled.   cio and USB LS mode.  DP is on.
 - ATDeviceTBTPortOnePlugTunnelAndDisableUSB: Set titanium to TBT mode with usb disabled        cio and  NO USB.  DP is on.
 - ATDeviceTBTPortOnePlugAltAndHighSpeed: Set titanium to DP alternative mode with usb high speed pass through enabled. DP Alt Mode with USB HS.
 - ATDeviceTBTPortOnePlugAltAndFullSpeed: Set titanium to DP alternative mode with usb full speed pass through enabled. DP Alt Mode with USB FS.
 - ATDeviceTBTPortOnePlugAltAndLowSpeed: Set titanium to DP alternative mode with usb low speed pass through enabled.   DP Alt Mode with USB LS.
 - ATDeviceTBTPortOnePlugAltAndDisableUSB: Set titanium to DP alternative mode with usb disabled                        DP Alt Mode with NO USB.
 */
typedef NS_ENUM(uint8_t,ATDeviceTBTPortOnePlugModes){
    ATDeviceTBTPortOnePlugTunnelMode = 0,
    ATDeviceTBTPortOnePlugAltMode = 1,
    ATDeviceTBTPortOnePlugDaisyChain = 2,
    ATDeviceTBTPortOnePlugUSBSuperSpeed = 3,
    ATDeviceTBTPortOnePlugUSBSuperSpeedPlus = 4,
    ATDeviceTBTPortOnePlugUSBHighSpeed = 5,
    ATDeviceTBTPortOnePlugUSBFullSpeed = 6,
    ATDeviceTBTPortOnePlugLowSpeed = 7,
    ATDeviceTBTPortOnePlugDisableUSB = 8,
    ATDeviceTBTPortOnePlugTunnelAndSuperSpeed = 9,
    ATDeviceTBTPortOnePlugTunnelAndSuperSpeedPlus = 10,
    ATDeviceTBTPortOnePlugTunnelAndHighSpeed = 11,
    ATDeviceTBTPortOnePlugTunnelAndFullSpeed = 12,
    ATDeviceTBTPortOnePlugTunnelAndLowSpeed = 13,
    ATDeviceTBTPortOnePlugTunnelAndDisableUSB = 14,
    ATDeviceTBTPortOnePlugAltAndHighSpeed = 15,
    ATDeviceTBTPortOnePlugAltAndFullSpeed = 16,
    ATDeviceTBTPortOnePlugAltAndLowSpeed = 17,
    ATDeviceTBTPortOnePlugAltAndDisableUSB = 18
};

typedef NS_ENUM(uint8_t,ATDeviceTBTTxPortModes){
    ATDeviceDPTxPortTunnelMode = 0,
    ATDeviceDPTxPortDPAltMode,
    ATDeviceDPTxPortUSBMode,
    ATDeviceDPTxPortMultiMode,
    ATDeviceDPTxPortDPOverDriveMode
};

typedef NS_ENUM(uint8_t,ATDeviceTBTPortType) {
    ATDevicePortTBTA = 0,
    ATDevicePortTBTB = 1
};
typedef NS_ENUM(uint8_t,ATDeviceTBTTxPortType) {
    ATDevicePortTBTC = 0,
    ATDevicePortTBTD = 1
};
typedef NS_ENUM(uint8_t,ATDeviceTitaniumMaxEDIDResolutionType) {
    ATDeviceTitaniumMaxEDIDResolution8k = 0,
    ATDeviceTitaniumMaxEDIDResolution5k,
    ATDeviceTitaniumMaxEDIDResolution4k,
    ATDeviceTitaniumHDMIMaxEDIDResolution4k,
    ATDeviceTitaniumHDMIRadonEDIDResolution
    
};

@interface ATDeviceTitanium :  ATDevicePalladium <ATDeviceHDMICapable, ATDeviceSmartCableCapable, ATDeviceDisplayPortCapable, ATDevicePatternGeneratorCapable,ATDeviceEyeCaptureCapable>
/**
 sets usb passthrough on port from ATDeviceTitaniumPortType
 
 @param portType based on ATDeviceTitaniumPortType
 @param persistence if set writes persistence to eeprom and always will allow ethernet bypass on port
 @param aError set if there is any error
 @return NO if setting ethernet bypass on port fails
 */
-(BOOL) enableUSBPassThroughOnPort:(ATDeviceTitaniumPortType) portType withPersistence:(BOOL)persistence andError:(NSError *__autoreleasing *)aError;



/**
 Switch EDID to passed max resolution

 @param resolution max resoltion sent as part of EDID based on ATDeviceTitaniumMaxEDIDResolutionType
 @param persistence if set writes persistence to eeprom and always will allow max resolution as part of EDID to passed resolution value
 @param aError set if there is any error
 @return No if setting to the passed max resolution as part of EDID message fails
 */
-(BOOL) switchEDIDToMaxResolution:(ATDeviceTitaniumMaxEDIDResolutionType) resolution withPersistence:(BOOL)persistence andError:(NSError *__autoreleasing *)aError;


/**
 sets ethernet passthrough on port from ATDeviceTitaniumPortType

 @param portType based on ATDeviceTitaniumPortType
 @param persistence if set writes persistence to eeprom and always will allow ethernet bypass on port
 @param aError set if there is any error
 @return NO if setting ethernet bypass on port fails
 */
-(BOOL) enableEthernetOnPort:(ATDeviceTitaniumPortType) portType withPersistence:(BOOL)persistence andError:(NSError *__autoreleasing *)aError;

/**
 convertTBTPort   switch TBTA/B to either Tunneled DP or Native DP.

 @param tbtPort ATDevicePortTBTA or ATDevicePortTBTB
 @param mode ATDeviceModeTBT or ATDeviceModeDP or ATDeviceModeDaisyChain or ATDeviceModeDisableUSB
 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
- (BOOL) convertTBTPort:(ATDeviceTBTPortType) tbtPort toMode:(ATDeviceTBTPortModeType) mode andError:(NSError **)aError;

/**
 deprecated disableDPPath   disable DP path between TBTA and FPGA
 deprecated Use disableDisplayPortWithError and enableDisplayPortWithError instead.
 
 @param isDisabled Bool, YES or NO
 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
- (BOOL) disableDPPath:(BOOL) isDisabled andError:(NSError **)aError;
/**
   Disable the Display Port , so the UUT can't see Titaium as a Display.

 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
- (BOOL) disableDisplayPortWithError:(NSError **)aError;
/**
   Enable the Display Port , so the UUT can see Titaium as a Display.
 
 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
- (BOOL) enableDisplayPortWithError:(NSError **)aError;
/**
 Change the usb passthrough speed for selected tbt port

 @param tbtPort ATDevicePortTBTA or ATDevicePortTBTB
 @param speed ATDeviceTBTPortUSBPassThroughSpeedType
 @param disconnectTime disconnect time in ms
 @param enumerationTimeout Timeout value for reenumeration in ms
 @param actualSpeed returns actual speed except for low speed mode
 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
-(BOOL) changeSpeedForUSBPassThroughOnTBTPort:(ATDeviceTBTPortType) tbtPort
            toSpeed:(ATDeviceTBTPortUSBPassThroughSpeedType) speed
            disconnectTimeInMilliSec: (uint16_t) disconnectTime
            enumerationTimeoutInMilliSec:(uint16_t) enumerationTimeout
            andActualSpeed:(uint8_t *) actualSpeed
            andError:(NSError **)aError;

/**
 Change TBTM mode for selected tbt port for one plug mode only (setup - Caesium is attached to titanium through can
 and all caesium mode changes are handled by titanium)
 
 @param tbtPort ATDevicePortTBTA or ATDevicePortTBTB
 @param mode ATDeviceTBTPortUSBPassThroughSpeedType
 @param disconnectTime disconnect time in ms
 @param enumerationTimeout Timeout value for reenumeration in ms
 @param aError set if there is any error
 @return YES = Sucess or NO = Fail
 */
-(BOOL) changeOnePlugModeOnTBTPort:(ATDeviceTBTPortType) tbtPort
                            toMode:(ATDeviceTBTPortOnePlugModes) mode
          disconnectTimeInMilliSec: (uint16_t) disconnectTime
      enumerationTimeoutInMilliSec:(uint16_t) enumerationTimeout
                    andActualSpeed:(uint8_t *) actualSpeed
                          andError:(NSError **)aError;


/**
 Change Data type on DPTx port (TBTC, TBTD)
 @param tbtDataPort                ATDevicePortTBTC or ATDevicePortTBTD
 @param mode                   0 = TBT(single DP)
                                1 = DP Alt
                                2 = USB
                                3 = Multi Mode (DP+USB)
 @param disconnectTime         disconnect time in ms
 @param aError                 set if there is any error
 @return                        YES = Sucess or NO = Fail
 */
-(BOOL) changeDataModeOnTBTTxPort:(ATDeviceTBTTxPortType) tbtDataPort
                            toMode:(ATDeviceTBTTxPortModes) mode
          disconnectTimeInMilliSec: (uint16_t) disconnectTime
                          andError:(NSError **)aError;
/**
 check TBTC mode
 @return ATDeviceTBTTxPortModes:   mode index.
 */
- (ATDeviceTBTTxPortModes) dptx0ModeWithError:(NSError **)aError;
/**
 check TBTM mode
 @return ATDeviceTBTPortOnePlugModes:   mode index.
 */
- (ATDeviceTBTPortOnePlugModes) tbtModeWithError:(NSError **)aError;

// Supported Functions inheriated from Palladium
//
//
//- (ATDeviceDisplayPortLinkStatus*) displayPortLinkStatusWithError: (NSError**) aError;
//
//


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
                                                  andError: (NSError**) aError;



- (uint32_t) readDataFromFPGARegisterAt: (NSUInteger) address andError: (NSError**) aError;


/** writeFPGARegisterAt
 * brief write FPGA Register register
 *
 * param address           FPGA Register Address
 * param writeData         uint16_t data to write
 * param[out] aError nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval BOOL:             Command Sucess or Fail
 *
 */
- (BOOL)    writeDataToFPGARegisterAt: (NSUInteger) address withData:(uint32_t) writeData andError: (NSError**) aError;



- (ATDeviceColor32bitCRC*)  imageCRCWithNumberOfFrames: (uint16_t) numFrames
                                        expectedDP0Red: (uint32_t) expectedDP0Red
                                      expectedDP0Green: (uint32_t) expectedDP0Green
                                       expectedDP0Blue: (uint32_t) expectedDP0Blue
                                        expectedDP1Red: (uint32_t) expectedDP1Red
                                      expectedDP1Green: (uint32_t) expectedDP1Green
                                       expectedDP1Blue: (uint32_t) expectedDP1Blue
                                                 error: (NSError**) aError;


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
 @param[out] aError                nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
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
                                                    error: (NSError**) aError;



/** symbolErrorCountWithDurationInMilliSeconds
 * brief getting the symbol error counts for all lanes from the Test Device Rx Pot.
 *
 * param numFrames:           duration
 * param[out] aError: nil = NO error, or error set.
 * retval ATDeviceSymbolErrorCount:      the Struct of symbol error counts for all lanes
 *
 */
- (ATDeviceSymbolErrorCount *) symbolErrorCountWithDurationInMilliSeconds: (NSUInteger) duration
                                                                 andError: (NSError**) aError;

/**
 symbolErrorCountAt either TX or Rx, this function will read THEN clean symbol error count registers.
 
 @param aTxOrRx ATDDisplayPortTX or ATDDisplayPortRX
 @param aError nil = NO error, or error set.
 @return ATDeviceSymbolErrorCount
 */
- (ATDeviceSymbolErrorCount *) symbolErrorCountAt: (ATDDisplayPortTxRx) aTxOrRx
                                         andError: (NSError**) aError;

/**
 symbolErrorCountAt either TX or Rx

 @param aTxOrRx ATDDisplayPortTX or ATDDisplayPortRX
 @param duration    duration in milli seconds
 @param aError nil = NO error, or error set.
 @return ATDeviceSymbolErrorCount
 */
- (ATDeviceSymbolErrorCount *) symbolErrorCountAt: (ATDDisplayPortTxRx) aTxOrRx
                       WithDurationInMilliSeconds: (NSUInteger) duration
                                         andError: (NSError**) aError;

- (ATDeviceVideoStatus*) videoStatusForDPRx: (NSInteger) dpIndex
                                   andError: (NSError**) aError;



/*  reset a selected IC on Titanium.
ATDeviceTitaniumFPGA             = 0,
ATDeviceTitaniumTitanRidge       = 1,
ATDeviceTitaniumAceTBTA          = 2,
ATDeviceTitaniumAceTBTB          = 3,
ATDeviceTitaniumAceDPRX1         = 4,
ATDeviceTitaniumAceDPRX0         = 5,
ATDeviceTitaniumAceDPTX1         = 6,
ATDeviceTitaniumPLL              = 7,
ATDeviceTitaniumUSBHub           = 8,
ATDeviceTitaniumW5500            = 9,
ATDeviceTitaniumToslink          = 10,
ATDeviceTitaniumForceAceTR       = 11,

return value
      BOOL:   YES = successed with no Error.
              NO  = Error occured;
 */
- (BOOL) resetSelectedIC: (ATDeviceTitaniumSelectedIC) selectedIC  withError:(NSError**) aError;

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
                     andError:(NSError *__autoreleasing *)aError;


/**
 enable/disable USBA Port Power
 
 @param isEnabled BOOL, YES or NO
 @param aError set if there is any error
 @return YES = Success or NO = Fail
 */
-(BOOL) usbAPortPower: (BOOL) isEnabled
             andError: (NSError**) aError;

/**
 Set downstream USB2 path to DPTX0 or DPTX1
 
 @param dpTxPort 0 = DPRX1, 1 = TBTA
 @param aError error is set if there was an error setting USB2 path
 @return yes if successfully set downstream USB2 path
 */
-(BOOL) downstreamUSB2DevicePathTo: (ATDeviceDPTxPortType) dpTxPort
                 andError: (NSError**) aError;


/**
 Set upstream USB2 path to TBTA or DPRX1
 
 @param usb2HostPort 0 = DPRX1, 1 = TBTA
 @param saved 0 = not saved, 1 = saved setting to EEpprom
 @param aError error is set if there was an error setting USB2 path
 @return yes if successfully set upstream USB2 path
 */
-(BOOL) upstreamUSB2HostPathTo: (ATDeviceUSB2HostPortType) usb2HostPort
             andSaveEEpprom: (BOOL)saved
               andError: (NSError**) aError;

/**
 Increment cable count for attached neuton cable. Titanium needs to be vconn src to do this
 
 @param port This port is based on @sa ATDeviceTitaniumPortType
 @param aError error if increementing count didnt work
 @return Yes if cable count was increemented
 */
-(BOOL) neutronIncrementCycleCountForPort:(ATDeviceTitaniumPortType) port
                                 andError:(NSError**) aError;

/**
 Get cable count for attached neuton cable. Titanium needs to be vconn src to do this
 
 @param port his port is based on @sa ATDeviceTitaniumPortType
 @param aError error if getting count didnt work
 @return return cycle count
 */
-(NSInteger) neutronCycleCountForPort:(ATDeviceTitaniumPortType) port
                        andError:(NSError**) aError;

/**
 hdcpControlOnPort

 @param port            ATDeviceHPCD_DPRxPort0 = 0, ATDeviceHPCD_DPRxPort1 = 1, ATDeviceHPCD_HDMIPort = 2,
 @param enableHDCP1     enable HDCP 1
 @param enableHDCP2     enable HDCP 2
 @param aError          error is set if there was an error
 @return                yes if successfully set upstream USB2 path
 */
- (BOOL) hdcpControlOnPort: (ATDeviceHPCDDPRxPortType) port
            andEnableHDCP1: (BOOL) enableHDCP1
            andEnableHDCP2: (BOOL) enableHDCP2
                  andError:(NSError**) aError;

/**
 hdcpControlOnInternalVideoPort is super set of hdcpControlOnPort.
 
 @param anInternalVideoPort
 @param ATDeviceInternalVideoPort
 @param enableHDCP1     enable HDCP 1
 @param enableHDCP2     enable HDCP 2
 @param aError          error is set if there was an error
 @return                yes if successfully set upstream USB2 path
 */
- (BOOL) hdcpControlOnInternalVideoPort: (ATDeviceInternalVideoPort) anInternalVideoPort
                         andEnableHDCP1: (BOOL) enableHDCP1
                         andEnableHDCP2: (BOOL) enableHDCP2
                               andError:(NSError**) aError;

/**
 Update default contract current for all ports
 
 @param milliAmp   default current(mA) will be set
 @param aError     when there is an error, this will be set
 @return           BOOL:    YES = successed with no Error.
                            NO  = Error occured;
 */
- (BOOL) setUSBCDefaultCurrentInMilliAmp: (NSInteger) milliAmp
                                andError: (NSError **) aError;

/**
 check HDCP status on Display Ports
 
 @param anInternalVideoPort:
 ATDeviceDisplayPortRx0 = 0x10,
 ATDeviceDisplayPortRx1,
 ATDeviceDisplayPortHDMIRx,
 ATDeviceDisplayPortHDMITx,
 ATDeviceDisplayPortTx0,
 ATDeviceDisplayPortTx1
 @param aError when there is an error, this will be set
 @return return HDCP authentication status
 */
- (ATDeviceHDCPStatus*) hdcpStatusOnInternalVideoPort:(ATDeviceInternalVideoPort)anInternalVideoPort
                                             andError:(NSError**)aError;

/**
 clear dock channel FIFO buffer
 
 @param aError error is set if there was an error
 @return yes if successfully clear fifo buffer
 */
- (BOOL) clearDockChannelFIFOWithError: (NSError **) aError;


@end
