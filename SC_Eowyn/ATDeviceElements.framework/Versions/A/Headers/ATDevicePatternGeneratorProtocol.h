//
//  ATDevicePatternGeneratorProtocol.h
//  ATDeviceElements
//
//  Created by sai on 9/20/18.
//  Copyright © 2018 htwe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ATDeviceElements/ATDeviceParameters.h>



typedef NS_ENUM(uint32_t, ATDevicePatternGenType) {    
    ATDPatternGenLoopBack                  = 0,
    ATDPatternGenMem,
    ATDPatternGenSimple,
    ATDPatternGenDSC,
    ATDPatternGenDPtoHDMI
};



@protocol ATDevicePatternGeneratorCapable < NSObject >


/**
 generate Default Pattern

 @param dpTxPort    ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable      YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive     Horizontal Active pixel
 @param hTotal      Horizontal Total pixel
 @param vActive     Vertical Active pixel
 @param vTotal      Vertical Total pixel
 @param refreshRate refresh rate 50hz 60hz
 @param aError      error is set if there was an error generating pattern
 @return            yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
                     andError: (NSError**) aError;

/**
 generate Default Pattern

 @param dpTxPort    ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable      YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive     Horizontal Active pixel
 @param hTotal      Horizontal Total pixel
 @param vActive     Vertical Active pixel
 @param vTotal      Vertical Total pixel
 @param refreshRate refresh rate 50hz 60hz
 @param format      0 = RGB; 1 = YCbCr 4:4:4; 2 = YCbCr 4:2:2, 3 = YCbCr 4:2:0
 @param bpc         0 = 6bpc; 1 = 8 bpc; 2 = 10 bpc; 3 = 12 bpc; 4 = 16 bpc
 @param range       0 = VESA; 1 = CEA
 @param colorimetry 0 = BT601-5; 1 = BT709-5;
 @param useVscSDP   0 = use MISC0; 1 = use VSC_SDP
 @param aError      error is set if there was an error generating pattern
 @return            yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
               andColorFormat: (ATDeviceColorSpaceFormat) format
           andBitPerComponent: (ATDeviceColorSpaceBPC) bpc
                     andRange: (ATDeviceColorSpaceRange) range
               andColorimetry: (ATDeviceColorSpaceColorimetry) colorimetry
                    useVscSDP: (ATDeviceColorSpaceUseVscSDP) useVscSDP
                     andError: (NSError**) aError;


/**
 generate Custom Pattern

 @param dpTxPort    ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable      YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive     Horizontal Active pixel
 @param hTotal      Horizontal total pixel
 @param vActive     Vertical Active pixel
 @param vTotal      Vertical Total pixel
 @param refreshRate refresh rate 50hz 60hz
 @param colorBars   The Color bar object that include the 16 bars
 @param aError      error is set if there was an error generating pattern
 @return            yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
           andCustomColorBars: (ATDeviceColor16Bars*) colorBars
                     andError: (NSError**) aError;


/**
 generate  Pattern with the same color

 @param dpTxPort    ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable      YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive     Horizontal Active pixel
 @param hTotal      Horizontal total pixel
 @param vActive     Vertical Active pixel
 @param vTotal      Vertical Total pixel
 @param refreshRate refresh rate 50hz 60hz
 @param color       The color to set for all 16 bars
 @param aError      error is set if there was an error generating pattern
 @return            yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
                     andColor: (ATDeviceColors) color
                     andError: (NSError**) aError;

/**
 generate  Pattern with the same color
 
 @param dpTxPort    ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable      YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive     Horizontal Active pixel
 @param hTotal      Horizontal total pixel
 @param vActive     Vertical Active pixel
 @param vTotal      Vertical Total pixel
 @param refreshRate refresh rate 50hz 60hz
 @param patternType Pattern Gen format type
 @param aError      error is set if there was an error generating pattern
 @return            yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
               andPatternType: (ATDevicePatternGenType) patternType
               andDPOverDrive: (BOOL)dpod
                     andError: (NSError**) aError;

/**
 generate Pattern with the advanced options
 
 @param dpTxPort        ATDeviceDPTxPort0 or ATDeviceDPTxPort1
 @param enable          YES to enable the Pattern generation  and NO to disable the pattern.
 @param hActive         Horizontal Active pixel
 @param hTotal          Horizontal total pixel
 @param vActive         Vertical Active pixel
 @param vTotal          Vertical Total pixel
 @param refreshRate     refresh rate 50hz 60hz
 @param customIndex     customIndex - 0 = built-in color bars, 1 = custom color bars (fill in color bar 0-15 fields), 2 = solid white, 3 = solid silver, 4 = solid gray, 5 = solid black, 6 = solid yellow, 7 = solid fushsia, 8 = solid red, 9 = solid maroon, 10 = solid lime, 11 = solid olive, 12 = solid green, 13 = solid purple, 14 = solid aqua, 15 = solid teal, 16 = solid blue, 17 = solid navy
 @param format          Color space format.
 @param bpc             bit per channel.
 @param range           color space range
 @param colorimetry     color space colorimetry
 @param patternType     pattern generation type
 @param enableHSyncPolarity     enable HSync Polarity
 @param enableVSyncPolarity     enable VSync Polarity
 @param hSyncStart      hSync start
 @param vSyncStart      vSync start
 @param hSyncCount      hSync count
 @param vSyncCount      vSync count
 @param enableDPOD      enable DP overdrive. Once enabled, DP stream will output from DPTx0 ONLY.
 @param colorbar0       desired color for bar 0 (when customIndex = 1)
 @param colorbar1       desired color for bar 1 (when customIndex = 1)
 @param colorbar2       desired color for bar 2 (when customIndex = 1)
 @param colorbar3       desired color for bar 3 (when customIndex = 1)
 @param colorbar4       desired color for bar 4 (when customIndex = 1)
 @param colorbar5       desired color for bar 5 (when customIndex = 1)
 @param colorbar6       desired color for bar 6 (when customIndex = 1)
 @param colorbar7       desired color for bar 7 (when customIndex = 1)
 @param colorbar8       desired color for bar 8 (when customIndex = 1)
 @param colorbar9       desired color for bar 9 (when customIndex = 1)
 @param colorbar10      desired color for bar 10 (when customIndex = 1)
 @param colorbar11      desired color for bar 11 (when customIndex = 1)
 @param colorbar12      desired color for bar 12 (when customIndex = 1)
 @param colorbar13      desired color for bar 13 (when customIndex = 1)
 @param colorbar14      desired color for bar 14 (when customIndex = 1)
 @param colorbar15      desired color for bar 15 (when customIndex = 1)
 @param aError      error is set if there was an error generating pattern
 @return        yes if successfully generate pattern
 */
