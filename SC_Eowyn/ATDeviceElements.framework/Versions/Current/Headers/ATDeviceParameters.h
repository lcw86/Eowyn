//
//  ATDeviceParameters.h
//  ATDeviceElements
//
//  Created by Sai  on 9/6/16.
//  Copyright © 2016 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATDeviceVideoParameterStructs.h"
#import "ATDeviceCarbonConnectorChecker.h"

#define SET_BIT_FIELD(value,len,pos) ((value & ((1 << len) - 1)) << pos)

typedef NS_ENUM(uint8_t,ATDeviceMantisLoadWarning) {
    ATDeviceMantisLoadWarningNoWarning = 0,
    ATDeviceMantisLoadWarningRunAwayReturnToFirstTryValue = 1,
    ATDeviceMantisLoadWarningConvergeCheckINA = 2
};
typedef NS_ENUM(uint8_t, ATDCarbonEuropeanPinConfigType) {

    ATDCarbonDontConfigure = 0,
    GPIO_Mode_IN_25MHz_PP_NoPull, //1
    GPIO_Mode_IN_50MHz_PP_NoPull,  //2
    GPIO_Mode_IN_25MHz_PP_PullDown, //3 default
    GPIO_Mode_IN_50MHz_PP_PullDown,  //4
    GPIO_Mode_IN_25MHz_PP_PullUp,   // 5 default
    GPIO_Mode_IN_50MHz_PP_PullUp,   //6
    
    GPIO_Mode_OUT_25MHz_PP_NoPull_Init0, //7
    GPIO_Mode_OUT_25MHz_PP_NoPull_Init1,  //8
    GPIO_Mode_OUT_25MHz_PP_PullDown_Init0, //9
    GPIO_Mode_OUT_25MHz_PP_PullUp_Init1,   //10
    
    GPIO_Mode_OUT_50MHz_PP_NoPull_Init0,//11
    GPIO_Mode_OUT_50MHz_PP_NoPull_Init1,//12
    GPIO_Mode_OUT_50MHz_PP_PullDown_Init0,//13
    GPIO_Mode_OUT_50MHz_PP_PullUp_Init1,//14
    
    GPIO_Mode_OUT_100MHz_PP_NoPull_Init0,//15
    GPIO_Mode_OUT_100MHz_PP_NoPull_Init1,//16
    GPIO_Mode_OUT_100MHz_PP_PullDown_Init0,//17
    GPIO_Mode_OUT_100MHz_PP_PullUp_Init1,//18
    
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_USART1,  //19 //GPIO_AF_USART1
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_USART2,  //20
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_USART3,   //21
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_UART4,   //22
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_UART5,   //23
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_USART6,  //24
    
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_SPI2,  //25
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_SPI3,   //26
    
    GPIO_Mode_AF_OD_NoPull_GPIO_AF_I2C1,  //27
    GPIO_Mode_AF_OD_NoPull_GPIO_AF_I2C2,   //28
    
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_CAN1,  //29
    GPIO_Mode_AF_PP_NoPull_GPIO_AF_CAN2,  //30
    
    GPIO_Mode_AN_AnalogIO,  //31
    
    GPIO_Mode_OUT_25MHz_OD_NoPull, //32 Open drain
    
    ATDCarbonNumOfPortConfigType,
};


typedef NS_ENUM(uint8_t, ATDDisplayPortTxRx){
    
    ATDDisplayPortTX = 0,
    ATDDisplayPortRx
    
};

typedef NS_ENUM(uint8_t, ATDGpioState) {
    ATDIzzyGpio_Low = 0,
    ATDIzzyGpio_High = 1,
    ATDIzzyGpio_HighZ = 2,
};

typedef NS_ENUM(uint32_t, ATDeviceUSBSpeed) {
    ATDeviceUSBLowSpeed   = 0,
    ATDeviceUSBFullSpeed  ,
    ATDeviceUSBHighSpeed  ,
    ATDeviceUSBSuperSpeed ,
    ATDeviceUSBDisconnect ,
};

typedef NS_ENUM(uint32_t, ATDeviceMantisUSBSpeed) {
    ATDeviceMantisUSBLowSpeed   = 0,
    ATDeviceMantisUSBFullSpeed  ,
    ATDeviceMantisUSBHighSpeed  ,
    ATDeviceMantisUSBSuperSpeed ,
    ATDeviceMantisUSBEyeSpeed   ,
    ATDeviceMantisUSBDisconnect = 0xFF
    
};




typedef NS_ENUM(uint8_t, ATDeviceUSBSelectedIC) {
    ATDeviceUSBFX3            = 0,
    ATDeviceUSBLegacyAce      ,
    ATDeviceUSBSSPlusAceAR    ,
    ATDeviceUSBASMedia        ,
    ATDeviceUSBW5500          ,
    ATDeviceUSBLPC11
};


