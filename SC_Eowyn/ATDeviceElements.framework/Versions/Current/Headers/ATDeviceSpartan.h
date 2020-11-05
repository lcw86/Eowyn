//
//  ATDevicePotassium.h
//  ATDeviceElements
//
//  Created by Sai  on 11/9/16.
//  Copyright © 2016 htwe. All rights reserved.
//

#import <ATDeviceElements/ATDeviceElements.h>
#import <ATDeviceElements/ATDeviceSpartanConfig.h>

#define kATDSpartanProductID    0x1636
#define kATDSpartanBCDeviceID   0x000F

typedef NS_ENUM(uint8_t, ATDSpartanPort)
{
    ATDSpartanTargetPort = 0,
    ATDSpartanChargePort = 1
};

typedef NS_ENUM(uint8_t, ATDSpartanPinPair)
{
    ATDSpartanMissionUSB    = 0,
    ATDSpartanDebugUSB      = 1,
    ATDSpartanSBU           = 2
};

typedef NS_ENUM(uint8_t, ATDSpartanModule)
{
    ATDSpartanModuleUART    = 1,
    ATDSpartanModuleSWD     = 2,
    ATDSpartanModuleDock    = 4,
    ATDSpartanModuleBanana  = 8
};

#define kATDSpartanRegisterCOMDescriptor        64
#define kATDSpartanRegisterActiveConfig         65
#define kATDSpartanRegisterCCConnection         70
#define kATDSpartanRegisterPDState              71
#define kATDSpartanRegisterDPMState             72
#define kATDSpartanRegisterDataPinState         73
#define kATDSpartanRegisterActionState          74
#define kATDSpartanRegisterBootloaderVersion    79
#define kATDSpartanRegisterModuleConfig         80
#define kATDSpartanRegisterDiscoveredDockChannels   81
#define kATDSpartanRegisterMUXSettings          82
#define kATDSpartanRegisterPowerStatus          83
#define kATDSpartanRegisterDetectedCable        84
#define kATDSpartanRegisterTargetPDStatus       85
#define kATDSpartanRegisterChargePDStatus       86
#define kATDSpartanRegisterTargetOfferedPDOs    87
#define kATDSpartanRegisterChargeOfferedPDOs    88
#define kATDSpartanRegisterTargetVBusVoltage    89
#define kATDSpartanRegisterTargetVBusCurrent    90
#define kATDSpartanRegisterChargeVBusVoltage    91
#define kATDSpartanRegisterTargetVConnVoltage   92
#define kATDSpartanRegisterTargetVConnCurrent   93
#define kATDSpartanRegisterExecutionAddress     100

typedef NS_ENUM(uint8_t, ATDSpartanLED)
{
    ATDSpartanLEDRed    = 0x01,
    ATDSpartanLEDYellow = 0x02,
    ATDSpartanLEDGreen  = 0x04,
};

#define kATDSpartanLEDOff   0
#define kATDSpartanLEDOn    0xFFFF

@interface ATDeviceSpartan : ATDeviceElement


/**
 Set the verbosity level of the Debug serial channel on Spartan
 
 0 - No Debug
 1 - Board events, Commands
 2 - State Changes
 3 - PD Events
 4 - ROM Table Explore
 5 - Unused
 6 - PD Messages
 7 - SWD, Hippo

 @param level Debug level
 @param save If YES, save as persistant boot debug level
 @param error Error on failure
 @return YES on success
 */
-(BOOL) setDebugLevel : (uint8_t)level
      savingAsDefault : (BOOL)save
            withError : (NSError**)error;

/**
 Get string describing the last 128 state changes
 
 @note The state change buffer does not persist across power cycles.

 @param error Error on failure
 @return On success, the string.  Otherwise nil.
 */
- (NSString*) stateChangeStringWithError : (NSError**)error;

/**
 Get string describing the current state of any FIFO on Spartan
 
 @param error Error on failure
 @return On success, the string.  Otherwise nil.
 */
- (NSString*) fifoInfoStringWithError : (NSError**)error;

/**
 Get the first 256 bytes in a FIFO
 
 @note The data is not removed from the FIFO

 @param fifo The index as to which FIFO to preview
 @param error Error on failure
 @return Data in the FIFO on success, otherwise nil
 */
- (NSData*) previewFIFO : (uint8_t)fifo
              withError : (NSError**)error;

/**
 Update the Spartan configuration
 
 This will update any properties that can be changed immediately. Other properties will change when available.

 @param config Configuration to upload
 @param save If YES, save as default, POR configuration
 @param error Error on failure
 @return YES on success
 */
