//
//  ATDeviceFixture.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 1/23/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceErrors.h>

typedef NS_ENUM(uint8_t, ATDeviceIOValueType) {
    ATDeviceDIOValueLow = 0,
    ATDeviceDIOValueHigh,
};
typedef NS_ENUM(uint8_t,ATDeviceCanOpenOperation){
    
    ATDeviceCanOperationNone = 0x00,
    ATDeviceCanOpenOperationPosition = 0x01,
    ATDeviceCanOpenOperationVelocity = 0x03,
    ATDeviceCanOpenOperationHoming   = 0x06,
};

@interface ATDFixtureDriveErrors: NSObject
    @property (nonatomic) BOOL positionLimit;
    @property (nonatomic) BOOL cwLimit;
    @property (nonatomic) BOOL ccwLimit;
    @property (nonatomic) BOOL overTemp;
    @property (nonatomic) BOOL internalVoltage;
    @property (nonatomic) BOOL underVoltage;
    @property (nonatomic) BOOL overVoltage;
    @property (nonatomic) BOOL overCurrent;
    @property (nonatomic) BOOL badEncoder;
    @property (nonatomic) BOOL commError;
    @property (nonatomic) BOOL badFlash;
    @property (nonatomic) BOOL motorWinding;
@end
@interface ATDFixtureDriveStatus: NSObject
    @property (nonatomic) BOOL motorEnabled;
    @property (nonatomic) BOOL driveFault;
    @property (nonatomic) BOOL inPosition;
    @property (nonatomic) BOOL moving;
    @property (nonatomic) BOOL jogging;
    @property (nonatomic) BOOL stopping;
    @property (nonatomic) BOOL alarmPresent;
    @property (nonatomic) BOOL initializing;
    @property (nonatomic) BOOL operationEnabled;
    @property (nonatomic) BOOL currentOperationError;
    @property (nonatomic) BOOL currentOperationSuccess;
    @property (nonatomic) ATDeviceCanOpenOperation currentOperationMode;
@end
@interface ATDFixtureDriveInputs: NSObject
    @property (nonatomic) BOOL input1;
    @property (nonatomic) BOOL input2;
    @property (nonatomic) BOOL input3;
    @property (nonatomic) BOOL input4;
    @property (nonatomic) BOOL input5;
    @property (nonatomic) BOOL input6;
    @property (nonatomic) BOOL input7;
    @property (nonatomic) BOOL input8;
@end
@interface ATDFixtureDriveOutputs: NSObject
    @property (nonatomic) BOOL ouput1;
    @property (nonatomic) BOOL output2;
    @property (nonatomic) BOOL output3;
    @property (nonatomic) BOOL output4;
@end

typedef NS_ENUM(uint8_t,ATDeviceHomingMethodType){
    
    ATDeviceHomingMethod1 = 1,
    ATDeviceHomingMethod2 = 2,
    ATDeviceHomingMethod3 = 3,
    ATDeviceHomingMethod4 = 4,
    ATDeviceHomingMethod5 = 5,
    ATDeviceHomingMethod6 = 6,
    ATDeviceHomingMethod7 = 7,
    ATDeviceHomingMethod8 = 8,
    ATDeviceHomingMethod9 = 9,
    ATDeviceHomingMethod10 = 10,
    ATDeviceHomingMethod11= 11,
    ATDeviceHomingMethod12 = 12,
    ATDeviceHomingMethod13 = 13,
    ATDeviceHomingMethod14 = 14,
    ATDeviceHomingMethod15 = 15,
    ATDeviceHomingMethod16 = 16,
    ATDeviceHomingMethod17 = 17,
    ATDeviceHomingMethod18 = 18,
    ATDeviceHomingMethod19 = 19,
    ATDeviceHomingMethod20 = 20,
    ATDeviceHomingMethod21 = 21,
    ATDeviceHomingMethod22 = 22,
    ATDeviceHomingMethod23 = 23,
    ATDeviceHomingMethod24 = 24,
    ATDeviceHomingMethod25 = 25,
    ATDeviceHomingMethod26 = 26,
    ATDeviceHomingMethod27 = 27,
    ATDeviceHomingMethod28 = 28,
    ATDeviceHomingMethod29 = 29,
    ATDeviceHomingMethod30 = 30,
    ATDeviceHomingMethod31 = 31,
    ATDeviceHomingMethod32 = 32,
    ATDeviceHomingMethod33 = 33,
    ATDeviceHomingMethod34 = 34,
    ATDeviceHomingMethod35 = 35,
    
    
};