typedef NS_ENUM(uint32_t, ATDeviceCaesiumSpeed) {
    ATDeviceCaesiumLowSpeed         = 0,
    ATDeviceCaesiumFullSpeed        = 1,
    ATDeviceCaesiumHighSpeed        = 2,
    ATDeviceCaesiumSuperSpeed       = 3,
    ATDeviceCaesiumSuperSpeedPlus   = 4,
    ATDeviceCaesiumDisconnect       = 0xFF
};


typedef NS_ENUM(uint8_t, ATDeviceCaesiumSelectedIC) {
    ATDeviceCaesiumFX3          = 0,
    ATDeviceCaesiumASMedia      = 1,
    ATDeviceCaesiumLSController = 2,
    ATDeviceCaesiumAce          = 3,
    ATDeviceCaesiumW5500        = 4,
    ATDeviceCaesiumSATA         = 5,
};

typedef NS_ENUM(uint8_t, ATDeviceTitaniumSelectedIC) {
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
};

typedef NS_ENUM(uint8_t, ATDeviceBananaUSBState) {
    ATDeviceBananaUnconnected   = 0,
    ATDeviceBananaDefault       = 1,
    ATDeviceBananaAddressed     = 2,
    ATDeviceBananaConfigured    = 3,
    ATDeviceBananaSuspended     = 4,
};

typedef NS_ENUM(uint8_t, ATDeviceModifierKeys) {
    ATDeviceModifierKeyLeftControl  = 1,
    ATDeviceModifierKeyLeftShift    = 2,
    ATDeviceModifierKeyLeftOption   = 4,
    ATDeviceModifierKeyLeftCommand  = 8,
    ATDeviceModifierKeyRightControl = 16,
    ATDeviceModifierKeyRightShift   = 32,
    ATDeviceModifierKeyRightOption  = 64,
    ATDeviceModifierKeyRightCommand = 128,
};

typedef NS_ENUM(uint8_t, ATDeviceSpecialKeys) {
    ATDeviceSpecialKeyPlayPause     = 1,
    ATDeviceSpecialKeyNextTrack     = 2,
    ATDeviceSpecialKeyPrevTrack     = 4,
    ATDeviceSpecialKeyEject         = 8,
    ATDeviceSpecialKeyMute          = 16,
    ATDeviceSpecialKeyVolumeDown    = 32,
    ATDeviceSpecialKeyVolumeUp      = 64,
};

typedef NS_ENUM(uint32_t, ATDeviceHDMIColorModes) {
    ATDeviceHDMIColorModeRGB        = 0,
    ATDeviceHDMIColorModeYCbCr422  = 0x800,
    ATDeviceHDMIColorModeYCbCr444  = 0x1000,
    ATDeviceHDMIColorModeYCbCr440  = 0x1800
};
typedef NS_ENUM(uint32_t, ATDeviceHDMIColorDepth) {
    ATDeviceHDMIColorDepth24bpp  = 0x40000,
    ATDeviceHDMIColorDepth30bpp  = 0x50000,
    ATDeviceHDMIColorDepth36bpp  = 0x60000,
    ATDeviceHDMIColorDepth48bpp  = 0x70000
};

typedef NS_ENUM(uint32_t, ATDeviceHDMIVideoMode) {
    ATDeviceHDMIVideoModeDVI        = 0,
    ATDeviceHDMIVideoModeHDMI       = 0x0400
};
typedef NS_ENUM(uint32_t, ATDeviceHDMISpecMode) {
    ATDeviceHDMISpecMode14        = 0,
    ATDeviceHDMISpecMode20        = 0x40
};

typedef NS_ENUM(uint32_t, ATDeviceColors) {
    ATDeviceColor8bitBlack  = 0,
    ATDeviceColor8bitNavy   = 0x00000080,
    ATDeviceColor8bitBlue   = 0x000000FF,
    ATDeviceColor8bitGreen  = 0x00008000,
    ATDeviceColor8bitTeal   = 0x00008080,
    ATDeviceColor8bitLime   = 0x0000FF00,
    ATDeviceColor8bitAqua   = 0x0000FFFF,
    ATDeviceColor8bitMaroon = 0x00800000,
    ATDeviceColor8bitPurple = 0x00800080,
    ATDeviceColor8bitOlive  = 0x00808000,
    ATDeviceColor8bitGray   = 0x00808080,
    ATDeviceColor8bitSilver = 0x00C0C0C0,
    ATDeviceColor8bitRed    = 0x00FF0000,
    ATDeviceColor8bitFushsia= 0x00FF00FF,
    ATDeviceColor8bitYellow = 0x00FFFF00,
    ATDeviceColor8bitWhite  = 0x00FFFFFF,
    
};

