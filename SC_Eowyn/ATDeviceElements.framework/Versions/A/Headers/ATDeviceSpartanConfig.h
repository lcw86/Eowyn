//
//  ATDeviceSpartanConfig.h
//  ATDeviceElements
//
//  Created by Corey Lange on 7/7/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kSpartanConfigurationLength        52

typedef NS_ENUM(uint8_t, ATDSpartanPowerRole)
{
    ATDSpartanPowerSink      = 0,
    ATDSpartanPowerSource    = 1,
};

typedef NS_ENUM(uint8_t, ATDSpartanPinProtocol)
{
    ATDSpartanDataDisabled      = 0,
    ATDSpartanDataUSB           = 1,
    ATDSpartanDataSWD           = 2,
    ATDSpartanDataUART          = 3,
    ATDSpartanDataUSB_KIS       = 4,
};

typedef NS_ENUM(uint16_t, ATDSpartanAction)
{
    ATDSpartanActionReset       = 0x8000,
    ATDSpartanActionForceDFU    = 0x8001,
    ATDSpartanActionForceDiags  = 0x8002,
};

typedef NS_ENUM(uint8_t, ATDSpartanCableDetection)
{
    ATDSpartanAutoDetectCable   = 0,
    ATDSpartanStandardCable     = 1,
    ATDSpartanNeutronCable      = 2,
};

typedef NS_ENUM(uint8_t, ATDSpartanBananaFunction)
{
    ATDSpartanBananaDisabled    = 0x00,
    ATDSpartanBananaUFPKeyboard = 0x01,
    ATDSpartanBananaUFPCDC      = 0x02,
    ATDSpartanBananaDFPKIS      = 0x81,
};

#define kSpartanUartConfiguration_ParityMask            0x03
#define kSpartanUartConfiguration_ParityNone            0x00
#define kSpartanUartConfiguration_ParityEven            0x01
#define kSpartanUartConfiguration_ParityOdd             0x02
#define kSpartanUartConfiguration_WordLengthMask        0x0C
#define kSpartanUartConfiguration_WordLength8Bits       0x00
#define kSpartanUartConfiguration_WordLength9Bits       0x04
#define kSpartanUartConfiguration_StopBitsMask          0x30
#define kSpartanUartConfiguration_StopBits1Bit          0x00
#define kSpartanUartConfiguration_StopBits1p5Bits       0x10
#define kSpartanUartConfiguration_StopBits2Bits         0x20

@interface ATDeviceSpartanConfig : NSObject

//Power Path
@property ATDSpartanPowerRole powerRoleForTarget;
@property uint8_t chargingEnabled;

//Mission USB
@property uint8_t enableBanana;
@property uint8_t missionUSBTarget;
@property uint32_t missionUSBDelay;
@property uint8_t missionUSBSignal;

//SBU
@property ATDSpartanPinProtocol sbuRoute;
@property uint8_t sbuTarget;
@property uint32_t sbuDelay;
@property uint8_t sbuPassthroughEnabled;

//Debug USB
@property ATDSpartanPinProtocol debugUSBRoute;
@property uint8_t debugUSBTarget;
@property uint32_t debugUSBDelay;

//SWD
@property uint8_t dockChannelsEnabled;
@property uint8_t defaultDockChannel;
@property uint32_t swdClockSpeed;
@property uint32_t dockChannelPollPeriod;
@property uint32_t dockChannelMask;

//UART
@property uint32_t uartBuadRate;
@property uint8_t uartConfiguration;

//Buffer data while disconnected
@property uint8_t bufferDisconnected;

//Action
@property ATDSpartanAction actionAction;
@property uint8_t actionTarget;
@property uint32_t actionDelay;

//Other
@property uint8_t advancedMuxSettings;
@property ATDSpartanCableDetection cableDetectionOverride;

/**
 Update all valid configuration properties based on the passed in JSON

 @note JSON files passed in here should be created using configAsFileContentsWithError
 
 @param fileContents Contents of the JSON file
 @param error Error on failure
 @return YES on success
 */
-(BOOL)loadWithFileContents : (NSString*)fileContents
                  withError : (NSError**)error;

/**
 Update all valid configuration properties based on the passed in binary data
 
 @note Data passed in here should be created using configAsDataWithError

 @param data Binary data containing configuration
 @param error Error on failure
 @return YES on success
 */
-(BOOL)loadWithData : (NSData*)data
          withError : (NSError**)error;

/**
 Create the contents of a JSON file using the configuration properties

 @param error Error on failure
 @return Contents of a JSON file on success. Otherwise, nil
 */
-(NSString*)configAsFileContentsWithError : (NSError**)error;

/**
 Create binary data using the configuration properties

 @param error Error on failure
 @return Binary data representing the configuration on success. Otherwise, nil
 */
-(NSData*)configAsDataWithError : (NSError**)error;

@end