typedef NS_ENUM(int16_t,ATDeviceFixtureKeys){
    ATDAttributeMotorName              = 0,
    ATDAttributeMotorSoftwareVersion   = 1,
    ATDAttributeMotorHardwareVersion   = 2,
    ATDAttributeMotorPosition          = 3,
    ATDAttributeMotorVelocity          = 4,
    ATDAttributeMotorSerialNumber      = 5
};

@protocol ATDeviceFixtureCapable < NSObject >

/**
 Pass node id and get the device name string
 
 @param axisID Physical Node id value set by switch
 @param error If there was an error getting device name otherwise set to nil
 @return device name for given node id
 */
-(NSString *_Nullable) deviceNameForAxisID:(NSInteger) axisID
                                  andError:(out NSError *_Nullable*_Nullable)error;


/**
 Pass node id and get the hardware version string
 
 @param axisID Physical Node id value set by switch
 @param error If there was an error getting device name otherwise set to nil
 @return hardware version for given node id
 */
-(NSString *_Nullable) hardwareVersionForAxisID:(NSInteger) axisID
                                       andError:(out NSError *_Nullable*_Nullable)error;


/**
 Pass node id and get the software version string
 
 @param axisID Physical Node id value set by switch
 @param error If there was an error getting device name otherwise set to nil
 @return software version for given node id
 */
-(NSString *_Nullable) softwareVersionForAxisID:(NSInteger) axisID
                                       andError:(out NSError *_Nullable*_Nullable)error;


/** writeDigitalOutput
 * @brief                       write Digital IO
 * @param [in] iOIndex           the DIO id
 * @param [in] value             value to write AHWTEDIOValueLow,AHWTEDIOValueHigh, or AHWTEDIOValueToggle.
 * @param [out] error            nil = NO error, or error set.
 * @retval BOOL                 YES = sucess , NO = Error;
 *
 *
 */
- (BOOL)  writeDigitalOutput: (NSInteger) iOIndex
                    andValue: (ATDeviceIOValueType) value
                    andError: (out NSError *_Nullable*_Nullable) error;

/** readDigitalInput
 * @brief                       read Digital IO
 * @param [in] iOIndex           the DIO id
 * @param [out] error            nil = NO error, or error set.
 * @retval AHWTEDIOValueType    AHWTEDIOValueLow (0) or AHWTEDIOValueHigh (1).
 *
 *
 */
- (ATDeviceIOValueType) readDigitalInput: (NSInteger) iOIndex
                              andError: (out NSError *_Nullable*_Nullable) error;

-(id _Nullable ) attributesForKey:(ATDeviceFixtureKeys) key
                        andAxisID:(NSInteger) axisID
                         andError:(out NSError *_Nullable*_Nullable)error;

/**
 allAttributesForAxisID

 @param axisID AxisID
 @param error Set when there is an error
 @return an NSDictionary key:value   key is NSNumber and value is id
 */
-(NSDictionary <NSNumber*,id>* _Nullable ) allAttributesForAxisID:(NSInteger) axisID
                                           andError:(out NSError *_Nullable*_Nullable)error;


@end



@protocol ATDeviceMotionCapable < NSObject >


/**
 Go to an absolute position and set the parameters according to user
 (Blocking call)
 @param axisID nodeID
 @param targetPosition final step position motor has to go to
 @param velocity velcoity in rps
 @param acceleration acceleration in rps/s
 @param deceleration deceleration in rps/s
 @param error set if there was any error
 @return YES or NO  depending on all steps to move motor and go to final position succeded
 */
-(BOOL) moveAbsoluteForAxisID : (NSInteger) axisID
                     andTarget: (int32_t) targetPosition
                   andVelocity: (uint32_t) velocity
              andAcceleration : (uint32_t) acceleration
              andDeceleration : (uint32_t) deceleration
                      andError: (out NSError *_Nullable*_Nullable) error;