typedef NS_ENUM(uint8_t,ATDeviceTitaniumPortType) {
    ATDeviceTitaniumPortTBTC = 1,
    ATDeviceTitaniumPortTBTA = 2,
    ATDeviceTitaniumPortTBTB = 3,
    ATDeviceTitaniumPortTBTD = 4,
    ATDeviceTitaniumPortDPRx1 = 5,
    ATDeviceTitaniumPortHDMIRx = 6
};

typedef NS_ENUM(uint8_t,ATDeviceTitanRidgeEyeType) {
    ATDeviceTitanRidgeEyeUnknown    = 0x00,
    
    ATDeviceTitanRidgeEyeDP         = 0x80,
    ATDeviceTitanRidgeEyeCIO        = 0x40,
    ATDeviceTitanRidgeEyeUSB        = 0x20,
    
    ATDeviceTitanRidgeEye20G        = 0x01,
    ATDeviceTitanRidgeEye10G        = 0x02,
    ATDeviceTitanRidgeEye5G         = 0x03,
    
    ATDeviceTitanRidgeEyeD8G        = 0x08,
    ATDeviceTitanRidgeEyeD5G        = 0x0C,
    
    ATDeviceTitanRidgeEyeCIO20G     = 0x41, // (EyeMonConnection_CIO | EyeMonConnection_20G)
    ATDeviceTitanRidgeEyeCIO10G     = 0x42, // (EyeMonConnection_CIO | EyeMonConnection_10G)
    
    ATDeviceTitanRidgeEyeUSB10G     = 0x22, // (EyeMonConnection_USB | EyeMonConnection_10G)
    ATDeviceTitanRidgeEyeUSB5G      = 0x23, // (EyeMonConnection_USB | EyeMonConnection_5G)
    
    ATDeviceTitanRidgeEyeDP8G       = 0x88, // (EyeMonConnection_DP | EyeMonConnection_D8G)
    ATDeviceTitanRidgeEyeDP5G       = 0x8C, // (EyeMonConnection_DP | EyeMonConnection_D5G)
    
    ATDeviceTitanRidgeEyeUSB10GDP8G = 0xAA, // (EyeMonConnection_USB | EyeMonConnection_10G | EyeMonConnection_DP | EyeMonConnection_D8G)
    ATDeviceTitanRidgeEyeUSB10GDP5G = 0xAE, // (EyeMonConnection_USB | EyeMonConnection_10G | EyeMonConnection_DP | EyeMonConnection_D5G)
    ATDeviceTitanRidgeEyeUSB5GDP8G  = 0xAB, // (EyeMonConnection_USB | EyeMonConnection_5G | EyeMonConnection_DP | EyeMonConnection_D8G)
    ATDeviceTitanRidgeEyeUSB5GDP5G  = 0xAF, // (EyeMonConnection_USB | EyeMonConnection_5G | EyeMonConnection_DP | EyeMonConnection_D5G)
};

typedef NS_ENUM(uint8_t,ATDeviceColorSpaceFormat) {
    ATDeviceColorSpaceRGB = 0,
    ATDeviceColorSpaceYCBCr444,
    ATDeviceColorSpaceYCBCr422,
    ATDeviceColorSpaceYCBCr420
    
};
typedef NS_ENUM(uint8_t,ATDeviceColorSpaceBPC) {
    
    ATDeviceColorSpace6BPC = 0,
    ATDeviceColorSpace8BPC,
    ATDeviceColorSpace10BPC,
    ATDeviceColorSpace12BPC,
    ATDeviceColorSpace16BPC
    
};
typedef NS_ENUM(uint8_t,ATDeviceColorSpaceRange) {
    ATDeviceColorSpaceVESA,
    ATDeviceColorSpaceCEA
};
typedef NS_ENUM(uint8_t,ATDeviceColorSpaceColorimetry) {
    ATDeviceColorSpaceBT601_5,
    ATDeviceColorSpaceBT709_5
};
typedef NS_ENUM(uint8_t,ATDeviceColorSpaceUseVscSDP) {
    
    ATDeviceColorSpaceUseMISC0,
    ATDeviceColorSpaceUseVSC_SDP
};

typedef NS_ENUM(uint8_t,ATDeviceArcType) {
    ATDeviceEARC = 0,
    ATDeviceARC = 1,
    ATDeviceARCMax
};

typedef NS_ENUM(uint8_t,ATDeviceArcI2SClockSpeed) {
    ATDeviceI2SClockSpeed192 = 0x00,
    ATDeviceI2SClockSpeed96 = 0x01,
    ATDeviceI2SClockSpeed48 = 0x02,
    ATDeviceI2SClockSpeed32 = 0x03,
    ATDeviceI2SClockMax
};

typedef NS_ENUM(uint8_t,ATDeviceArcTransmitSize) {
    
    ATDeviceArcTransmitterSize32 = 0x00,
    ATDeviceArcTransmitterSize16 = 0x04
};

