//
//  ATDeviceElementsCommon.h
//  ATDeviceElements
//
//  Created by Sai  on 3/15/17.
//  Copyright © 2017 htwe. All rights reserved.
//

#ifndef ATDeviceElementsCommon_h
#define ATDeviceElementsCommon_h

typedef NS_ENUM(uint32_t, ATDeviceElementsID) {
    ATDevice_INVALID_ID         = 0,
    ATDevice_PALLADIUM_ID       = 0xD0010001,
    ATDevice_TITANIUM_ID        = 0xD0010002,
    ATDevice_SPADE_ID           = 0xD0020001,
    ATDevice_XENON_ID           = 0xD0020002,
    ATDevice_POTASSIUM_ID       = 0xD0020003,
    ATDevice_CAESIUM_ID         = 0xD0020005,
    ATDevice_POTASSIUM_IMU_ID   = 0xD0020006,
    ATDevice_SPARTAN_ID         = 0xD0020009,
    ATDevice_GALLIUM_ID         = 0xD0030001,
    ATDevice_RADON_ID           = 0xD0040001,
    ATDevice_DUST_ID            = 0xD0070001,
    ATDevice_MIRAGE_ID          = 0xD0070002,
    ATDevice_AZTEC_ID           = 0xD0070004,
    ATDevice_MOLYBDENUM_ID      = 0xD0070007,
    ATDevice_ASTATINE_ID        = 0xD0070008,
    ATDevice_CARBON_ID          = 0xD0080001,
    ATDevice_ZINC_ID            = 0xD0080002,
    ATDevice_C3PO_ID            = 0xD0090001,
    ATDevice_GIMLI_ID           = 0xD0090002,
    ATDevice_IODINE_ID          = 0xD0090003,
    ATDevice_LEGOLAS_ID         = 0xD0090004,
    ATDevice_MANTIS_ID          = 0xD00A0001,
    ATDevice_RAVEN_ID           = 0xD00A0003,
    ATDevice_NIBBLER_ID         = 0xD00A0004,
    ATDevice_IZZY_ID            = 0xD00A0005,
    ATDevice_BROMINE_ID         = 0xD00B0001,
  
};

typedef NS_ENUM(uint32_t, ATDeviceBCD) {
    ATDeviceInvalidBCD          = 0x0000,
    ATDevicePotassiumBCD        = 0x0001,
    ATDeviceSodiumBCD           = 0x0002,
    ATDeviceCarbonBCD           = 0x0003,
    ATDeviceCaesiumBCD          = 0x0004,
    ATDeviceTitaniumBCD         = 0x0005,
    ATDeviceC3PO_BCD            = 0x0006,
    ATDeviceMantisBCD           = 0x0007,
    ATDeviceZincBCD             = 0x0008,
    ATDeviceWolfBCD             = 0x0009,
    ATDeviceIodineBCD           = 0x000A,
    ATDeviceMolybdenumBCD       = 0x000B,
    ATDeviceGimliBCD            = 0x000C,
    ATDeviceRavenBCD            = 0x000D,
    ATDeviceDalmatianBCD        = 0x000E,
    ATDeviceSpartanBCD          = 0x000F,
    ATDeviceLegolasBCD          = 0x0010,
    ATDeviceNibblerBCD          = 0x0011,
    ATDeviceAstatineBCD         = 0x0012,
    ATDeviceBromineBCD          = 0x0013,
    ATDeviceIzzyBCD             = 0x0016,
};


#endif /* ATDeviceElementsCommon_h */
