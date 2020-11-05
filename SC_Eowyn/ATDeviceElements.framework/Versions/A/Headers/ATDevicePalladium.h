//
//  ATDevicePalladium.h
//  ATDeviceElements
//
//  Created by Sai  on 3/15/17.
//  Copyright © 2017 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ATDeviceElements/ATDeviceUSBC.h>
#import <ATDeviceElements/ATDeviceParameters.h>




typedef NS_ENUM(uint32_t, ATDCableSOPType) {
    ATDCableSOPPrime                = 1,
    ATDCableSOPPrimePrime           = 2,
   
    
};

@interface ATDevicePalladium : ATDeviceUSBC

// Get the RG & BG CRC Values on incoming HDMI Streams on A1 and A2 for specified frames
//
// return value
// ATDeviceDisplayPortLinkStatus:
//           BOOL      statusPassed;
//           NSInteger cedarP0laneCount;
//           NSInteger cedarP0linkBandwidthGbps;
//           NSInteger cedarP0status;
//           NSInteger cedarP1laneCount;
//           NSInteger cedarP1linkBandwidthGbps;
//           NSInteger cedarP1status;
//           NSData * rawData; Data from back from the Palladium. They match what in the User Manual
- (ATDeviceDisplayPortLinkStatus*) displayPortLinkStatusWithError: (NSError**) aError;

// return value
// ATDeviceDisplayPortSymbolErrorCount:
//      NSInteger totalErrorCount;
//      NSInteger cedarP0ErrorCount;
//      NSInteger cedarP1ErrorCount;
//      NSInteger cedarP0Lane0ErrorCount;
//      NSInteger cedarP0Lane1ErrorCount;
//      NSInteger cedarP0Lane2ErrorCount;
//      NSInteger cedarP0Lane3ErrorCount;
//      NSInteger cedarP1Lane0ErrorCount;
//      NSInteger cedarP1Lane1ErrorCount;
//      NSInteger cedarP1Lane2ErrorCount;
//      NSInteger cedarP1Lane3ErrorCount;
- (ATDeviceDisplayPortSymbolErrorCount*) displayPortSymbolErrorCountWithDurationInMilliSeconds: (NSUInteger) duration
                                                                                      andError: (NSError**) aError;

/** symbolErrorCountWithDurationInMilliSeconds
 * brief getting the symbol error counts for all lanes from the Test Device. This function is the same as displayPortSymbolErrorCountWithDurationInMilliSeconds .
 *
 * param numFrames:           duration
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval ATDeviceSymbolErrorCount:      the Struct of symbol error counts for all lanes
 *
 */
- (ATDeviceSymbolErrorCount *) symbolErrorCountWithDurationInMilliSeconds: (NSUInteger) duration
                                                                 andError: (NSError**) aError;


- (ATDeviceColorCRC*) displayPortSymbolCRCWithNumberOfFrames: (uint16_t) numFrames
                                          expectedCedarP0Red: (uint16_t) expectedCedarP0Red
                                        expectedCedarP0Green: (uint16_t) expectedCedarP0Green
                                         expectedCedarP0Blue: (uint16_t) expectedCedarP0Blue
                                          expectedCedarP1Red: (uint16_t) expectedCedarP1Red
                                        expectedCedarP1Green: (uint16_t) expectedCedarP1Green
                                         expectedCedarP1Blue: (uint16_t) expectedCedarP1Blue
                                                       error: (NSError**) aError;
/** imageCRCWithNumberOfFrames
 * brief getting the CRC from the Test Device. This function is the same as displayPortSymbolCRCWithNumberOfFrames.
 *
 * param numFrames:           Number frames to capture
 * param expectedDP0Red:         expected DPRX0 Red
 * param expectedDP0Green:       expected DPRX0 Green
 * param expectedDP0Blue:        expected DPRX0 Blue
 * param expectedDP1Red:         expected DPRX1 Red
 * param expectedDP1Green:       expected DPRX1 Green
 * param expectedDP1Blue:        expected DPRX1 Blue
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval ATDeviceColor32bitCRC:      the Struct of the CRC.
 *
 */
- (ATDeviceColor32bitCRC*)  imageCRCWithNumberOfFrames: (uint16_t) numFrames
                                        expectedDP0Red: (uint32_t) expectedDP0Red
                                      expectedDP0Green: (uint32_t) expectedDP0Green
                                       expectedDP0Blue: (uint32_t) expectedDP0Blue
                                        expectedDP1Red: (uint32_t) expectedDP1Red
                                      expectedDP1Green: (uint32_t) expectedDP1Green
                                       expectedDP1Blue: (uint32_t) expectedDP1Blue
                                                 error: (NSError**) aError;
// Only avaliable to Palladium
- (BOOL) palladiumVideoStatusForDP0: (ATDevicePalladiumVideoStatus**) dp0VideoStatus
                             forDP1: (ATDevicePalladiumVideoStatus**) dp1VideoStatus
                           andError: (NSError**) aError;

// SOP' Cable
// Palladium or Titanium must be configured as DFP

/**
 cableIdentityForPort

 @param portIndex  1 = TBT Port A,  2 = Ridge DPSNK1, 3 = Cedar DPRX, 4 = TBT Port B;
 @param aError nil = NO error, or error set.
 @return    NSData is the data coming from Register 100
 */
- (NSData*) cableIdentityForPort:(NSUInteger) portIndex
                    andError: (NSError **)  aError;

/**
 cableSVIDsForPort
 
 @param portIndex  1 = TBT Port A,  2 = Ridge DPSNK1, 3 = Cedar DPRX, 4 = TBT Port B;
 @param aError nil = NO error, or error set.
 @return    NSData is the data coming from Register 101  uint16_t svid1 = (data[1] << 8) | data[0];   uint16_t svid2 = (data[3] << 8) | data[2];
 */
- (NSData*) cableSVIDsForPort:(NSUInteger) portIndex
                        andError: (NSError **)  aError;

/**
 cableModeForPort
 
 @param portIndex  1 = TBT Port A,  2 = Ridge DPSNK1, 3 = Cedar DPRX, 4 = TBT Port B;
 @param aError nil = NO error, or error set.
 @return    NSData is the data coming from Register 102
 */
- (NSData*) cableModeForPort:(NSUInteger) portIndex
                    andError: (NSError **)  aError;


/**
 cableSerialNumberForPort
 
 @param portIndex  1 = TBT Port A,  2 = Ridge DPSNK1, 3 = Cedar DPRX, 4 = TBT Port B;
 @param sopType SOP' or SOP''
 @param aError nil = NO error, or error set.
 @return    NSData is the data contains the Serial Info
 */
- (NSData*) cableSerialNumberForPort:(NSUInteger) portIndex
                     andCableSOPType:(ATDCableSOPType) sopType
                            andError: (NSError **)  aError;


@end