typedef NS_ENUM(uint8_t,ATDeviceArcMuteState) {
    ArcUnmuted = 0,
    ArcMuted = 1
};

typedef struct{
    uint8 row, column;
} ATDEuroConnectorLocation;

typedef struct{
    ATDEuroConnectorLocation MOSI;
    ATDEuroConnectorLocation MISO;
    ATDEuroConnectorLocation SCK;
    ATDEuroConnectorLocation SS;
} ATDEuroConnectorSPILocation;

typedef struct{
    ATDEuroConnectorLocation SDA;
    ATDEuroConnectorLocation SCL;
} ATDEuroConnectorI2cLocation;

typedef NS_ENUM(int, ATDEyeType)
{
    ATDNativeDPEye      = 0,
    ATDTunneledDPEye       = 1,
    ATDUSBEye    = 2,
    
};
typedef NS_ENUM(int8_t, ATDChannelType)
{
    ATDRavenChannelA = 0,
    ATDRavenChannelB = 1,
    ATDRavenChannelAandB = 2,
};
typedef NS_ENUM(int8_t, ATDPolarityType)
{
    ATDPolarityPositive = 0,
    ATDPolarityNegative = 1
};
typedef NS_ENUM(uint8_t, ATDeviceGPIOPortName) {
    ATD_GPIO_A = 0,
    ATD_GPIO_B,
    ATD_GPIO_C,
    ATD_GPIO_D,
    ATD_GPIO_E,
    ATD_GPIO_F,
    ATD_GPIO_G,
    ATD_GPIO_H,
    ATD_GPIO_I,
};
@interface ATDVideoHDMICrc : NSObject

- (id) initWithRedGreenCRC: (NSNumber*) aRedGreenCRC
           andBlueGreenCRC: (NSNumber*) aBlueGreenCRC;

@property (nonatomic, strong) NSNumber* RedGreenCRC;
@property (nonatomic, strong) NSNumber* BlueGreenCRC;

@end

@interface ATDeviceRGBColorCRC : NSObject

- (id) initWithRedCRC: (NSInteger) aRedCRC
          andGreenCRC: (NSInteger) aGreenCRC
           andBlueCRC: (NSInteger) aBlueCRC;

@property (nonatomic) NSInteger redCRC;
@property (nonatomic) NSInteger greenCRC;
@property (nonatomic) NSInteger blueCRC;

@end

@interface ATDCarbonEuropeanConnectorPin : NSObject

//initWithRow
// Args:
//      Row can be 'A', 'B', or 'C'
//      pin can between 1 to 32.
//
// Return:
//  Invalid pin or Row will return nil.
//
- (id) initWithRow: (ATCarbonEuropeanConnectorRow) aRow andPin: (int) aPin andType: (ATDCarbonEuropeanPinConfigType) aType;

@property (nonatomic) unsigned int row; // 0 based . 0 = A, 1 = B, 2 = C
@property (nonatomic) unsigned int pin; // 1 based and total 32
@property (nonatomic) unsigned int index; // total 96
@property (nonatomic) ATDCarbonEuropeanPinConfigType type;

@end



@interface ATDCarbonEuropeanConnector : NSObject
// Args:
//      Row can be 'EuropeanPortRowA', 'EuropeanPortRowB', or 'EuropeanPortRowC'  Must be Upper case.
//      pin can between 1 to 32.
//      type is one of the ATDCarbonEuropeanPinConfigType
// Return:
//  Invalid pin or Row will return NO.
//
- (BOOL) addPinWithRow: (ATCarbonEuropeanConnectorRow) aRow andPin: (int) aPin andType: (ATDCarbonEuropeanPinConfigType) aType andError: (NSError**) aError;
//
- (BOOL) addPinWithRawData:(uint8_t*)rawData andError: (NSError**) aError ;

- (BOOL) isEqualToConnector: (ATDCarbonEuropeanConnector*) connector;
    // array of ATDCarbonEuropeanConnectorPin
@property (nonatomic, readonly) NSArray* pins;

@end

@interface ATDLogEntry : NSObject

@property (nonatomic) NSUInteger status;
@property (nonatomic) NSInteger entryIndex;
@property (nonatomic) NSUInteger upTime;
@property (nonatomic) NSUInteger lifeTime;
@property (nonatomic, copy) NSString* message; // decoded message if the test device support it

- (id) initWithStatus: (NSUInteger) aStatus
        andEntryIndex: (NSInteger)  aEntryIndex
            andUpTime: (NSUInteger) aUpTime
          andLifeTime: (NSUInteger) aLifeTime
           andMessage: (NSString *) aMessage;

@end



@interface ATDeviceDisplayPortLinkStatus : NSObject

