//
//  ATDeviceElement.h
//  ATDeviceElements
//
//  Created by Sai  on 9/6/16.
//  Copyright © 2016 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATDeviceBusInterfaceBase.h"
#import <ATDeviceElements/ATDeviceElementsCommon.h>
#import <ATDeviceElements/ATDeviceParameters.h>
#import <ATDeviceElements/ATDeviceVersions.h>

#define kATDeviceVendorID 0x5AC

@interface ATDeviceElement : NSObject

-(id) initWithCommunicationInterface: (ATDeviceBusInterface*) aCommInterface;


// The default Timeout for simple4ccCommand is 10 seconds
// simple4ccCommand is for sending 4cc commands without args or data.
// if you have data to write or args, you can use execute4ccCommand below
- (BOOL) simple4ccCommand: (NSString*) cmdToSend andError: (NSError**) aError;

// Function to read Test Device Register
-(BOOL) readRegisterAtAddress:(NSUInteger)address
                   withLength:(NSUInteger)length
                         data:(uint8_t *)data
                        error:(NSError **)error;

// Function to read Test Device Registers, you can read more than 1 register
// param addresses   NSArray * of NSNumber
-(NSArray *) readRegistersAtAddresses:(NSArray *)addresses
                                error:(NSError **)error;

// Function to write Test Device Register
-(BOOL) writeRegisterAtAddress:(NSUInteger)address
                        length:(NSUInteger)length
                          data:(uint8_t *)data
                         error:(NSError **)error;
// Function to execute 4CC command
// parameters
//  data: is used by both Write and Read.
-(BOOL) execute4ccCommand:(NSString*)command4cc
                 withArgs:(uint32_t)args
                 withData:(uint8_t*)data
              writeLength:(NSUInteger)writeLength
               readLength:(NSUInteger)readLength
      timeoutMilliseconds:(NSUInteger)timeoutMilliseconds
                    error:(NSError **) error;

//Functions to access the data buffer in a single access
-(BOOL) writeDataBufferWithData : (uint8_t*)data
                     withLength : (uint16_t)writeLength
                      withError : (out NSError**)error;

-(BOOL) readDataBufferWithData : (uint8_t*)data
                    withLength : (uint16_t)readLength
                     withError : (out NSError**)error;

// read back the info in raw binary format
// parameters
// outputInfo:	The Raw binary NSData of the Test Device Info. outputInfo[0] = Byte[0] in User manual. Pass in NSData *data's &data
// aError:		When Error occured, NSError will be set.
// return value
// NSData:	the raw info in NSData
//
- (NSData*) rawInfo: (NSError**) aError;


- (BOOL) isVersionMatchedWithExpectedVersion: (ATDeviceVersions*) expectedVersion andError: (NSError**) aError;

// parameters
//      aError:		When Error occured, NSError will be set.
// return value
//      device ID  defined in ATDeviceElementsID in <ATDeviceElements/ATDeviceElementsCommon.h>
- (NSUInteger) deviceID: (NSError**) aError;
// parameters
//      aError:		When Error occured, NSError will be set.
// return value
//      Mode Status Register value // Check User Manual to find out what the Mode status register mean
- (NSUInteger) selfTest: (NSError**) aError ;

- (NSString *) vendorSerialNumber: (NSError**) aError ;

// parameters
//      aError:		When Error occured, NSError will be set.
// return value
//      returns Apple Serial Number or nil when there was an Error.
- (NSString *) appleSerialNumber:  (NSError**) aError ;

//RSTP - Reset the specified IC on
// parameters
//      selectedIC:input    The 4 bytes in the user manual.
//      aError:output		When Error occured, NSError will be set.
// return value
//
- (BOOL) resetSelectedIC: (uint32_t) selectedIC andError: (NSError**) aError;

// command = "Gaid"
// reset all components
- (BOOL) reset: (NSError**) aError;

// Command = "I2Cx"
// i2c Transfer
// parameters
//      busID: i2c Bus ID
//      aAdress:  7 bit i2c address. Some vendors incorrectly provide two 8-bit slave addresses for their device,
//                one to write to the device and one to read from the device.
//                  This 8-bit number actually encodes the 7-bit slave address and the read/write bit.
//                  it is important to only use the top 7 bits of the address as the slave address.
//                  That is why you need shift the address 1 bit to get rid of the  read/write bit.
//                  e.g. 24LC02 EEPROM i2c address is 0xA0 = Write address and 0xA1 is the read address. The actual Address is (0xA0 >> 1).
//
//      writeLen: write dnumber of data in byte.
//      readLen: Read number of data in byte
//      data:  Write and Read both share this array. Size of this array must be bigger than writeLen and readLen. Max size is 255.
// return value
//
- (BOOL) i2cTransferWithBusId: (uint8_t) busID
                      address: (uint8_t) aAdress
                  andWriteLen: (uint8_t) writeLen
                   andReadLen: (uint8_t) readLen
                      andData: (uint8_t*) data
                     andError: (NSError**) aError;