- (BOOL) updateConfiguration : (ATDeviceSpartanConfig*)config
            andSaveAsDefault : (BOOL)save
                   withError : (NSError**)error;

/**
 Update the Spartan configuration
 
This will update any properties that can be changed immediately. Other properties will change when available.

 @param path Path to JSON file containing configuration
 @param save If YES, save as default, POR configuration
 @param error Error on failure
 @return YES on success
 */
- (BOOL) updateConfigurationFromFile : (NSString*)path
                    andSaveAsDefault : (BOOL)save
                           withError : (NSError**)error;

/**
 Control the RYG LEDs on Spartan

 @param ledMask A bitwise-OR of ATDSpartanLED values. Determines which LEDs will be affected.
 @param duration Period of blinking in milliseconds.  If kATDSpartanLEDOff, turn selected LEDs off.  If kATDSpartanLEDOn, turn selected LEDs on
 @param clear If YES, turn off all LEDs before applying new change
 @param error Error on failure
 @return YES on success
 */
- (BOOL)        controlLEDs : (uint8_t)ledMask
    withMillisecondDuration : (uint16_t)duration
            turningOffFirst : (BOOL)clear
                  withError : (NSError**)error;

/**
 Tell selected port to remove CC resistors for a period of time to emulate a physical disconnect on that port

 @param port The port on which the disconnect should be emulated
 @param duration The duration of time, in milliseconds, that the port should keep CC resistors removed before reapplying them
 @param error Error on failure
 @return YES on success
 */
- (BOOL) emulateDisconnectOnPort : (ATDSpartanPort) port
          forMillisecondDuration : (uint16_t) duration
                       withError : (NSError**) error;

/**
 Set the name that will appear in MacOS when using the AppleTestDevice-IOUSBHostFamily kext

 @param name Name can be up to 32 bytes long, but will be truncated for the -Debug, and -UART ports
 @param error Error on failure
 @return YES on success
 */
- (BOOL) changeSerialPortName : (NSString*)name
                    withError : (NSError**)error;

/**
 Enable or disable Apple Debug Mode on the specified pin pair per the active configuration

 @param enable Whether to enable or disable Apple Debug Mode
 @param pins Which pins to act on
 @param error Error on failure
 @return YES on success
 */
- (BOOL) enableAppleDebugMode : (BOOL)enable
                    onPinPair : (ATDSpartanPinPair)pins
                    withError : (NSError**)error;



/**
 Send an action to the specified target over Apple Debug VDM
 
 @param action Action to send (0x8000 - Reset, 0x8001 - ForceDFU, 0x8002 - ForceDiags)
 @param target Target that should receive the action
 @param force If YES, don't try to GetDCT or EDC, just send action
 @param timeout Time in milliseconds before returning
 @param error Error on failure
 @return YES on success
 */
- (BOOL) sendAppleDebugAction : (uint16_t)action
                     toTarget : (uint8_t)target
                      byForce : (BOOL)force
       withMillisecondTimeout : (uint16_t)timeout
                    withError : (NSError**)error;


/**
 Send ForceDFU action to the attached SoC

 @param error Error on failure
 @return YES on success
 */
- (BOOL) sendForceDFUWithError : (NSError**)error;


/**
 Send Reset action to the attached PMU

 @param error Error on failure
 @return YES on success
 */
- (BOOL) resetTargetWithError : (NSError**)error;


/**
 Use the onboard banana circuit to send keystrokes to the target
 
 @note Target must be connected to Spartan and Spartan must be in the UFP role

 @param keycodes Array of up to 5 HID keycodes to type at once
 @param modifiers Bitwise OR of modifier keys
 @param specials Bitwise OR of special keys
 @param duration Duration to hold the keystrokes in milliseconds.  If 0, hold indefinitely
 @param error Error on failure
 @return YES on success
 */
- (BOOL) bananaTypeKeys : (NSArray<NSNumber*>*)keycodes
       withModifierKeys : (uint8_t)modifiers
        withSpecialKeys : (uint8_t)specials
            forDuration : (uint16_t)duration
              withError : (NSError**)error;


/**
 Tell the onboard banana circuit to release all keystrokes

 @param error Error on failure
 @return YES on success
 */
- (BOOL) bananaReleaseAllKeysWithError : (out NSError**)error;


/**
 Request Spartan to issue a Power Role Swap to the target to become the power sink.
 
 @note If Spartan is already the power sink, return immediately

 @param error Error on failure
 @return YES on success
 */
