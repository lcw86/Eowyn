//
//  ATDeviceTitaniumPrivate.h
//  ATDeviceElements
//
//  Created by Yuanyuan Tian on 4/22/19.
//  Copyright © 2019 htwe. All rights reserved.
//

#ifndef ATDeviceTitaniumPrivate_h
#define ATDeviceTitaniumPrivate_h

typedef NS_ENUM(uint8_t,ATDeviceDPTxPrivatePortType){
    ATDeviceDPOverDrive = 2,//option to enable Display Pattern OverDrive. this will genrate pattern on both DPTx port on titanium and send DP out from DPTx0 (TBTC).
    ATDeviceDPTxMultiModePatternGen,  //option 3 to enable Display Pattern multi mode + HDCP2 + 4K YCbCr
    ATDeviceDPTxLinkResetPriorPatternGen//reset pattern gen parameter, HDCP, and DP link train before send pattern.
};

#endif /* ATDeviceTitaniumPrivate_h */
