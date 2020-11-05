//
//  ATDeviceMolybdenum.h
//  ATDeviceElements
//
//  Created by Arjun Agaram Mangad on 6/24/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <ATDeviceElements/ATDeviceElements.h>
#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>

typedef NS_ENUM(uint8_t,ATDMolybdenumPCIEGPIOIndex){
    ATDMolybdenumPCIEGPIOPresent_L,
    ATDMolybdenumPCIEGPIOPresent1_L,
    ATDMolybdenumPCIEGPIOPresent4_L,
    ATDMolybdenumPCIEGPIOPresent8_L,
    ATDMolybdenumPCIEGPIOPresent16_L,
    ATDMolybdenumPCIEGPIOPCIE_TCK,
    ATDMolybdenumPCIEGPIOPCIE_TDI,
    ATDMolybdenumPCIEGPIOPCIE_TDO,
    ATDMolybdenumPCIEGPIOPCIE_TMS,
    ATDMolybdenumPCIEGPIOPCIE_TRST_L,
    ATDMolybdenumPCIEGPIOPCIE_WAKE_L,
    ATDMolybdenumPCIEGPIOPCIE_SMCLK,
    ATDMolybdenumPCIEGPIOPCIE_SMDAT,
    ATDMolybdenumPCIEGPIOPCIE_CLKREQ_L,
    ATDMolybdenumPCIEGPIOPCIE_PERST_3V3_L
};

typedef NS_ENUM(uint8_t,ATDMolybdenumSPCIEGPIOIndex){
    ATDMolybdenumSPCIEGPIOFPGA_LED_R3,
    ATDMolybdenumSPCIEGPIOSPCIE_PRESENT_L,
    ATDMolybdenumSPCIEGPIOPCIE_CFG,
    ATDMolybdenumSPCIEGPIOTBT_A_USB_PWR_EN,
    ATDMolybdenumSPCIEGPIOTBT_A_CIO_PWR_EN,
    ATDMolybdenumSPCIEGPIOTBT_A_PLUG_EVENT_L,
    ATDMolybdenumSPCIEGPIOTBT_A_POC_RST,
    ATDMolybdenumSPCIEGPIOTBT_PWR_EN,
    ATDMolybdenumSPCIEGPIOPP1V8_SPCIE,
    ATDMolybdenumSPCIEGPIOJTAG_TBT_A_TMS,
    ATDMolybdenumSPCIEGPIOJTAG_TBT_B_TMS,
    ATDMolybdenumSPCIEGPIOPM_SLP_S3_L,
    ATDMolybdenumSPCIEGPIOPM_RSMRST_L,
    ATDMolybdenumSPCIEGPIOTBT_B_USB_PWR_EN,
    ATDMolybdenumSPCIEGPIOTBT_B_CIO_PWR_EN,
    ATDMolybdenumSPCIEGPIOTBT_B_PLUG_EVENT_L,
    ATDMolybdenumSPCIEGPIOTBT_B_POC_RESET,
    ATDMolybdenumSPCIEGPIOTBT_WAKE_3V3_L,
    ATDMolybdenumSPCIEGPIOJTAG_ISP_TCK,
    ATDMolybdenumSPCIEGPIOJTAG_ISP_TDI,
    ATDMolybdenumSPCIEGPIOJTAG_ISP_TDO,
    ATDMolybdenumSPCIEGPIOHDMI_RST_L,
    ATDMolybdenumSPCIEGPIOGPU_THROTTLE_L,
    ATDMolybdenumSPCIEGPIOGPU_SELF_THROTTLE_L,
    ATDMolybdenumSPCIEGPIOGPU_THRMTRP,
    ATDMolybdenumSPCIEGPIOGPU_I2C_SDA,
    ATDMolybdenumSPCIEGPIOGPU_I2C_SCL,
    ATDMolybdenumSPCIEGPIOGPU_I2C_INT_L,
    ATDMolybdenumSPCIEGPIOI2C_SNS_3V3_SDA,
    ATDMolybdenumSPCIEGPIOI2C_SNS_3V3_SCL,
    ATDMolybdenumSPCIEGPIOGCON_INT_L,
    ATDMolybdenumSPCIEGPIOUC_FPGA_GPIO7,
    ATDMolybdenumSPCIEGPIODP_ML0_MUX_FLIP_FPGA,
    ATDMolybdenumSPCIEGPIODP_ML1_MUX_FLIP_FPGA,
    ATDMolybdenumSPCIEGPIODP_ML2_MUX_FLIP_FPGA,
    ATDMolybdenumSPCIEGPIODP_ML3_MUX_FLIP_FPGA,
    ATDMolybdenumSPCIEGPIORETIMER1_PD_L,
    ATDMolybdenumSPCIEGPIORETIMER2_PD_L,
    ATDMolybdenumSPCIEGPIORETIMER3_PD_L,
    ATDMolybdenumSPCIEGPIORETIMER4_PD_L
};
@interface ATDeviceMolybdenum : ATDeviceElement