/**
 moveRelativeForAxisID (Blocking call)
 
 @param axisID nodeID
 @param targetPosition NUMBER OF STEPS to move from current position
 @param velocity in rps
 @param error set if there was any error
 @return YES or NO depending on whether motor was moved succesfuly
 */
-(BOOL) moveRelativeForAxisID : (NSInteger) axisID
                     andTarget: (int32_t) targetPosition
                   andVelocity: (uint32_t) velocity
                      andError: (out NSError *_Nullable*_Nullable) error;
/**
 Go to an relative position and set the parameters according to user
  (non Blocking call)
 @param axisID nodeID
 @param velocity velcoity in rps
 @param acceleration acceleration in rps/s
 @param deceleration deceleration in rps/s
 @param error set if there was any error
 @return NO or YES depending on all steps to move motor and go to final position succeded
 */
-(BOOL) moveVelocityForAxisID : (NSInteger) axisID
                   andVelocity: (uint32_t) velocity
              andAcceleration : (uint32_t) acceleration
              andDeceleration : (uint32_t) deceleration
                      andError: (out NSError *_Nullable*_Nullable) error;

/**
 stopVelocityForAxisID

 @param axisID nodeID
 @param error  error set if there was any error
 @return YES or NO
 */
-(BOOL) stopVelocityForAxisID: (NSInteger) axisID
                     andError: (out NSError *_Nullable*_Nullable) error;
/**
 Get the actual position or steps from motor
 
 @param axisID nodeID
 @param error set if there was any error in getting value
 @return returns a 4 byte position value
 */
-(int32_t) positionValueForAxisID : (NSInteger) axisID
                          andError:(out NSError *_Nullable*_Nullable)error;

/**
 Get the actual velocity from motor in rps
 
 @param axisID nodeID
 @param error set if there was any error in getting value
 @return returns a 4 byte velocity value
 */
-(int32_t) velocityValueForAxisID : (NSInteger) axisID
                          andError:(out NSError *_Nullable*_Nullable)error;

/**
 Stop motor irrespective of operation mode
 
 @param axisID nodeID
 @param error if any error during stopping motion
 @return YES or NO depening on success in stopping motor
 */
-(BOOL) stopMotionForAxisID: ( NSInteger) axisID
               andError: (out NSError *_Nullable*_Nullable)error;
/**
 Do a fixed homing method 19 according to driver
 
 @param axisID nodeID
 @param error set if there is any error
 @return YES or NO depening on success
 */
-(BOOL) doHomingForAxisID:(NSInteger) axisID
            andMethod:(ATDeviceHomingMethodType) method
                 andError:(out  NSError*_Nullable*_Nullable) error;
/**
 Do homing based on method chosen by user from ATDeviceHomingMethodType
 
 @param axisID nodeID
 @param error set if there is any error
 @return YES or NO depening on success
 */
-(BOOL) doHomingForAxisID:(NSInteger) axisID
             andError:(out NSError*_Nullable*_Nullable) error;
/**
Set all parameters according to user and do corresponding homing method 19

@param axisID nodeID
@param offset Number of steps to move after hitting sensor
@param homeVelocity speed to move to switch in rps
@param indexVelocity speed to move to zero position in rps
@param home_switch number of home switch sensors
@param acceleration acceleration value in rps/s
@param error set if there is any error
@return YES or NO depening on success
*/
- (BOOL)doHomingForAxisID:(NSInteger)axisID
                andOffset:(int32_t)offset
        andHomingVelocity:(uint32_t)homeVelocity
         andIndexVelocity:(uint32_t)indexVelocity
       andHomeSwitchInput:(uint8_t)home_switch
          andAcceleration:(uint32_t)acceleration
                 andError:(out NSError *_Nullable*_Nonnull)error;
/**
 Set all parameters according to user and do corresponding homing
 
 @param axisID nodeID
 @param offset Number of steps to move after hitting sensor
 @param homeVelocity speed to move to switch in rps
 @param indexVelocity speed to move to zero position in rps
 @param home_switch number of home switch sensors
 @param acceleration acceleration value in rps/s
 @param method check @sa ATDeviceHomingMethodType
 @param error set if there is any error
 @return YES or NO depening on success
 */
