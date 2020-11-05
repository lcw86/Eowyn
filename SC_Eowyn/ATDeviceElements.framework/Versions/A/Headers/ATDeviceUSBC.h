//
//  ATDeviceUSBC.h
//  ATDeviceElements
//
//  Created by Sai  on 3/23/17.
//  Copyright © 2017 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceElement.h>
#import <ATDeviceElements/ATDevicePDControllerParameter.h>
#import <ATDeviceElements/ATDPDControllerProtocols.h>
#import <ATDeviceElements/ATDPDControllerRegisters.h>

typedef NS_ENUM(uint8_t, ATDeviceOrientation) {
    ATDOrientationCC1 = 0,
    ATDOrientationCC2,
    ATDOrientationNeither,
    ATDOrientationBoth,
};

typedef NS_ENUM(uint8_t, ATDeviceCCConfigType) {
    ATD_CCType_NoAction = 0,
    ATD_CCType_NoConnection,
    ATD_CCType_MakeConnection,
    ATD_CCType_Reserved,
};




@interface ATDeviceUSBC : ATDeviceElement <ATDPDControlCapable>

//
// measureVConnPowerOnPort
// param
//      portIndex   port index to measure. 1 base.
//      miliVolt    measurement  voltage result  in mili voltage.
//      miliAmp     measurement  Amp result  in mili amp.
//      isSource    TRUE means port is sourcing current. NO means port is sinking current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;

-(BOOL) measureVConnPowerOnPort: (NSUInteger)     portIndex
              andMiliVoltResult: (uint32_t*)      miliVolt
               andMiliAmpResult: (uint32_t*)      miliAmp
                    andIsSource: (BOOL*)          isSource
                       andError: (NSError **)     aError;

//
// measureVBusPowerOnPort
// param
//      portIndex   port index to measure. 1 base.
//      miliVolt    measurement  voltage result  in mili voltage.
//      miliAmp     measurement  Amp result  in mili amp.
//      isSource    TRUE means port is sourcing current. NO means port is sinking current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;

-(BOOL) measureVBusPowerOnPort: (NSUInteger)    portIndex
             andMiliVoltResult: (uint32_t*)     miliVolt
              andMiliAmpResult: (uint32_t*)     miliAmp
                   andIsSource: (BOOL*)         isSource
                      andError: (NSError **)    aError;






// configureDeviceAsVBusSinkOnPort
// This function will make sure device has a Galluim connected and configure it to sink current at requested voltage and currrent.
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) configureDeviceAsVBusSinkOnPort: (NSUInteger) portIndex
                           andMilliVolt: (NSUInteger) milliVolt
                            andMilliAmp: (NSUInteger) milliAmp
                               andError: (NSError **) aError;



/**
     configureVBusSinkCurrentWithOutNegotiatePowerContractOnPort.
     Set Gallium's Vbus Sink Current without Negotiating Power Contract. You can use it to do overcurrent test.

 @param portIndex Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
 @param milliAmp Target Milli Current
 @param aError when there is an error, this will be set
 @return YES = successed with no Error.
 */
-(BOOL) configureVBusSinkCurrentWithOutNegotiatePowerContractOnPort: (NSUInteger) portIndex
                                                        andMilliAmp: (NSUInteger) milliAmp
                                                           andError: (NSError **) aError;

// clearVBusSinkOnPort
// this fucntion will turn off the VBus Sink (Load)
// param
//      portIndex    Port ID to apply the change,Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) clearVBusSinkOnPort: (NSUInteger) portIndex
                     andError: (NSError **) aError;
/**
 configureDeviceAsVBusSourceOnPort
 
 @param portIndex Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
 @param milliVolt Target Milli Voltage
 @param milliAmp Target Milli Current
 @param delay delay before negotiating a contract
 @param aError when there is an error, this will be set
 @return YES = successed with no Error.
 NO  = Error occured
 */
-(BOOL) configureDeviceAsVBusSourceOnPort: (NSUInteger) portIndex
                             andMilliVolt: (NSUInteger) milliVolt
                              andMilliAmp: (NSUInteger) milliAmp
                  andDelayBeforeNegotiate: (NSTimeInterval) delay
                                 andError: (NSError **) aError;


/**
 updateVBusSourceVoltageOnPort  Update Gallium VBus Source Voltage level. No contact Updated.
 
 @param portIndex  Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
 @param milliVolt Target Milli Voltage
 @param aError when there is an error, this will be set
 @return YES = successed with no Error.
 */