/**
 Drive PCIE output to either low or high

 @param ioValue 32 bit value , set bits to drive molybdenum gpio pins to high. @sa ATDMolybdenumPCIEGPIOIndex
 @param aError any error when driving pins low/high
 @return Yes if operation was success
 */
-(BOOL) drivePCIEGPIOIOValue:(uint32_t)ioValue  andError:(NSError **)aError;


/**
 Set PCIE gpio pins to be output/input

 @param ioValue 32 bit value , set bits to make molybdenum gpio pins to output, otherwise input. @sa ATDMolybdenumPCIEGPIOIndex
 @param aError any error when setting pins to input/output
 @return Yes if operation was success
 */
-(BOOL) PCIEGPIOToValue:(uint32_t)ioValue       andError:(NSError **)aError;


/**
 Returns the status of current PCIE GPIO pins

 @param actualValue 64 bit value saying whether pins are asserted if bit is set, otherwise deasserted.@sa ATDMolybdenumPCIEGPIOIndex
 @param aError any error when getting status
 @return Yes if operation was success
 */
-(BOOL) PCIEGPIOValue:(uint64_t*)actualValue    andError:(NSError **)aError;

/**
 Drive SPCIE output to either low or high

 @param ioValue ioValue 32 bit value , set bits to drive copper gpio pins to high. @sa ATDMolybdenumSPCIEGPIOIndex
 @param aError any error when driving pins low/high
 @return Yes if operation was success
 */
-(BOOL) driveSPCIEGPIOIOValue:(uint64_t)ioValue andError:(NSError **)aError;


/**
  Set SPCIE gpio pins to be output/input

 @param ioValue 32 bit value , set bits to make copper gpio pins to output, otherwise input. @sa ATDMolybdenumSPCIEGPIOIndex
 @param aError any error when setting pins to i/p o/p
 @return Yes if operation was success
 */
-(BOOL) SPCIEGPIOToValue:(uint64_t)ioValue      andError:(NSError **)aError;

/**
 Returns the status of current SPCIE GPIO pins
 
 @param actualValue 64 bit value saying whether pins are asserted if bit is set, otherwise deasserted.@sa ATDMolybdenumSPCIEGPIOIndex
 @param aError any error when getting status
 @return Yes if operation was success
 */
-(BOOL) SPCIEGPIOValue:(uint64_t*)actualValue   andError:(NSError **)aError;


/**
 Start aux load in milli volts for passed number of samples

 @param samples Number of samples used to calculate drop
 @param aError any error when doing aux load
 @return Voltage after running aux load for passed number of samples at a constant current of 3.3A
 */
-(NSNumber *) auxLoadinMilliVoltsForNumberOfSamples:(uint32_t) samples
                                          withError:(NSError **)aError;

/**
 Disable aux load ie the constant current of 3.3 Amps

 @param aError any error when disabling aux load
 @return Yes if operation was success
 */
-(BOOL) disableAuxLoadWithError:(NSError **)aError;
/**
 Enable aux load ie the constant current of 3.3 Amps
 
 @param aError any error when enabling aux load
 @return Yes if operation was success
 */
-(BOOL) enableAuxLoadWithError:(NSError **)aError;

-(BOOL) drivePCIEPresentPinsGateWithpresent8PinState:(BOOL)present8PinState andpresent16PinState:(BOOL) present16PinState withError:(out NSError **)aError;

@end