-(BOOL) doHomingForAxisID: (NSInteger)axisID
                andOffset: (int32_t) offset
        andHomingVelocity: (uint32_t) homeVelocity
         andIndexVelocity: (uint32_t) indexVelocity
      andHomeSwitchInput : (uint8_t) home_switch
          andAcceleration: (uint32_t) acceleration
                andMethod:(ATDeviceHomingMethodType)method
                 andError: (out NSError *_Nullable*_Nullable)error;

-(BOOL) stopHomingForAxisID: (NSInteger) axisID
                   andError:(out NSError *_Nullable*_Nullable)error;

/**
 enableOperationForAxisID
 
 @param axisID nodeID 0 for all devices
 @param modeID   ATDeviceCanOpenOperation        ATDeviceCanOpenOperationPosition = 0x01,
                                                 ATDeviceCanOpenOperationVelocity = 0x03,
                                                 ATDeviceCanOpenOperationHoming   = 0x06,
 @param error set if there is any error
 @return YES or NO depening on success
 */
-(BOOL) enableOperationForAxisID: (NSInteger) axisID andOperation:(NSUInteger) modeID
                        andError: (out NSError *_Nullable*_Nullable)error;
/**
 disable all operating modes for motor by changing control word, moves the motor position a little bit.
 
 @param axisID nodeID
 @param error set if there is any error
 @return YES or NO depening on success
 */
-(BOOL) disableOperationForAxisID: (NSInteger) axisID
                         andError:(out NSError *_Nullable*_Nullable)error;


/**
 Send a custom command to canopen drive to get information from drive
 
 @param axisID nodeID
 @param index Index value used based on CanOpen protocol
 @param subIndex subIndex value used based on CanOpen protocol
 @param data 4 byte data returned
 @param error  set if there was any error in getting value
 @return yes if command succeeds else no
 */
-(BOOL) customUploadCommandForAxisID:(NSInteger) axisID andIndex:(uint16_t)index andSubIndex:(uint8_t) subIndex andData:(uint8_t *_Nullable)data andError: (out NSError *_Nullable*_Nullable)error;

/**
 Returns drive errors for corresponding nodeid @sa ATDFixtureDriveErrors
 
 @param axisID nodeID
 @param error set if there was any error in getting drive errors value
 @return check @sa ATDFixtureDriveErrors
 */
- (ATDFixtureDriveErrors*_Nullable) driveErrorsForAxisID: (NSInteger) axisID
                                                andError: (out NSError *_Nullable*_Nullable)error;

/**
 Returns drive status for corresponding nodeID
 
 @param axisID nodeID
 @param error set if there was any error in getting drive status value
 @return check @sa ATDFixtureDriveStatus
 */
- (ATDFixtureDriveStatus*_Nullable) driveStatusForAxisID: (NSInteger) axisID
                                                andError: (out NSError *_Nullable*_Nullable)error;
/**
 read digital inputs from drive
 
 @param axisID nodeID
 @param error Set if any error read i/p from drive
 @return check @sa ATDFixtureDriveInputs - 1 is close, 0 is open
 */
- (ATDFixtureDriveInputs*_Nullable) readDriveInputsForAxisID: (NSInteger) axisID
                                                    andError: (out NSError *_Nullable*_Nullable)error;
/**
 Returns drive output status
 
 @param axisID nodeID
 @param error Set if any error when reading o/p from drive
 @return check @sa ATDFixtureDriveOutputs - 1 is close, 0 is open
 */
- (ATDFixtureDriveOutputs*_Nullable) readDriveOutputsForAxisID: (NSInteger) axisID
                                                      andError: (out NSError *_Nullable*_Nullable)error;
/**
 Control 4 outputs attached to driver to open/close
 
 @param axisID nodeID
 @param driveOutputs check @sa ATDFixtureDriveOutputs - set value to 1 for close, 0 for open
 @param error set if any issue changing output value
 @return YES if operation was succesful else NO
 */
- (BOOL) writeDriveOutputsForAxisID: (NSInteger) axisID withOutputValue:(ATDFixtureDriveOutputs *_Nullable) driveOutputs
                           andError: (out NSError *_Nullable*_Nullable)error;

//@property ATDFixtureDriveErrors * _Nullable motorErrors;
@end