- (BOOL) powerRoleSwapToSinkWithError : (NSError**)error;


/**
 Request Spartan to issue a Power Role Swap to the target to become the power source.
 
 @note If Spartan is already the power source, return immediately
 
 @param error Error on failure
 @return YES on success
 */
- (BOOL) powerRoleSwapToSourceWithError : (NSError**)error;


/**
 Request Spartan to issue a Data Role Swap to the target to become the UFP.
 
 @note If Spartan is already the UFP, return immediately
 
 @param error Error on failure
 @return YES on success
 */
- (BOOL) dataRoleSwapToUfpWithError : (NSError**)error;


/**
 Request Spartan to issue a Data Role Swap to the target to become the DFP.
 
 @note If Spartan is already the DFP, return immediately
 
 @param error Error on failure
 @return YES on success
 */
- (BOOL) dataRoleSwapToDfpWithError : (NSError**)error;

/**
 Get the serial number of the attached Neutron

 @param error Error on failure
 @return Serial Number on Success, nil on failure
 */
- (NSString*) neutronSerialNumberWithError : (NSError**)error;

/**
 Get the current cycle count of the attached Neutron

 @param error Error on failure
 @return Count on success, nil on failure
 */
- (NSNumber*) neutronCycleCountWithError : (NSError**)error;

/**
 Increment the attached Neutron cycle count by 1

 @param error Error on failure
 @return Yes on success
 */
- (BOOL) incrementNeutronCycleCountWithError : (NSError**)error;

/**
 Control the LED of the attached Neutron

 @param color What color to set LED to. Can be kCombinedDCSDColorOff, kCombinedDCSDColorRed, kCombinedDCSDColorYellow, kCombinedDCSDColorGreen
 @param mode What mode to set LED to. Can be kCombinedDCSDModeOff, kCombinedDCSDModeOn, kCombinedDCSDModeSlow, kCombinedDCSDModeFast
 @param error Error on failure
 @return Yes on success
 */
- (BOOL) setNeutronLEDtoColor : (uint8_t)color
                     withMode : (uint8_t)mode
                    withError : (NSError**)error;


/**
 Reset Spartan's USB Hub
 
 This command will scheudule a Hub reset for 300ms after the command returns.
 When the hub resets, the Spartan USB device will drop, so the application code needs to handle that.

 @param error Error on failure
 @return Yes on success
 */
- (BOOL) resetHubWithError : (NSError**)error;

/**
 Reads a register from the target's host interface

 @param address Address to read
 @param error Error on failure
 @return Register data on success, otherwise nil
 */
- (NSData*) readTargetHostInterfaceRegister : (uint8_t)address
                                  withError : (NSError**)error;



/**
 Get the Main Loop Tcl Script written in the EEPROM

 @param offset Returns offset into the User Page where the script is located
 @param error Error on failure
 @return Script, otherwise nil
 */
-(NSString*) mainTclScriptAtOffset : (uint16_t*)offset
                         withError : (NSError**)error;

/**
 Get the Boot Tcl Script written in the EEPROM
 
 @param offset Returns offset into the User Page where the script is located
 @param error Error on failure
 @return Script, otherwise nil
 */
-(NSString*) bootTclScriptAtOffset : (uint16_t*)offset
                         withError : (NSError**)error;


/**
 Write the provided Tcl Script to the User Page at the specified offset and set it to run in the main loop

 @param script Tcl Script to execute
 @param offset Offset into the User Page where the script would be stored
 @param error Error on failure
 @return Yes on success
 */
-(BOOL) writeMainTclScript : (NSString*)script
                  toOffset : (uint16_t)offset
                 withError : (NSError**)error;

/**
 Write the provided Tcl Script to the User Page at the specified offset and set it to run on boot
 
 @param script Tcl Script to execute
 @param offset Offset into the User Page where the script would be stored
 @param error Error on failure
 @return Yes on success
 */
-(BOOL) writeBootTclScript : (NSString*)script
                  toOffset : (uint16_t)offset
                 withError : (NSError**)error;


/**
 Unschedule the main loop Tcl Script

 @param error Error on failure
 @return Yes on success
 */
-(BOOL) clearMainTclScriptWithError : (NSError**)error;

/**
 Unschedule the boot Tcl Script
 
 @param error Error on failure
 @return Yes on success
 */
-(BOOL) clearBootTclScriptWithError : (NSError**)error;

@end