- (BOOL) updateVBusSourceVoltageOnPort: (NSUInteger) portIndex
                          andMilliVolt: (NSUInteger) milliVolt
                              andError: (NSError **) aError;

// configureDeviceAsVBusSourceOnPort
// This function will make sure device has a Galluim connected and configure it to source current at requested voltage and currrent.
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) configureDeviceAsVBusSourceOnPort: (NSUInteger) portIndex
                             andMilliVolt: (NSUInteger) milliVolt
                              andMilliAmp: (NSUInteger) milliAmp
                                 andError: (NSError **) aError;


// configureDeviceAsVConnSinkOnPort
// This function will make sure device has a Galluim connected and configure it to sink current at requested currrent.
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) configureDeviceAsVConnSinkOnPort: (NSUInteger) portIndex
                             andMilliAmp: (NSUInteger) milliAmp
                                andError: (NSError **) aError;


/**
 configureDeviceAsVConnSourceOnAllPortsToMilliVolt

 @param milliVolt Target millivolt. It can be 0v, 2000mV to 5500 mV.
 @param aError  when there is an error, this will be set
 @return YES = successed with no Error and NO = Error occured.
 */
-(BOOL) configureDeviceAsVConnSourceOnAllPortsToMilliVolt: (NSUInteger) milliVolt
                                                   andError: (NSError **) aError;

-(BOOL)  lastVBusLoadRequestedOnPort: (NSUInteger) portIndex
                         andMilliAmp: (uint32_t *) milliAmp
                            andError: (out NSError **)aError;

-(BOOL) swapVConnToSourceOnPort:(NSUInteger) portIndex WithError: (out NSError **) aError;
/**
 vconnSwapOnPort Attempt a VConn swap on a selected port.

 @param portIndex Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
 @param aError  when there is an error, this will be set
 @return YES = successed and NO = failed
 */
-(BOOL) vconnSwapOnPort: (NSUInteger) portIndex
               andError: (NSError **) aError;

-(BOOL) clearVConnSourceOnAllPortsWithError: (NSError **) aError;

// clearVConnSinkOnPort
// this fucntion will turn off the VConn Sink (Load)
// param
//      portIndex    Port ID to apply the change,Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) clearVConnSinkOnPort: (NSUInteger) portIndex
                      andError: (NSError **) aError;


// isGalliumConnected
// this fucntion will check if Gallium is connected or not.
// param
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = connected.
//              NO  = not connnected or Error occured
-(BOOL) isGalliumConnected: (NSError **) aError;

//  portStatusOnPort
//  param
//       portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//       ccConnected            CC Connection State 0 - Disconnected, 1 - Connected
//       andIsSource            0 - Sink. Port is presenting Rd, 1 - Source. Port is presenting Rp
//       andIsDownFacingPort    Port Data Role.  Only valid if Bit 0 is 1.   0 - UFP 1 - DFP
//       andIsCC2Up             Orientation.  Only valid if Bit 0 is 1.  0 - CC1 (top-up),  1 - CC2 (bottom-up)
//       numOfPorts             Number of Ports of the device
//       dataProtocolUsed        Current data protocol.
//                              0 - USB
//                              1 - DisplayPort
//                              2 - Thunderbolt
//                              3 - Reserved
-(BOOL)     portStatusOnPort: (NSUInteger) portIndex
              andCCConnected: (BOOL*) ccConnected
                 andIsSource: (BOOL*) isSource
         andIsDownFacingPort: (BOOL*) isDownFacingPort
                  andIsCC2Up: (BOOL*) isCC2Up
         andDataProtocolUsed: (uint8_t*) dataProtocolUsed
               andNumOfPorts: (NSUInteger*) numOfPorts
                    andError: (NSError **) aError;

/**
 Port status on given port

 @param portIndex Port ID to apply the change, Xenon 2 ports: 1 or 2. Caesium 1, Palladium 4 ports: 1,2,3,and 4. Titanium 5 ports - 1,2,3,4 and 5.
 
 @param ccConnected CC Connection State 0 - Disconnected, 1 - Connected
 @param isSource 0 - Sink. Port is presenting Rd, 1 - Source. Port is presenting Rp
 @param isDownFacingPort Port Data Role.  Only valid if Bit 0 is 1.   0 - UFP 1 - DFP
 @param isCC2Up Orientation.  Only valid if Bit 0 is 1.  0 - CC1 (top-up),  1 - CC2 (bottom-up)
 @param dataProtocolUsed Current data protocol.
 //                              0 - USB
 //                              1 - DisplayPort
 //                              2 - Thunderbolt
 //                              3 - Reserved
 @param numOfPorts Number of Ports of the device
 @param isVCONNSource nly valid if Bit 0 is 1. 1 - vconn src, 0 - vconn sink
 @param aError set if error retrieving port status
 @return YES or NO depending on result
 */