//Overall Status PASSED or FAILED
@property (nonatomic) BOOL      statusPassed;
@property (nonatomic) NSInteger cedarP0laneCount;
@property (nonatomic) NSInteger cedarP0linkBandwidthGbps;  // This is actually Mbps e.g. 5400 or 8100
@property (nonatomic) NSInteger cedarP0status;
@property (nonatomic) NSInteger cedarP1laneCount;
@property (nonatomic) NSInteger cedarP1linkBandwidthGbps;  // This is actually Mbps e.g. 5400 or 8100
@property (nonatomic) NSInteger cedarP1status;

//The raw data coming back from test device. this matches the Palladium User manual.
@property (nonatomic,strong) NSData * rawData;

- (id) initWithStatusPassed: (BOOL)       aPassed
             andP0LaneCount: (NSInteger)  aP0LaneCount
             andP0BandWidth: (NSInteger)  aP0linkBandwdidth
                andP0Status: (NSUInteger) aP0Status
             andP1LaneCount: (NSInteger)  aP1LaneCount
             andP1BandWidth: (NSInteger)  aP1linkBandwdidth
                andP1Status: (NSUInteger) aP1Status
                 andRawData: (NSData*)    aData;



@end
@interface ATDeviceIndividualDisplayEyeTestLaneResult: NSObject

@property (nonatomic) int voltageMax;
@property (nonatomic) int voltageMin;
@property (nonatomic) int timeMax;
@property (nonatomic) int timeMin;
@property (nonatomic) int eyeHeight;
@property (nonatomic) int eyeWidth;
@property (nonatomic) int totalLanes;


-(id) initWithEyeResultWithVoltageMax:(int) voltageMax
                        andVoltageMin:(int) voltageMin
                        andTimeMax:(int) timeMax
                        andTimeMin:(int) timeMin
                         andEyeHeight:(int) eyeHeight
                        andEyeWidth:(int) eyeWidth;



@end

@interface ATDeviceDisplayEyeTestLaneResult: NSObject


@property (nonatomic) NSArray <ATDeviceIndividualDisplayEyeTestLaneResult*> *eyeResultValues;
@property (nonatomic) NSUInteger result;


-(id) initWithEyeResultArray:(NSArray <ATDeviceIndividualDisplayEyeTestLaneResult*>*)aeyeResultValues andResult:(NSUInteger) aResult;


@end

@interface ATDeviceEyeResult: NSObject

- (id)          initWithEyeWidth: (double) eyeWidth
                    andEyeHeight: (double) eyeHeight
            andEyeVerticalOffset: (double) eyeVerticalOffset
          andEyeHorizontalOffset: (double) eyeHorizontalOffset
            andEyeMidpointHeight: (double) eyeMidpointHeight
            andEyeMidpointOffset: (double) eyeMidpointOffset
                       andVScale: (double) eyeVScale
                       andHScale: (double) eyeHScale
                      andEyeType: (ATDeviceTitanRidgeEyeType) eyeType
                      andEyeData: (NSArray <NSData*> *) eyeData;

@property (nonatomic) double eyeWidth;
@property (nonatomic) double eyeHeight;
@property (nonatomic) double eyeVerticalOffset;
@property (nonatomic) double eyeHorizontalOffset;
@property (nonatomic) double eyeMidpointHeight;
@property (nonatomic) double eyeMidpointOffset;
@property (nonatomic) double eyeVerticalScale;
@property (nonatomic) double eyeHorizontalScale;
@property (nonatomic) ATDeviceTitanRidgeEyeType eyeType;
@property (nonatomic, strong) NSArray <NSData*> *eyeData;


@end


@interface ATDeviceDisplayPortSymbolErrorCount : NSObject

@property (nonatomic) NSInteger totalErrorCount;
@property (nonatomic) NSInteger cedarP0ErrorCount;
@property (nonatomic) NSInteger cedarP1ErrorCount;
@property (nonatomic) NSInteger cedarP0Lane0ErrorCount;
@property (nonatomic) NSInteger cedarP0Lane1ErrorCount;
@property (nonatomic) NSInteger cedarP0Lane2ErrorCount;
@property (nonatomic) NSInteger cedarP0Lane3ErrorCount;
@property (nonatomic) NSInteger cedarP1Lane0ErrorCount;
@property (nonatomic) NSInteger cedarP1Lane1ErrorCount;
@property (nonatomic) NSInteger cedarP1Lane2ErrorCount;
@property (nonatomic) NSInteger cedarP1Lane3ErrorCount;