// Command = "SPIx"
// SPI transfer
// parameters
//      busID: SPI Bus ID
//      slaveSelectPort:  0 = GPIOA, 1 = GPIOB and so on {GPIOA=0,GPIOB=1,GPIOC=2,GPIOD=3,GPIOE=4,GPIOF=5,GPIOG=6,GPIOH=7,GPIOI=8};
//      slaveSelectPin:  The pin for GPIO Port from 0 to 15
//      isWriteAndReadMode: YES = Write and Read Mode or NO = Write then Read mode
//      writeLen: write dnumber of data in byte
//      readLen: Read number of data in byte
//      data:  Write and Read both share this array. Size of this array must be bigger than writeLen and readLen. Max size is 255.
// return value
- (BOOL) spiTransferWithBusId: (uint8_t) busID
           andSlaveSelectPort: (uint8_t) slaveSelectPort
            andSlaveSelectPin: (uint8_t) slaveSelectPin
          andWriteAndReadMode: (BOOL) isWriteAndReadMode // isWriteAndReadMode = Write One byte and then Read one byte
                  andWriteLen: (uint8_t) writeLen
                   andReadLen: (uint8_t) readLen
                      andData: (uint8_t*) data
                     andError: (NSError**) aError;

// Command = URTx
// UART transfer
// parameters
//      uartID: UART Bus ID
//      writeLen: write dnumber of data in byte
//      readLen: Read number of data in byte
//      data:  Write and Read both share this array. Size of this array must be bigger than writeLen and readLen. Max size is 255.
//      uartReadTimeOutInMiliSeconds:  timeout in Miliseconds when read the UART bus . Only vaild if readLen is non zero.
- (BOOL) uartTransferWithBusId: (uint8_t) uartID
                   andWriteLen: (uint8_t) writeLen
                    andReadLen: (uint8_t) readLen
                       andData: (uint8_t*) data
            andUartReadTimeOut: (uint16_t) uartReadTimeOutInMiliSeconds
                      andError: (NSError**) aError;

//Command = CANx
- (BOOL) canTransmitWithBusId: (uint8_t) canID
               andWaitForSend: (BOOL) waitForSend
                    andSetRTR: (BOOL) setRTR
             andUseExtendedID: (BOOL) extendedID
                    andLength: (uint8_t) len
                 andMessageID: (uint32_t) messageID
                      andData: (uint8_t*) data
                     andError: (NSError**) aError;

- (BOOL) canRecieveWithBusId: (uint8_t) canID
                   andLength: (uint8_t) len
               andDataBuffer: (uint8_t*) data
        andRemainingMessages: (uint16_t*) remainingMessages
         andDeviceBufferSize: (uint16_t*) deviceBufferSize
 andNumberOfMessagesReceived: (uint8_t*) messagesReceived
                    andError: (NSError**) aError;

// When Read data transfer failed, you can check how many bytes got read back.
// Number of valid bytes in the data buffer
- (NSInteger) validBytesInDataBufferhWithError: (NSError**) aError;

// dumpStatusLogWithError
// param[out]       currentTime will be set to test device current time. pass NULL or 0 if you don't need it.
// retval           an NSArray of ATDLogEntry which is defined in <ATDeviceElements/ATDeviceParameters.h>
- (NSArray<ATDLogEntry*>*) dumpStatusLogWithCurrentTime: (uint64_t*) currentTime
                                               andError: (NSError**) aError;

/** readUserPageAtAddress
 * brief read Test Device User Page. 4CC command = UEPr
 *
 * param[in] startAddress:            Message/Frame ID
 * param[in] dataLength:
 * param[in] buffer:                Remote transmission request (RTR)
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval BOOL: YES = sucess NO = Error;
 *
 *
 */
- (BOOL) readUserPageAtAddress: (uint16_t) startAddress
                     andLength: (uint8_t) dataLength
                 andDataBuffer: (uint8_t*) buffer
                      andError: (NSError**) aError;