-(BOOL)     portStatusOnPort: (NSUInteger) portIndex
              andCCConnected: (out BOOL*) ccConnected
                 andIsSource: (out BOOL*) isSource
         andIsDownFacingPort: (out BOOL*) isDownFacingPort
                  andIsCC2Up: (out BOOL*) isCC2Up
         andDataProtocolUsed: (out uint8_t*) dataProtocolUsed
               andNumOfPorts: (out NSUInteger*) numOfPorts
            andIsVCONNSource: (out BOOL *) isVCONNSource
                    andError: (out NSError **) aError;
//  swapPowerRoleToSourceOnPort
//  param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
- (BOOL) swapPowerRoleToSourceOnPort: (NSUInteger) portIndex
                            andError: (NSError **) aError;
//  swapPowerRoleToSinkOnPort
//  param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
- (BOOL) swapPowerRoleToSinkOnPort: (NSUInteger) portIndex
                          andError: (NSError **) aError;

- (BOOL) setVBusSinkOnPort: (NSUInteger) portIndex
             andMilliAmps: (NSUInteger) milliAmp
                 andError: (NSError **) aError;

// updateSinkCapabilitiesOnPort
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) updateSinkCapabilitiesOnPort: (NSUInteger) portIndex
                        andMilliVolt: (NSUInteger) milliVolt
                         andMilliAmp: (NSUInteger) milliAmp
                            andError: (NSError **) aError;

// updateSinkCapabilitiesOnPort
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      maxVolt      Maximum Voltage. enable PDO_VARIABLE
//      aError      when there is an error, this will be set
// return value
//      BOOL:    YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) updateSinkCapabilitiesOnPort: (NSUInteger) portIndex
                        andMilliVolt: (NSUInteger) milliVolt
                         andMilliAmp: (NSUInteger) milliAmp
                          andMaxVolt: (NSUInteger) maxVolt
                            andError: (NSError **) aError;
// updateSourceCapabilitiesOnPort
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) updateSourceCapabilitiesOnPort: (NSUInteger) portIndex
                          andMilliVolt: (NSUInteger) milliVolt
                           andMilliAmp: (NSUInteger) milliAmp
                              andError: (NSError **) aError;

// updateSourceCapabilitiesOnPort
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      maxVolt     Maximum Voltage.   enable PDO_VARIABLE
//      aError      when there is an error, this will be set
// return value
//      BOOL:    YES = successed with no Error.
//              NO  = Error occured;
-(BOOL) updateSourceCapabilitiesOnPort: (NSUInteger) portIndex
                          andMilliVolt: (NSUInteger) milliVolt
                           andMilliAmp: (NSUInteger) milliAmp
                            andMaxVolt: (NSUInteger) maxVolt
                              andError: (NSError **) aError;
// negotiatePowerContractOnPort
// param
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    Target Milli Voltage
//      milliAmp     Target Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
- (BOOL) negotiatePowerContractOnPort: (NSUInteger) portIndex
                         andMilliVolt: (NSUInteger) milliVolt
                          andMilliAmp: (NSUInteger) milliAmp
                            andAsSink: (BOOL)       asSink
                             andError: (NSError **) aError;

// negotiatedContractOnPort
// get the current negotiated power contract on port
//      portIndex    Port ID to apply the change, Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      milliVolt    negotiated Milli Voltage
//      milliAmp     negotiated Milli Current
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;
- (BOOL)    negotiatedContractOnPort: (NSUInteger) portIndex
              andNegotiatedMilliVolt: (NSUInteger*) milliVolt
               andNegotiatedMilliAmp: (NSUInteger*) milliAmp
                            andError: (NSError **) aError;

// setCCOrientationOnPort
// param
//      portIndex       port index to change orientation. Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      orientation     The Orientation to:
//                      ATDOrientationCC1
//                      ATDOrientationCC2,
//                      ATDOrientationNeither, Both disconnected
//                      ATDOrientationBoth,    Both connected
//      presentRa       When it's not connected, connect the pin to Ra Pull Down resistor?
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;