- (id) initWithTotalErrorCount: (NSInteger) totalErrCnt
          andCedarP0ErrorCount: (NSInteger) cedarP0ErrCnt
          andCedarP1ErrorCount: (NSInteger) cedarP1ErrCnt
     andCedarP0Lane0ErrorCount: (NSInteger) cedarP0L0ErrCnt
     andCedarP0Lane1ErrorCount: (NSInteger) cedarP0L1ErrCnt
     andCedarP0Lane2ErrorCount: (NSInteger) cedarP0L2ErrCnt
     andCedarP0Lane3ErrorCount: (NSInteger) cedarP0L3ErrCnt
     andCedarP1Lane0ErrorCount: (NSInteger) cedarP1L0ErrCnt
     andCedarP1Lane1ErrorCount: (NSInteger) cedarP1L1ErrCnt
     andCedarP1Lane2ErrorCount: (NSInteger) cedarP1L2ErrCnt
     andCedarP1Lane3ErrorCount: (NSInteger) cedarP1L3ErrCnt;

@end



@interface ATDeviceSymbolErrorCount : NSObject

@property (nonatomic) NSInteger dP0Lane0ErrorCount;
@property (nonatomic) BOOL      dP0Lane0CountValid;
@property (nonatomic) NSInteger dP0Lane1ErrorCount;
@property (nonatomic) BOOL      dP0Lane1CountValid;
@property (nonatomic) NSInteger dP0Lane2ErrorCount;
@property (nonatomic) BOOL      dP0Lane2CountValid;
@property (nonatomic) NSInteger dP0Lane3ErrorCount;
@property (nonatomic) BOOL      dP0Lane3CountValid;

@property (nonatomic) NSInteger dP1Lane0ErrorCount;
@property (nonatomic) BOOL      dP1Lane0CountValid;
@property (nonatomic) NSInteger dP1Lane1ErrorCount;
@property (nonatomic) BOOL      dP1Lane1CountValid;
@property (nonatomic) NSInteger dP1Lane2ErrorCount;
@property (nonatomic) BOOL      dP1Lane2CountValid;
@property (nonatomic) NSInteger dP1Lane3ErrorCount;
@property (nonatomic) BOOL      dP1Lane3CountValid;

- (id) initWithDPLane0ErrorCount: (NSInteger)   aDP0Lane0ErrorCount
           andDP0Lane0CountValid: (BOOL)        aDP0Lane0CountValid
          andaDP0Lane1ErrorCount: (NSInteger)   aDP0Lane1ErrorCount
           andDP0Lane1CountValid: (BOOL)        aDP0Lane1CountValid
          andaDP0Lane2ErrorCount: (NSInteger)   aDP0Lane2ErrorCount
           andDP0Lane2CountValid: (BOOL)        aDP0Lane2CountValid
          andaDP0Lane3ErrorCount: (NSInteger)   aDP0Lane3ErrorCount
           andDP0Lane3CountValid: (BOOL)        aDP0Lane3CountValid

          andaDP1Lane0ErrorCount: (NSInteger)   aDP1Lane0ErrorCount
           andDP1Lane0CountValid: (BOOL)        aDP1Lane0CountValid
          andaDP1Lane1ErrorCount: (NSInteger)   aDP1Lane1ErrorCount
           andDP1Lane1CountValid: (BOOL)        aDP1Lane1CountValid
          andaDP1Lane2ErrorCount: (NSInteger)   aDP1Lane2ErrorCount
           andDP1Lane2CountValid: (BOOL)        aDP1Lane2CountValid
          andaDP1Lane3ErrorCount: (NSInteger)   aDP1Lane3ErrorCount
           andDP1Lane3CountValid: (BOOL)        aDP1Lane3CountValid;

@end


//

@interface ATDeviceColorCRC : NSObject
@property (nonatomic) NSInteger numberOfMisMatched;
@property (nonatomic) uint16_t cedarP0RedCRC;
@property (nonatomic) uint16_t cedarP0GreenCRC;
@property (nonatomic) uint16_t cedarP0BlueCRC;
@property (nonatomic) uint16_t cedarP1RedCRC;
@property (nonatomic) uint16_t cedarP1GreenCRC;
@property (nonatomic) uint16_t cedarP1BlueCRC;


- (id) initWithMisMatched: (NSInteger) numMisMatch
             andCedarP0RCRCRed: (uint16_t) cedarP0RedCRC
            andCedarP0CRCGreen: (uint16_t) cedarP0GreenCRC
             andCedarP0CRCBlue: (uint16_t) cedarP0BlueCRC
             andCedarP1RCRCRed: (uint16_t) cedarP1RedCRC
            andCedarP1CRCGreen: (uint16_t) cedarP1GreenCRC
             andCedarP1CRCBlue: (uint16_t) cedarP1BlueCRC;
@end

@interface ATDeviceColor32bitCRC : NSObject
@property (nonatomic) NSInteger numberOfMisMatched;
@property (nonatomic) uint32_t dPRX0RedCRC;
@property (nonatomic) uint32_t dPRX0GreenCRC;
@property (nonatomic) uint32_t dPRX0BlueCRC;
@property (nonatomic) uint32_t dPRX1RedCRC;
@property (nonatomic) uint32_t dPRX1GreenCRC;
@property (nonatomic) uint32_t dPRX1BlueCRC;