/** writeUserPageAtAddress
 * brief write Test Device User Page. 4CC command = UEPw
 *
 * param[in] startAddress:            Message/Frame ID
 * param[in] dataLength:
 * param[in] buffer:                Remote transmission request (RTR)
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval BOOL: YES = sucess NO = Error;
 *
 *
 */
- (BOOL) writeUserPageAtAddress:(uint16_t)startAddress
                      andLength:(uint8_t)dataLength
                  andDataBuffer:(uint8_t *)buffer
                       andError:(NSError **)aError;

/** registerNameFromAddress
 * brief Get NSString containing the name of the register
 *
 * param[in] address:            Register address from 0 - 255
 * retval NSString*: nil = error, otherwise name of register
 *
 *
 */
- (NSString*) registerNameFromAddress:(uint8_t)address;

/** decodedRegisterDataFromAddress
 * brief Get NSString containing the decoded information of a register
 *
 * param[in] address:            Register address from 0 - 255
 * param[in] data:               Data for decoding
 * retval NSString*: nil = error, otherwise decoded data of register
 *
 *
 */
- (NSString*) decodedRegisterDataFromAddress:(uint8_t)address
                                     andData:(NSData*)data;

/** decodedRegisterInformationAtAddresses
 * brief Get NSString containing the decoded information of the specified registers on the device
 *
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval NSString*: nil = error, otherwise decoded data of registers
 *
 *
 */
- (NSString*) decodedRegisterInformationAtAddresses:(NSArray*)addresses
                                          withError:(NSError **)aError;

/** decodedAllRegisterInformationWithError
 * brief Get NSString containing the decoded information of every register on the device
 *
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval NSString*: nil = error, otherwise decoded data of registers
 *
 *
 */
- (NSString*) decodedAllRegisterInformationWithError:(NSError **)aError;

/** deviceIdFromInterface
 * brief Static Function to get Device ID with a communicaiton Interface
 *
 * param[in] aInterface:            communicaiton Interface
 * param[out] aError: nil = NO error, or error set. Error code is defined in <ATDeviceElements/ATDeviceCarbonErrors.h>
 * retval NSUInteger: device ID  defined in ATDeviceElementsID in <ATDeviceElements/ATDeviceElementsCommon.h>
 *
 *
 */
+ (NSUInteger) deviceIdFromInterface: (ATDeviceBusInterface*)aInterface andError:(NSError**) aError;

/**
 Set ip address of test box

 @param ipAddress pass ip address in the form of string
 @param aError if error in setting ip this descriptor gets set
 @return false if set ip fails
 */
-(BOOL) setIPAddressWithIPString:(NSString *)ipAddress andError:(NSError **)aError;

-(BOOL) setNetMaskWithIPString:(NSString *)netMask andError:(NSError **)aError;

/**
 Set cc to be persistent so cc will remain in previous state after reboot

 @param aError if error setting cc to be persistent
 @return false if setting cc to be persistent fails
 */
-(BOOL) makeCCStatePersistentWithError:(NSError **)aError;

/**
 Set option bits to be persistent after reboot
 Option bits include :
     PD Sniffer enable
     Dock Channel enable
     Automatically start the Apple Debug VDM process after connecting
     Mojo enable
     Use Debug USB pair for primary debug protocol (if cleared, SBU will be used  as primary)
 
 @param aError  if error setting optional bits to be persistent
 @return false if setting option bit to be persistent fails
 */
-(BOOL) makeOptionBitsPersistentWithError:(NSError **)aError;

/**
 Get all the GPIO Pin values

 @param aError is set when error getting GPIO port status
 @return an Array of GPIO ports
 
 NSArray[0] or NSArray[ATD_GPIO_A]= PORTA
 NSArray[1] or NSArray[ATD_GPIO_B]= PORTB
 NSArray[2] or NSArray[ATD_GPIO_C]= PORTC
 NSArray[3] or NSArray[ATD_GPIO_D]= PORTD .. and etc.
 */
- (NSArray<ATDeviceGPIOPort*>*) gpioStatus: (NSError **) aError;

/**
 Check if port is connected

 @param portNumber port number of the test box
 @param connected is set to true when port is connected and vice versa
 @param aError is set when error checking whether the port is connected
 @return false if fails to check port status
 */
- (BOOL) port:(NSInteger)portNumber isConnected:(BOOL*)connected withError:(NSError **)aError;

@property (strong, nonatomic, readonly) ATDeviceBusInterface * communicationInterface;
@end
