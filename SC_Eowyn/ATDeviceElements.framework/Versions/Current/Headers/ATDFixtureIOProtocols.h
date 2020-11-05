//
//  ATDFixtureIOProtocols.h
//  ATDeviceElements
//
//  Created by Sai  on 9/10/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#ifndef ATDFixtureIOProtocols_h
#define ATDFixtureIOProtocols_h

typedef NS_ENUM(uint8_t, ATDeviceDIOType) {
    ATDeviceDIOLow = 0,
    ATDeviceDIOHigh,
    ATDeviceDIOToggle,
    ATDeviceDIOFlash,
    ATDeviceDIOUnknown = 0xFF
    
};

typedef NS_ENUM(uint8_t, ATDFixtureI2CMode) {
    ATDFixtureI2CModeI2C       = 0,
    ATDFixtureI2CModeSMBusDevice,
    ATDFixtureI2CModeSMBusHost,
    ATDFixtureI2CModeTotal
};

typedef NS_ENUM(uint8_t, ATDFixtureI2CAckAddressMode) {
    ATDFixtureI2CAckAddressMode7bit       = 0,
    ATDFixtureI2CAckAddressMode10bit,
    ATDFixtureI2CAckAddressModeTotal
};

typedef NS_ENUM(uint8_t, ATDFixtureSpiCPOL){
    
    ATDFixtureSpiCPOLLow= 0,  //Clock Idle = Low
    ATDFixtureSpiCPOLHigh     //Clock Idle = High
};

typedef NS_ENUM(uint8_t, ATDFixtureSpiCPHA){
    ATDFixtureSpiCPHA1Edge= 0, //Leading Edge Falling edge
    ATDFixtureSpiCPHA2Edge     //Trailing Edge  Rising Edge
};


typedef NS_ENUM(uint8_t, ATDFixtureSpiFirstBit){
    
    ATFixtureSpiFirstBitMSB= 0,
    ATFixtureSpiFirstBitLSB
};
typedef NS_ENUM(uint16_t, ATDFixtureSpiBaudRate){
    
    ATDFixtureSpiBaudRate21MHz = 2,
    ATDFixtureSpiBaudRate10_5MHz = 4,
    ATDFixtureSpiBaudRate5_25MHz = 8,
    ATDFixtureSpiBaudRate2_63MHz = 16,
    ATDFixtureSpiBaudRate1_31MHz = 32,
    ATDFixtureSpiBaudRate656kHz = 64,
    ATDFixtureSpiBaudRate328kHz = 128,
    ATDFixtureSpiBaudRate164kHz = 255,
    ATDFixtureSpiBaudRateNumOfFixtureSPIBaudRate,
};

@protocol ATDFixtureIOCapable < NSObject >

/**
 write Digital Output

 @param iOIndex DIO Index
 @param value  ATDeviceDIOType
 @param error nil = NO error, or error set.
 @return YES = sucess , NO = Error;
 */
- (BOOL)  writeDigitalOutput: (NSInteger) iOIndex
                    andValue: (ATDeviceDIOType) value
                    andError: (out NSError **) error;

/**
 read Digital Input

 @param iOIndex DIO Index
 @param error nil = NO error, or error set.
 @return ATDeviceDIOLow (0) or ATDeviceDIOHigh (1).
 */
- (ATDeviceDIOType) readDigitalInput: (NSInteger) iOIndex
                            andError: (out NSError **) error;

/**
 Configure i2c bus speed, mode and ack mode

 @param i2cId bus id that can be configured for passed device
 @param mode @sa ATDFixtureI2CMode
 @param i2cAddress i2c address to configure
 @param clockSpeed clock speed to configure it to
 @param enableAck Yes or NO to enable/disable ack
 @param ackAddressMode @sa ATDFixtureI2CAckAddressMode
 @param aError error if method fails
 @return YES or NO depending on result
 */
-(BOOL) configureI2C: (int) i2cId
             andMode: (ATDFixtureI2CMode) mode
          andI2cAddr: (uint16_t) i2cAddress
       andClockSpeed: (uint32_t) clockSpeed
        andEnableAck: (BOOL) enableAck
       andAckAddress: (ATDFixtureI2CAckAddressMode)ackAddressMode
            andError: (out NSError *__autoreleasing  _Nullable * _Nullable) aError;

/**
 Send/Receive I2C Message for unique user bus id for the device

 @param aAdress 7 bit i2c address. Some vendors incorrectly provide two 8-bit slave addresses for their device,
 one to write to the device and one to read from the device.
 This 8-bit number actually encodes the 7-bit slave address and the read/write bit.
 it is important to only use the top 7 bits of the address as the slave address.
 That is why you need shift the address 1 bit to get rid of the  read/write bit.
 e.g. 24LC02 EEPROM i2c address is 0xA0 = Write address and 0xA1 is the read address. The actual Address is (0xA0 >> 1).
 @param writeLen write dnumber of data in byte
 @param readLen Read number of data in byte
 @param data Write and Read both share this array. Size of this array must be bigger than writeLen and readLen. Max size is 255.
 @param aError returns an error if something failed
 @return returns result YES or NO based on pass or fail
 */
- (BOOL) i2cTransferWithAddress: (uint8_t) aAdress
                    andWriteLen: (uint8_t) writeLen
                     andReadLen: (uint8_t) readLen
                        andData: (inout nonnull uint8_t*) data
                       andError: (out NSError *_Nullable*_Nullable) aError;


/**
 Sets spi baudrate from @sa ATDFixtureSpiBaudRate And set serial clock steady state from @sa ATDFixtureSpiCPOL
 and set active clock edge from @sa ATDFixtureSpiCPHA and endiannes of data transfer from @sa ATDFixtureSpiFirstBit
 
 @param baudRate set baud rate according to @sa ATDFixtureSpiBaudRate
 @param cpol set serial clock steady state from @sa ATDFixtureSpiCPOL
 @param cpha set active clock edge from @sa ATDFixtureSpiCPHA
 @param firstBit endiannes of data transfer from @sa ATDFixtureSpiFirstBit
 @param aError error if setting baud rate failed
 @return yes or no based on whether baud rate was succesfuly set
 */
- (BOOL) configureSPIwithBaudRate: (ATDFixtureSpiBaudRate) baudRate
                          andCPOL: (ATDFixtureSpiCPOL) cpol
                          andCPHA: (ATDFixtureSpiCPHA) cpha
                      andFirstBit: (ATDFixtureSpiFirstBit) firstBit
                         andError: (NSError *_Nullable*_Nullable) aError;


/**
 Transfer spi data with arguments

 @param isWriteAndReadMode If set to yes function will write one byte and then read one byte
 @param writeLen Number of bytes to write
 @param readLen Number of bytes to read
 @param data spi data
 @param aError error if spi transfer failed
 @return yes or no based on whether spi data was transfered
 */
- (BOOL) spiTransferWithWriteAndRead: (BOOL) isWriteAndReadMode
                         andWriteLen: (uint8_t) writeLen
                          andReadLen: (uint8_t) readLen
                             andData: (inout uint8_t*) data
                            andError: (out NSError **) aError;

@end

#endif /* ATDFixtureIOProtocols_h */