- (id) initWithMisMatched: (NSInteger) numMisMatch
            andDP0RCRCRed: (uint32_t) aDP0RedCRC
           andDP0CRCGreen: (uint32_t) aDP0GreenCRC
            andDP0CRCBlue: (uint32_t) aDP0BlueCRC
            andDP1RCRCRed: (uint32_t) aDP1RedCRC
           andDP1CRCGreen: (uint32_t) aDP1GreenCRC
            andDP1CRCBlue: (uint32_t) aDP1BlueCRC;

- (id) initWithATDeviceColorCRC: (ATDeviceColorCRC*) crc;
@end


@interface ATDevicePalladiumVideoStatus : NSObject

@property (nonatomic) NSInteger streamClock;
@property (nonatomic) NSInteger colorSpace;
@property (nonatomic) NSInteger dynamicRange;
@property (nonatomic) NSInteger colorCoefficient;
@property (nonatomic) NSInteger bitDepth; //6,8,10
@property (nonatomic) NSInteger activeHorizontalWidthInPixels;
@property (nonatomic) NSInteger activeVerticalWidthInLines;
@property (nonatomic) NSInteger totalHorizontalInPixels;
@property (nonatomic) NSInteger totalVerticalInLines;
@property (nonatomic) NSInteger activeHorizontalStartInPixels;
@property (nonatomic) NSInteger activeVerticalStartInLines;
@property (nonatomic) BOOL      horizontalSyncPolarityIsPostive;
@property (nonatomic) BOOL      verticalSyncPolarityIsPostive;
@property (nonatomic) NSInteger horizontalSyncWidthInPixels;
@property (nonatomic) NSInteger verticalSyncWidthInLines;


@end

//main stream attributes
@interface ATDeviceDisplayPortMSA : NSObject

// Vertical is in Lines and Horizontal is in pixels
@property (nonatomic) BOOL msaLocked;
@property (nonatomic) BOOL msaValid;
@property (nonatomic) NSInteger horizontalSyncWidth;
@property (nonatomic) NSInteger horizontalSyncPolarity;
@property (nonatomic) NSInteger verticalSyncWidth;
@property (nonatomic) NSInteger verticalSyncPolarity;
@property (nonatomic) NSInteger totalHorizontal;
@property (nonatomic) NSInteger totalVertical;
@property (nonatomic) NSInteger activeHorizontalWidth;
@property (nonatomic) NSInteger activeVerticalWidth;
@property (nonatomic) NSInteger horizontalStart;
@property (nonatomic) NSInteger verticalStart;
@property (nonatomic) NSInteger verticalBlankID;
@property (nonatomic) BOOL      verticalBlankFlag;
@property (nonatomic) BOOL      verticalBlankFieldIDFlag;
@property (nonatomic) BOOL      verticalBlankInterfaceFlag;
@property (nonatomic) BOOL      verticalBlankNoVideoStreamFlag;
@property (nonatomic) BOOL      verticalBlankAudioMuteFlag;
@property (nonatomic) BOOL      verticalBlankHDCPSyncDetectFlag;
@property (nonatomic) NSInteger verticalBlankMisc1And0;
@property (nonatomic) BOOL verticalBlankLocked;
@property (nonatomic) BOOL verticalBlankActive;
@end

@interface ATDeviceDisplayPortStream: NSObject

@property (nonatomic) BOOL vidLocked;
@property (nonatomic) NSInteger activeHorizontalWidth;
@property (nonatomic) NSInteger activeVerticalWidth;
@property (nonatomic) NSInteger refreshRate;

@end



@interface ATDeviceDisplayPortRxStatus : NSObject

@property (nonatomic) BOOL cableDetected;
@property (nonatomic) BOOL powerDetected;
@property (nonatomic) BOOL hotplugDetect;
@property (nonatomic) ATDeviceDisplayPortStream * stream0;
@property (nonatomic) ATDeviceDisplayPortStream * stream1;

@end

@interface ATDeviceHDMIStatus : NSObject

@property (nonatomic) double videoFrequency; //in Mhz
@property (nonatomic) NSInteger activeHorizontalWidth;
@property (nonatomic) NSInteger activeVerticalWidth;
@property (nonatomic) double refreshRate; //in Hz
@property (nonatomic) BOOL rxVideoLock;
@property (nonatomic) BOOL rxIOPLLLock;
@property (nonatomic) BOOL rxGXBReady;
@property (nonatomic) ATDeviceHDMISpecMode hdmiSpecMode;
@property (nonatomic) NSInteger pixelOversample;
@property (nonatomic) BOOL rxHDCP1XAuthenticated;
@property (nonatomic) BOOL rxHDCP2XAuthenticated;
@property (nonatomic) ATDeviceHDMIVideoMode videoMode;
@property (nonatomic) ATDeviceHDMIColorModes hdmiColorMode ;
@property (nonatomic) ATDeviceHDMIColorDepth hdmiColorDepth;