-(BOOL) generatePatternOnPort: (ATDeviceDPTxPortType) dpTxPort
                    andEnable: (BOOL) enable
          andHorizontalActive: (NSInteger) hActive
           andHorizontalTotal: (NSInteger) hTotal
            andVerticalActive: (NSInteger) vActive
             andVerticalTotal: (NSInteger) vTotal
               andRefreshRate: (NSInteger) refreshRate
          andUseCustomPattern: (NSInteger) customIndex
               andColorFormat: (ATDeviceColorSpaceFormat) format
           andBitPerComponent: (ATDeviceColorSpaceBPC) bpc
                     andRange: (ATDeviceColorSpaceRange) range
               andColorimetry: (ATDeviceColorSpaceColorimetry) colorimetry
               andPatternType: (ATDevicePatternGenType) patternType
             andHSyncPolarity: (BOOL) enableHSyncPolarity
             andVSyncPolarity: (BOOL) enableVSyncPolarity
                andHSyncStart: (NSInteger) hSyncStart
                andVSyncStart: (NSInteger) vSyncStart
                andHSyncCount: (NSInteger) hSyncCount
                andVSyncCount: (NSInteger) vSyncCount
               andDPOverDrive: (BOOL) enableDPOD
                 andColorbar0: (ATDeviceColors) colorbar0
                 andColorbar1: (ATDeviceColors) colorbar1
                 andColorbar2: (ATDeviceColors) colorbar2
                 andColorbar3: (ATDeviceColors) colorbar3
                 andColorbar4: (ATDeviceColors) colorbar4
                 andColorbar5: (ATDeviceColors) colorbar5
                 andColorbar6: (ATDeviceColors) colorbar6
                 andColorbar7: (ATDeviceColors) colorbar7
                 andColorbar8: (ATDeviceColors) colorbar8
                 andColorbar9: (ATDeviceColors) colorbar9
                andColorbar10: (ATDeviceColors) colorbar10
                andColorbar11: (ATDeviceColors) colorbar11
                andColorbar12: (ATDeviceColors) colorbar12
                andColorbar13: (ATDeviceColors) colorbar13
                andColorbar14: (ATDeviceColors) colorbar14
                andColorbar15: (ATDeviceColors) colorbar15
                     andError:(out NSError**) aError;

@end