-(BOOL) setCCOrientationOnPort: (NSUInteger) portIndex
                andOrientation: (ATDeviceOrientation) orientation
                  andPresentRa: (BOOL) presentRa
                      andError: (NSError **)  aError;
// flipOrientationOnPort
//   Flip the current Orientation to another. Reconnect delay is 0.5 second. If CC1 is active, CC2 will be active and CC1 will be off
//   If both CC1 and CC2 are active, error will return.
//   If neither CC1 and CC2 are active, error will return.
//    Ra will be preserved during fliping.
// param
//      portIndex       port index to change orientation. Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      aError      when there is an error, this will be set
// return value
//      BOOL:	YES = successed with no Error.
//              NO  = Error occured;

-(BOOL) flipOrientationOnPort: (NSUInteger) portIndex
                      andError: (NSError **)  aError;

-(BOOL) flipOrientationOnPort: (NSUInteger) portIndex
    andReconnectDelayInSecond: (NSTimeInterval) delayInSec
                     andError: (NSError **)  aError;
//ccConfigOnPort
// Read the CDTI register CCConfiguratino at 0x48
//param
//      portIndex       port index to change orientation. Xenon 2 ports: 1 or 2. Palladium 4 ports: 1,2,3,and 4.
//      aError      when there is an error, this will be set
// return value
//      uint8_t:	the value of the register

-(uint8_t) ccConfigOnPort: (NSUInteger) portIndex
                          andError: (NSError **)  aError;

- (ATDeviceDisplayEyeTestLaneResult *) runEyeTestForType:(ATDEyeType) eyeType
                                               andCycles:(NSUInteger) cycles
                                           andTotalLanes:(NSUInteger) totalLanes
                                                andError:(NSError **)error;





/**
 aceShortDetectionStatusWithError:
    Read Ace short detection register value from ACE_Status 0x1A. Corresponding 4cc command is SHRT.
    Data is stored from LSB:
        Ace1 short status is at: 0x1,
        Ace2 short status is at: 0x2,
        Ace3 short status is at: 0x4,
        ...
 @param aError return error from test device.
 @return return ATDeviceAceShortStatus object
 */
-(ATDeviceAceShortStatus*) aceShortDetectionStatusWithError:(NSError **) aError;

@property (nonatomic) NSUInteger numberOfPorts;



/**
 Read 4 ports(TBTA,TBTB,TBTC,TBTD) link status.

 @param aError when there is an error, this will be set
 @return return ATDevicePortsLinkStatus object as following:
 ATDeviceDataRate:
                0: Data rate is 20Gbps;
                1: Data rate is 10Gbps;
                2: Data rate is 5Gbps;
                3: Data rate is reserved;
 ATDeviceDataMode:
                0: Data mode is Disconnected;
                0x1: Data mode is CIO;
                0x2: Data mode is DP;
                0x8: Data mode is USB3;
                0x10: Data mode is Multi Function DP;
 Lane0 link:
           The value is 0 or 1;
 
 Lane1 link:
           The value is 0 or 1;
 */
-(ATDevicePortsLinkStatus*) portslinkStatusWithError: (NSError **) aError;


/**
 readPDControllerRegisterOnPort

 @param aPortIndex  Port
 @param aPDControllerRegister  Ace Register Offset
 @param aData    Data array.
 @param aReadLength   number of Byte to read
 @param aError   Error description
 @return YES = successed 
 */
-(BOOL) readPDControllerRegisterOnPort:(NSUInteger)aPortIndex
                     andRegisterOffset:(ATDPDControllerRegisterOffset)aPDControllerRegister
                               andData:(uint8_t*)aData
                     andReadDataLength:(uint8_t)aReadLength
                              andError:(NSError **)aError;

/**
 writePDControllerRegisterOnPort
 Modifying Ace can cause damages to your TextBoxes
 
 @param aPortIndex Port
 @param aPDControllerRegister  Ace Register Offset
 @param aData Data array.
 @param aWriteLength number of Byte to write
 @param aError Error description
 @return YES = successed
 */
-(BOOL) writePDControllerRegisterOnPort:(NSUInteger)aPortIndex
                      andRegisterOffset:(ATDPDControllerRegisterOffset)aPDControllerRegister
                                andData:(uint8_t*)aData
                     andWriteDataLength:(uint8_t)aWriteLength
                               andError:(NSError **)aError;

@end