- (id) initWithVideoFrequencyData:(double)aVideoFrequency
     andActiveHorizontalWidthData:(NSInteger)aActiveHorizontalWidth
       andActiveVerticalWidthData:(NSInteger)aActiveVerticalWidth
               andRefreshRateData:(double)aRefreshRate
   andhdmiGeneralRXSTATSLowerData:(NSInteger)aHDMIGeneralRXSTATS;

@end

@interface ATDeviceHDCPStatus : NSObject

@property (nonatomic) BOOL hdcp1XAuthenticated;
@property (nonatomic) BOOL hdcp2XAuthenticated;

- (id) initWithHDCPData:(uint32_t)aHDCPStatusData
     andIsDisplayTxPort:(BOOL)isDPTx;
@end

@interface ATDeviceVideoStatus : NSObject

@property  ATDeviceDisplayPortMSA * displayPortMSA;
@property  ATDeviceDisplayPortRxStatus * displayPortRxStatus;

@end

@interface ATDeviceAceShortStatus : NSObject
//stores raw data, Data starts from LSB.
//example:
//Ace1 status locate at 0x1
//Ace2 status locate at 0x2
//Ace3 status locate at 0x4
//Ace4 status locate at 0x8
//Ace5 status locate at 0x10
@property (nonatomic, readonly) NSInteger shortStatus;

-(BOOL)shortDetectedAtAce:(NSInteger)aIndex; //return short status from one Ace. aIndex is 1 based.
-(id) initWithShortStatus:(NSInteger)aShortStatus;
@end

@interface ATDeviceColorBars : NSObject


- (id) initWithNumberOfBars:(NSInteger) numberOfBar;

- (ATDeviceColors) colorAtBar:(NSInteger) barIndex;
- (void) setColor: (ATDeviceColors) color AtBar:(NSInteger) barIndex;
- (void) addColor:(ATDeviceColors) color;
- (NSInteger) count;

@end

@interface ATDeviceColor16Bars : ATDeviceColorBars






@end


typedef NS_ENUM(NSInteger,ATDeviceDataRate) {
    ATDeviceDataRate20Gbps = 0,
    ATDeviceDataRate10Gbps = 1,
    ATDeviceDataRate5Gbps = 2,
    ATDeviceDataRateReserved = 3,
    
};

typedef NS_ENUM(NSInteger,ATDeviceDataMode) {
    ATDeviceDataDisconnectedMode = 0,
    ATDeviceDataCIOMode = 0x1,
    ATDeviceDataDPMode = 0x2,
    ATDeviceDataUSB3Mode = 0x8,
    ATDeviceDataMultiFunctionDPMode = 0x10,
    
};


@interface ATDeviceLinkStatus : NSObject

@property (nonatomic) ATDeviceDataRate dataRate;
@property (nonatomic) ATDeviceDataMode dataMode;
@property (nonatomic) NSInteger lane0Link;
@property (nonatomic) NSInteger lane1Link;

- (id) initWithDataRate: (ATDeviceDataRate)   aDataRate
            andDataMode: (ATDeviceDataMode)   aDataMode
           andLane0Link: (NSInteger)          aLane0Link
           andLane1Link: (NSInteger)          aLane1Link;
@end


@interface ATDevicePortsLinkStatus: NSObject

@property (nonatomic,strong) ATDeviceLinkStatus * tbtaLinkStatus;
@property (nonatomic,strong) ATDeviceLinkStatus * tbtbLinkStatus;
@property (nonatomic,strong) ATDeviceLinkStatus * tbtcLinkStatus;
@property (nonatomic,strong) ATDeviceLinkStatus * tbtdLinkStatus;


-(id) initWithTBTALinkStatus: (ATDeviceLinkStatus*) tbtaLinkStatus
andTBTBLinkStatus: (ATDeviceLinkStatus*) tbtbLinkStatus
andTBTCLinkStatus: (ATDeviceLinkStatus*) tbtcLinkStatus
andTBTDLinkStatus: (ATDeviceLinkStatus*) tbtdLinkStatus;

@end

@interface ATDeviceGPIOPort: NSObject

//values
//Example: 0x2544 = 0b0010010101000100
//Pins 3,6,8,10,and 13 are at a logic level High
//The rest of the pins are at a logic level LOW
@property (nonatomic) uint16_t values;
//directions
//Example: 0x4083 = 0b0100000010000011
//Pins 0,1,7, and 14 are outputs.
//• The rest of the pins are inputs.
@property (nonatomic) uint16_t directions;

@end
