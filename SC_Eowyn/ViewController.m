//
//  ViewController.m
//  SC_Eowyn
//
//  Created by ciwei luo on 2020/3/31.
//  Copyright © 2020 ciwei luo. All rights reserved.
//
#import <CWGeneralManager/MyEexception.h>
#import "ViewController.h"
#import "Eowyn.h"
#import "ShowingLogVC.h"
#import <ATDeviceElements/ATDeviceElements.h>
#import <CWGeneralManager/NSString+Extension.h>
#import <CWGeneralManager/CWFileManager.h>

#import <pthread.h>
//#import <thread>

#define ADDR_24LC02        0xA0 >> 1  //0xA0 = Write address and 0xA1 is the read address.
#define I2C_SPEED               100000
#define I2C_SLAVE_ADDRESS7      0x30 >> 1
#define kBufferSize 20

NSInteger IN_GPIO=8;
NSInteger OUT_GPIO=9;
NSInteger DOWN_GPIO=10;
NSInteger UP_GPIO=11;


NSInteger elect_magnet=12;
NSInteger FAN_IN_GPIO=13;
NSInteger FAN_OUT_GPIO=14;


NSInteger UP_SENSOR=0;
NSInteger DOWN_SENSOR=1;
NSInteger IN_SENSOR=2;
NSInteger OUT_SENSOR=3;
NSInteger RESET_SENSOR=4;
NSInteger FAN_IN_SENSOR=5;
NSInteger FAN_OUT_SENSOR=6;


NSInteger GPIO_ON=1;
NSInteger GPIO_OFF=0;
NSInteger IN_OUT_SENSOR_ON=1;
NSInteger IN_OUT_SENSOR_OFF=0;
NSInteger UP_DOWN_SENSOR_ON=1;
NSInteger UP_DOWN_SENSOR_OFF=0;
NSInteger FAN_IN_OUT_SENSOR_ON=1;
NSInteger FAN_IN_OUT_SENSOR_OFF=0;

NSString *low_state_binary;
NSString *high_state_binary;

int IN_STATE=1;
int OUT_STATE=2;
int DOWN_STATE=3;
int UNREADY_STATE=4;

int DUT1_STATE = 5;
int DUT2_STATE = 6;
int DUT3_STATE = 7;
int DUT4_STATE = 8;
BOOL StopLoop;

int Eowyn_Count = 1;
//NSString *Default_IP=@"192.168.100.12";
NSString *eowyn_IP=@"169.254.1.20";
NSString *AllowSetIps=@"169.254.1.20;169.254.1.21;169.254.1.22;169.254.1.23;169.254.1.24;169.254.1.25;169.254.1.26;169.254.1.27;169.254.1.28;169.254.1.29";
//NSString *DFU_IP=@"10.0.200.177";

BOOL sign = YES;

@interface ViewController ()
@property (weak) IBOutlet NSButton *btnConnect;
@property (weak) IBOutlet NSButton *btnDisConnect;

@property (weak) IBOutlet NSPopUpButton *popTestType;

@property (weak) IBOutlet NSPopUpButton *popDebug;
@property (weak) IBOutlet NSButton *btnSend;

@property (weak) IBOutlet NSTextField *textField_loopCount;
@property (weak) IBOutlet NSButton *btn_loopStart;
@property (weak) IBOutlet NSButton *btn_loopStop;

@property (strong,nonatomic)ShowingLogVC *showingLogVC;

@property (weak) IBOutlet NSPopUpButton *popBtnScript;

@property (weak) IBOutlet NSButton *btn_scriptStart;

@property (weak) IBOutlet NSButton *btn_scriptStop;

//@property (weak) IBOutlet NSPopUpButton *popBtnLedCorlor;

@property (weak) IBOutlet NSPopUpButton *popBtnLedType;
@property (strong) IBOutlet NSPopUpButton *DOut;

//@property (weak) IBOutlet NSButton *btn_send_led;

@property (weak) IBOutlet NSImageView *lightSlot1;
@property (weak) IBOutlet NSImageView *lightSlot2;
@property (weak) IBOutlet NSImageView *lightSlot3;
@property (weak) IBOutlet NSImageView *lightSlot4;

@property (weak) IBOutlet NSImageView *lightIn;
@property (weak) IBOutlet NSImageView *lightOut;
@property (weak) IBOutlet NSImageView *lightDown;
@property (weak) IBOutlet NSImageView *lightUp;

@property (weak) IBOutlet NSButton *btnIN;
@property (weak) IBOutlet NSButton *btnUP;
@property (weak) IBOutlet NSButton *btnUP_OUT;
@property (weak) IBOutlet NSButton *btnOUT;
@property (weak) IBOutlet NSButton *btnDOWN;
@property (weak) IBOutlet NSButton *btnIN_DOWN;
@property (weak) IBOutlet NSButton *btnRed;

@property (weak) IBOutlet NSButton *btnBlue;
@property (weak) IBOutlet NSButton *btnReset;
@property (weak) IBOutlet NSButton *btnGreen;
@property (strong) IBOutlet NSProgressIndicator *LoopSignal;
@property (weak) IBOutlet NSButton *btnYellow;
@property (weak) IBOutlet NSTextField *addWriteView;
@property (weak) IBOutlet NSTextField *cmdWriteView;
@property (weak) IBOutlet NSTextField *busIdView;
@property (strong) IBOutlet NSTextField *DOut_Value;

@property (strong) IBOutlet NSTextField *LoopT;
@property (strong) IBOutlet NSTextField *Delay_Time;
@property (strong) IBOutlet NSTextField *CurrentTime;

@property (weak) IBOutlet NSButton *factoryIpBtn;
@property (weak) IBOutlet NSPopUpButton *setIpPopBtn;

@property (weak) IBOutlet NSButton *DigitalOut_ON;
@property (weak) IBOutlet NSButton *DigitalOut_OFF;

@end

@implementation ViewController
{
    NSMutableString * ledRecord_x42;
    NSMutableString * ledRecord_x44;
    NSMutableString * cylinderRecord;
    NSThread * threadLoop;
    Eowyn *eowyn;
    BOOL is_stop;
    BOOL is_run_scipt_stop;
    int up_sensor;//UP_SENSOR_1
    
    NSString *current_low_state;
    NSString *current_high_state;
    BOOL isPingSuccess;
    BOOL exitPing;
    BOOL isDebug;
    BOOL isConnect;
    NSString *connectingIp;
    
}

-(void)addItemsWithTitles:(NSArray *)titles popBtn:(NSPopUpButton *)popBtn{
    
    [popBtn removeAllItems];
    [popBtn addItemsWithTitles:titles];
}
//NSString *Default_IP=@"192.168.100.12";
//NSString *FCT_IP=@"169.254.1.20";
//NSString *DFU_IP=@"10.0.200.177";
-(void)setDefaultIp{
 
 
    int titleIndex = [[self.title substringFromIndex:2] intValue];
    NSArray *eowynIpArr =[eowyn_IP componentsSeparatedByString:@"."];
    if (eowynIpArr.count == 4) {
        int eowyn_IP_last = [[eowynIpArr lastObject] intValue];
        //    int FCT_IP_last = [[[FCT_IP componentsSeparatedByString:@"."] lastObject] intValue];
        //    int DFU_IP_last = [[[DFU_IP componentsSeparatedByString:@"."] lastObject] intValue];
        eowyn_IP = [NSString stringWithFormat:@"%@.%@.%@.%d",eowynIpArr[0],eowynIpArr[1],eowynIpArr[2],eowyn_IP_last+titleIndex-1];
        //    FCT_IP = [NSString stringWithFormat:@"169.254.1.%d",FCT_IP_last+titleIndex-1];
        //    DFU_IP = [NSString stringWithFormat:@"10.0.200.%d",DFU_IP_last+titleIndex-1];
        //    FCT_IP=@"169.254.1.20";
        //    DFU_IP=@"10.0.200.177";
    }

}


- (void)viewDidLoad {
    [super viewDidLoad];
    isDebug=NO;

//    char add = [self cw_stringToHex:@"0x42"];

    [self define_eowyn_ports];
    [self testlog];

    // Do view setup here.
    //[self addItemsWithTitles:@[@"FCT Test",@"DFU Test"] popBtn:self.popTestType];
//    [self addItemsWithTitles:@[@"FCT Test"] popBtn:self.popTestType];
    [self setDefaultIp];
    
//
    
    [self addItemsWithTitles: @[@"IN",@"OUT",@"DOWN",@"UP",@"CHECK CURRENT POSITION",@"CHECK DUT STATE",@"READ TEMPERATURE",@"READ FAN SPEED",@"RUN FAN RPM",@"ELECT_MAGNET ON",@"ELECT_MAGNET OFF",@"CHECK LED",@"CHECK RESET BUTTON",@"FAN MOVE IN",@"FAN MOVE OUT",@"LED TEST1"] popBtn:self.popDebug];
    
    [self addItemsWithTitles:@[@"UUT1",@"UUT2",@"UUT3",@"UUT4",@"Fixture"] popBtn:self.popBtnLedType];
    [self addItemsWithTitles:@[@"Megnet",@"IN",@"OUT",@"UP",@"DOWN",@"NONE"] popBtn:self.DOut];
//    [self addItemsWithTitles:[self getSetIpAddrs] popBtn:self.popTestType];
    if (Eowyn_Count == 1) {
        [self addItemsWithTitles:@[@"169.254.1.20",@"192.168.100.12"] popBtn:self.popTestType];
        [self addItemsWithTitles:@[@"169.254.1.20"] popBtn:self.setIpPopBtn];
    
    }else{//[self getSetIpAddrs]
//        NSMutableArray *arr = [self getSetIpAddrs];
//        [arr removeObject:eowyn_IP];
        if ([self.title containsString:[NSString stringWithFormat:@"%d",Eowyn_Count]]) {
            [self addItemsWithTitles:[self getSetIpAddrs] popBtn:self.popTestType];
            [self addItemsWithTitles:[self getSetIpAddrs] popBtn:self.setIpPopBtn];
        }else{
            [self addItemsWithTitles:@[eowyn_IP] popBtn:self.popTestType];
            [self addItemsWithTitles:@[@"169.254.1.20"] popBtn:self.setIpPopBtn];
        }

    }
//

    [self.popBtnScript removeAllItems];
    [self.popBtnScript addItemsWithTitles:[self getScriptPathList]];
    
    [self enableBtns:NO];
    self.popTestType.enabled = YES;

    self.btnConnect.enabled = NO;
    connectingIp = self.popTestType.title;
    if (Eowyn_Count == 1) {
        self.btnConnect.hidden = YES;
        self.btnDisConnect.hidden = YES;
//        NSString *ip = self.popTestType.title;
        [self setPingIpAddress:connectingIp];
    }
    
//    NSString *ip = isDebug ?@"14.215.177.39":FCT_IP;

    
}

-(NSMutableArray *)getSetIpAddrs{
    
    NSArray *ips = [AllowSetIps componentsSeparatedByString:@";"];
    NSMutableArray *mut_arr = [[NSMutableArray alloc]initWithArray:ips];

    return mut_arr;
}


- (IBAction)clickIpPopBtn:(NSPopUpButton *)btn {
    connectingIp = btn.title;
    if (Eowyn_Count == 1) {
        exitPing = YES;
        [NSThread sleepForTimeInterval:2];
        exitPing =NO;
        [self setPingIpAddress:btn.title];
    }
    
}


-(void)enableBtns:(BOOL)isEnable{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.btnIN.enabled=isEnable;
        self.btnUP.enabled=isEnable;
        self.btnOUT.enabled=isEnable;
        self.btnDOWN.enabled=isEnable;
        self.btnUP_OUT.enabled=isEnable;
        self.btnIN_DOWN.enabled=isEnable;
        self.btnRed.enabled=isEnable;
        self.btnBlue.enabled=isEnable;
        self.btnReset.enabled=isEnable;
        self.btnGreen.enabled=isEnable;
        self.btnSend.enabled=isEnable;
    
        self.btnYellow.enabled = isEnable;
        self.btnConnect.enabled=!isEnable;
        self.btnDisConnect.enabled=isEnable;

        self.btn_loopStop.enabled=isEnable;
        self.btn_loopStart.enabled=isEnable;
        self.DigitalOut_ON.enabled = isEnable;
        self.DigitalOut_OFF.enabled = isEnable;
        
        self.btn_scriptStart.enabled=isEnable;
        self.btn_scriptStop.enabled=isEnable;
        self.factoryIpBtn.enabled = isEnable;
        self.popTestType.enabled = !isEnable;
        
      
    });

}
- (IBAction)clickFactoryIP:(NSButton *)btn {
    NSError * myError = nil;
    
    BOOL isSucess = [eowyn setEowynIPAddressWithIPString:self.setIpPopBtn.title andError:&myError];
    
    if (isSucess) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [MyEexception RemindException:@"" Information:@"Set Factory IP successful.Please reboot the fixture"];
        });
    }else{
        dispatch_async(dispatch_get_main_queue(), ^{
            [MyEexception RemindException:@"Error" Information:[NSString stringWithFormat:@"Set Factory IP Fail.Error Info:%@",[myError localizedDescription]]];
        });
    }
    
}
-(void)setPingIpAddress:(NSString *)ip{
//    if ([self.title containsString:@"1"]) {
//        return;
//    }
    NSString *ip_address = [NSString stringWithFormat:@"ping %@",ip];
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSTask *task = [[NSTask alloc] init];
        [task setLaunchPath:@"/bin/sh"];
        
        [task setArguments:[NSArray arrayWithObjects:@"-c",ip_address, nil]];
        //        NSData *readData = nil;
        NSPipe* nsreadPipe = [NSPipe pipe];
        NSFileHandle *nsreadHandle = [nsreadPipe fileHandleForReading];
        [task setStandardOutput: nsreadPipe];
        [task launch];
        
    
        int errorcount =0;

        while (!exitPing)
        {
            [NSThread sleepForTimeInterval:0.5];
            NSData *readData = [nsreadHandle availableData];
            if (readData.length) {
                NSString *reply = [[NSString alloc] initWithData:readData encoding:NSUTF8StringEncoding];
                
                if (!isConnect) {
                    show_log(reply);
                    
                }
                
                if ([reply containsString:@"icmp_seq="] &&[reply containsString:@"ttl="]) {
               
                    
                    [self click_Connect:self.btnConnect];
                    isPingSuccess = YES;
                    errorcount =0;
                }
//                else{
//                    errorcount = errorcount +1;
//                    if (errorcount>5) {
//                        [self clickDisConnect:self.btnDisConnect];
//                        if (isPingSuccess) {
//                            dispatch_async(dispatch_get_main_queue(), ^{
//                                [MyEexception RemindException:@"ERROR" Information:@"Please confirm whether the network is normal"];
//                            });
//                        }
//                        isPingSuccess = NO;
//                        errorcount =0;
//                    }
//
//
//                }
            }else{
                break;
            }
            
            
            [NSThread sleepForTimeInterval:0.5];
        }
    });
}


- (IBAction)clickDisConnect:(NSButton *)sender {
    
    if (!eowyn || !isConnect) {
        return;
    }
    
    [self enableBtns:NO];
    isConnect=NO;
    [eowyn close];
    

    [self resetAllLightState];
    
}

-(void)resetAllLightState{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self resetLightState:self.lightSlot1];
        [self resetLightState:self.lightSlot2];
        [self resetLightState:self.lightSlot3];
        [self resetLightState:self.lightSlot4];
        [self resetLightState:self.lightOut];
        [self resetLightState:self.lightDown];
        [self resetLightState:self.lightUp];
        [self resetLightState:self.lightIn];
    });

}

-(void)resetLightState:(NSImageView *)lightView{
    if (lightView) {
        [lightView setImage:[NSImage imageNamed:@"state_off"]];
        lightView.tag=0;
    }

}

void show_log(NSString *string){
//    if (!isConnect) {
   
        if (Eowyn_Count <= 1) {
            [ShowingLogVC postNotificationWithLog:string type:@"DEBUG ####"];
        }else{
            NSLog(@"%@",string);
        }
        
//    }
    
}

bool initialI2C(Eowyn * eowyn,NSString * connectIP)
{
    BOOL success = NO;
    success = [eowyn connectWithIP:connectIP];
    if(!success) return NO;
    
    [eowyn configI2C];
    
    
    //luo add
    //    unsigned char data[3] ;
    //    memset(data, 0, 3);
    //    data[0]=0x06;
    //    data[1]=0x00;
    //    data[2]=0x00;
    //
    //    [eowyn writeI2C:data writeadd:0x42 writelen:3 busId:0];
    
    
    return YES;
}


//- (IBAction)changeIP:(NSPopUpButton *)btn {
//    connectingIp = btn.title;
////    [self click_Connect:nil];
//
//}



- (IBAction)click_Connect:(id)sender {
    
    if (isConnect) {

        return;
    }
//    if (!isPingSuccess) {
//
//        show_log(@"Please confirm whether the network is normal");
//        return;
//    }
    
    
    NSString *ip_address = [NSString stringWithFormat:@"ping %@ -t1",connectingIp];
    
        NSTask *task = [[NSTask alloc] init];
        [task setLaunchPath:@"/bin/sh"];
        
        [task setArguments:[NSArray arrayWithObjects:@"-c",ip_address, nil]];
        //        NSData *readData = nil;
        NSPipe* nsreadPipe = [NSPipe pipe];
        NSFileHandle *nsreadHandle = [nsreadPipe fileHandleForReading];
        [task setStandardOutput: nsreadPipe];
        [task launch];
    
    NSData *readData = [nsreadHandle availableData];
   
    NSString *reply = [[NSString alloc] initWithData:readData encoding:NSUTF8StringEncoding];
        
    if (!([reply containsString:@"icmp_seq="] &&[reply containsString:@"ttl="])) {
        return;
    }
    [self clickDisConnect:self.btnDisConnect];
//    NSString *connectIP = eowyn_IP;
//    if ([self.popTestType.title isEqualToString:@"DFU Test"]) {
//        connectIP = DFU_IP;
//
//    }
    NSString *connectIP = connectingIp;
    eowyn = nil;
    eowyn = [[Eowyn alloc] init];
    
    BOOL success = NO;
    show_log(@"Start Connect ...");
 
    if (!isDebug) {
        success = initialI2C(eowyn,connectIP);
    }else{
        success=YES;
    }
    
    if(!success){
        show_log(@"Connect Fail!");
        isConnect=NO;
        return;
    }else{
        
        [self enableBtns:YES];

        show_log(@"Connect Successful!");
        isConnect=YES;
        [self get_state];

        dispatch_async(dispatch_get_main_queue(), ^{
            [MyEexception RemindException:@"" Information:@"the network is connected successful"];
        });
       
        
        
    }
    
    ledRecord_x42 = [NSMutableString stringWithString:@"ffffffff"];
    ledRecord_x44 = [NSMutableString stringWithString:@"ffffffff"];
    cylinderRecord = [NSMutableString stringWithString:@"ffffff"];
}


int checkPositionSensor(Eowyn * eowyn){
    return 0;
//    show_log(@"-----------------checkPositionSensor-----------------");
//    ATDeviceDIOType in_io_stat = [eowyn readIO:IN_SENSOR];
//    show_log([NSString stringWithFormat:@"in_io_stat:%d",in_io_stat]);
//
//    ATDeviceDIOType out_io_stat = [eowyn readIO:OUT_SENSOR];
//    show_log([NSString stringWithFormat:@"out_io_stat:%d",out_io_stat]);
//    ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
//
//    show_log([NSString stringWithFormat:@"up_io_stat:%d",up_io_stat]);
//    ATDeviceDIOType down_io_stat = [eowyn readIO:DOWN_SENSOR];
//    show_log([NSString stringWithFormat:@"down_io_stat:%d",down_io_stat]);
//
//    if(in_io_stat == IN_OUT_SENSOR_OFF && out_io_stat == IN_OUT_SENSOR_ON && up_io_stat == UP_DOWN_SENSOR_ON && down_io_stat == UP_DOWN_SENSOR_OFF){
//        show_log(@"CurrentState is OUT_STATE");
//        return OUT_STATE;
//    }else if(in_io_stat == IN_OUT_SENSOR_OFF && out_io_stat == IN_OUT_SENSOR_OFF && up_io_stat == UP_DOWN_SENSOR_ON && down_io_stat == UP_DOWN_SENSOR_OFF){
//        show_log(@"CurrentState is UNREADY_STATE");
//        return UNREADY_STATE;
//    }else if(in_io_stat == IN_OUT_SENSOR_ON && out_io_stat == IN_OUT_SENSOR_OFF && up_io_stat == UP_DOWN_SENSOR_ON && down_io_stat == UP_DOWN_SENSOR_OFF){
//        show_log(@"CurrentState is IN_STATE");
//        return IN_STATE;
//    }else if(in_io_stat == IN_OUT_SENSOR_ON && out_io_stat == IN_OUT_SENSOR_OFF && up_io_stat == UP_DOWN_SENSOR_OFF && down_io_stat == UP_DOWN_SENSOR_ON){
//        show_log(@"CurrentState is DOWN_STATE");
//        return DOWN_STATE;
//    }else{
//        show_log(@"Error STATE");
//        return -1;
//    }
}

- (IBAction)clickCheckPosSenor:(NSButton *)btn {
    
    checkPositionSensor(eowyn);
}




int checkDUTSensor(Eowyn * eowyn){
    [eowyn writeI2C:@"06f0ff" writeadd:0x44 writelen:3];
    [eowyn writeI2C:@"00" writeadd:0x44 writelen:1];
    int state = [eowyn readDUTI2C:0x44 readlen:2];
    
    show_log([NSString stringWithFormat:@"checkDUTSensor state is %d\n",state]);
    
    return state;
}




- (IBAction)clickBtnScriptPath:(id)sender {
    NSString *title = self.popBtnScript.titleOfSelectedItem;
    NSString *resourcePath =  [NSString cw_getResourcePath];
    [CWFileManager cw_openFileWithPath:resourcePath];
    
    NSString *filePath = [resourcePath stringByAppendingPathComponent:title];
    [CWFileManager cw_openFileWithPath:filePath];
    
}

-(NSMutableArray *)getScriptPathList{
    
    NSString *resourcePath =  [NSString cw_getResourcePath];
    
    NSMutableArray *mutArray =[NSString cw_getFileNameListInDirPath:resourcePath str1:@".json" str2:@"script"];
    
    return mutArray;
}




-(void)controlWithName:(NSString *)bnt_title{
    if ([bnt_title.lowercaseString containsString:@"in"]) {
        show_log(@"-----------------IN-----------------");
        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];//0
        if (up_io_stat != UP_DOWN_SENSOR_ON){//#UP_DOWN_SENSOR_ON  1
            show_log(@"UP SENSOR NO ON\r");
            //self.btnSend.enabled = YES;
            return;
        }
        
        show_log([NSString stringWithFormat:@"UP SENSOR STATS IS %d\r",up_io_stat]);
        [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
        [eowyn writeIO:IN_GPIO value:GPIO_ON];
        
        [NSThread sleepForTimeInterval:3.0];
        int sleep =3;
        show_log([NSString stringWithFormat:@"sleep %ds\r",sleep]);
        int timeout =10;
        while (1) {
            
            if (sleep >=timeout) {
                show_log(@"IN ERROR\r");
                break;
            }
            
            ATDeviceDIOType in_sensor_stat = [eowyn readIO:IN_SENSOR];
            NSLog(@"%@", [NSString stringWithFormat:@"cw_ATDeviceDIOType--%hhu",in_sensor_stat]);
            if (in_sensor_stat == IN_OUT_SENSOR_ON){
                
                [eowyn writeIO:elect_magnet value:GPIO_ON];//elect_magnet 12
                show_log(@"IN SENSOR IS OK\r");
                break;
                
                //                        show_log(@"elect_magnet ON\r");
            }
            else{
                show_log([NSString stringWithFormat:@"sleep 1s\r"]);
                [NSThread sleepForTimeInterval:1.0];
                sleep = sleep+1;
    
            }
        }

        checkPositionSensor(eowyn);
    } else if([bnt_title.lowercaseString containsString:@"out"]){
        show_log(@"-----------------OUT-----------------");
        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
        show_log([NSString stringWithFormat:@"UP SENSOR STAT %d\r",up_io_stat]);
        if (up_io_stat != UP_DOWN_SENSOR_ON){
            show_log(@"UP SENSOR IS NOT ON\r");
            //            self.btnSend.enabled = YES;
            return;
        }
        else{
            
            [eowyn writeIO:elect_magnet value:GPIO_OFF];
            show_log(@"elect_magnet OFF\r");
            show_log(@"sleep 1s\r");
            [NSThread sleepForTimeInterval:1];
        }
        [eowyn writeIO:IN_GPIO value:GPIO_OFF];
        [eowyn writeIO:OUT_GPIO value:GPIO_ON];
       // show_log(@"sleep 3s\r");
//        [NSThread sleepForTimeInterval:3];
//        for (int j=0; j<3; j++) {
//
//            ATDeviceDIOType out_io_stat = [eowyn readIO:OUT_SENSOR];
//            if (out_io_stat==IN_OUT_SENSOR_ON){
//                printf("OUT SENSOR IS ON\r");
//                [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
//                break;
//            }
//            show_log(@"sleep 1.5s\r");
//            [NSThread sleepForTimeInterval:1.5];
//
//        }
        
        
        [NSThread sleepForTimeInterval:3.0];
        int sleep =3;
        show_log([NSString stringWithFormat:@"sleep %ds\r",sleep]);
        int timeout =10;
        while (1) {
            
            if (sleep >=timeout) {
                show_log(@"OUT ERROR\r");
                break;
            }
            
            ATDeviceDIOType out_io_stat = [eowyn readIO:OUT_SENSOR];
            if (out_io_stat == IN_OUT_SENSOR_ON){
                
                printf("OUT SENSOR IS ON\r");
                [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
                break;
                
                //                        show_log(@"elect_magnet ON\r");
            }
            else{
                show_log([NSString stringWithFormat:@"sleep 1s\r"]);
                [NSThread sleepForTimeInterval:1.0];
                sleep = sleep+1;
                
            }
        }
        
        checkPositionSensor(eowyn);

        
    }else if([bnt_title.lowercaseString containsString:@"up"]){
        //                    ATDeviceDIOType in_io_stat = [eowyn readIO:IN_SENSOR];
        //                    if (in_io_stat != IN_OUT_SENSOR_ON){
        //                        show_log(@"IN SENSOR IS NOT ON\r");
        //                        break;
        //                    }
        show_log(@"-----------------UP-----------------");
        [eowyn writeIO:DOWN_GPIO value:GPIO_OFF];
        [eowyn writeIO:UP_GPIO value:GPIO_ON];
//        show_log(@"sleep 3s\r");
//        [NSThread sleepForTimeInterval:3.0];
//        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
//        if (up_io_stat == UP_DOWN_SENSOR_ON){
//            show_log(@"UP SENSOR IS ON\r");
//        }
//        else{
//            show_log(@"UP SENSOR IS NOT ON\r");
//        }
        
        
        
        [NSThread sleepForTimeInterval:3.0];
        int sleep =3;
        show_log([NSString stringWithFormat:@"sleep %ds\r",sleep]);
        int timeout =10;
        while (1) {
            
            if (sleep >=timeout) {
                show_log(@"UP SENSOR IS NOT ON\r");
                break;
            }
            
            ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
            if (up_io_stat == UP_DOWN_SENSOR_ON){
 
                show_log(@"UP SENSOR IS ON\r");
                break;
    
            }
            else{
                show_log([NSString stringWithFormat:@"sleep 1s\r"]);
                [NSThread sleepForTimeInterval:1.0];
                sleep = sleep+1;
                
            }
        }
        
        checkPositionSensor(eowyn);
    
    }
    
    else if([bnt_title.lowercaseString containsString:@"down"]){
        show_log(@"-----------------DOWN-----------------");
        ATDeviceDIOType in_io_stat = [eowyn readIO:IN_SENSOR];
        show_log([NSString stringWithFormat:@"IN SENSOR STAT IS %d\r",in_io_stat]);
        if (in_io_stat != IN_OUT_SENSOR_ON){
            show_log(@"IN SENSOR IS NOT ON\r");
            //            self.btnSend.enabled = YES;
            return;
        }
        
        [eowyn writeIO:UP_GPIO value:GPIO_OFF];
        [eowyn writeIO:DOWN_GPIO value:GPIO_ON];
        
//        show_log(@"sleep 3s\r");
//        [NSThread sleepForTimeInterval:3.0];
//        ATDeviceDIOType down_io_stat = [eowyn readIO:DOWN_SENSOR];
//        if (down_io_stat == UP_DOWN_SENSOR_ON){
//            show_log(@"DOWN SENSOR IS ON\r");
//        }
//        else{
//            show_log(@"DOWN SENSOR IS NOT ON\r");
//        }
//
        
        [NSThread sleepForTimeInterval:3.0];
        int sleep =3;
        show_log([NSString stringWithFormat:@"sleep %ds\r",sleep]);
        int timeout =10;
        while (1) {
            
            if (sleep >=timeout) {
                show_log(@"DOWN SENSOR IS NOT ON\r");
                break;
            }
            
            ATDeviceDIOType up_io_stat = [eowyn readIO:DOWN_SENSOR];
            if (up_io_stat == UP_DOWN_SENSOR_ON){
                
                show_log(@"DOWN SENSOR IS ON\r");
                break;
                
            }
            else{
                show_log([NSString stringWithFormat:@"sleep 1s\r"]);
                [NSThread sleepForTimeInterval:1.0];
                sleep = sleep+1;
                
            }
        }
        
         checkPositionSensor(eowyn);
    }
    
    else if([bnt_title.lowercaseString containsString:@"dut"]){
        [self get_state_dut:bnt_title];
    }
}

- (IBAction)clickControl:(NSButton *)btn {

    if ([btn.title containsString:@"&"]) {
        NSArray *titles = [btn.title cw_componentsSeparatedByString:@"&"];
        if (titles.count<2) {
            [self controlWithName:btn.title];
        }else{
            for (NSString *title in titles) {
                [self controlWithName:title];
            }
        }
    }else{
        [self controlWithName:btn.title];
    }
}
- (IBAction)LoopStart:(id)sender {
    StopLoop = YES;
    [_LoopSignal startAnimation:nil];
    threadLoop = [[NSThread alloc] initWithTarget:self selector:@selector(threadMonitor:) object:nil];
    [threadLoop start];
}

- (IBAction)LoopStop:(id)sender {
    StopLoop = NO;
    [_LoopSignal stopAnimation:nil];
}
-(void)threadMonitor:(id)sender
{
//    NSInteger = [];
    
    for (int i=0; i<[_LoopT integerValue]; i++) {
        if(i>=([_LoopT integerValue]-1)){
            [_LoopSignal stopAnimation:nil];
        }
        [_CurrentTime setEnabled:YES];
        dispatch_async(dispatch_get_main_queue(), ^{
            [[self->_CurrentTime cell] setIntValue:(i+1)];
        });
        if(StopLoop == NO){
            [_LoopSignal stopAnimation:nil];
            break;
        }
        [self controlWithName:@"IN"];
        [NSThread sleepForTimeInterval:2];
        [self controlWithName:@"DOWN"];

//        [self FixtureA_IN:self];
//        [self FixtureA_DOWN:self];
//
        [NSThread sleepForTimeInterval:1];
        [self controlWithName:@"UP"];
        [NSThread sleepForTimeInterval:1];
        [self controlWithName:@"OUT"];
        
        [NSThread sleepForTimeInterval:[_Delay_Time integerValue]];

        
        //        [self FixtureA_UP:self];
//        [self FixtureA_OUT:self];
        
        
    }
    
}

-(void)get_state_dut:(NSString *)dut{

    int read_port = 4;
    NSImageView *lightView=self.lightSlot1;
    if ([dut containsString:@"1"]) {
        read_port =DUT1_STATE;
        lightView = self.lightSlot1;
    }else if ([dut containsString:@"2"]){
        read_port =DUT2_STATE;
        lightView = self.lightSlot2;
    }else if ([dut containsString:@"3"]){
        read_port =DUT3_STATE;
        lightView = self.lightSlot3;
    }else if ([dut containsString:@"4"]){
        read_port =DUT4_STATE;
        lightView = self.lightSlot4;
    }
    ATDeviceDIOType up_io_stat = [eowyn readDutIO:read_port printLog:NO];
    if (up_io_stat==0){
        
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=1) {
                [lightView setImage:[NSImage imageNamed:@"state_off"]];
                lightView.tag=1;
            }
            
        });
    }
    else if(up_io_stat==1){
        //show_log([NSString stringWithFormat:@"%@ iS OFF\r",dut.uppercaseString]);
        show_log([NSString stringWithFormat:@"%@ iS ON\r",dut.uppercaseString]);
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=0) {
                [lightView setImage:[NSImage imageNamed:@"state_on"]];
                lightView.tag=0;
            }
        });
        
    }else{
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=2) {
                [lightView setImage:[NSImage imageNamed:@"state_error"]];
                lightView.tag=2;
            }
        });
    }
}


-(void)get_state_sensor:(NSString *)trayAction{
    
    NSInteger ioIndex = 0;
    NSImageView *lightView=self.lightIn;
    if ([trayAction.lowercaseString containsString:@"up"]) {
        ioIndex = UP_SENSOR;
        lightView=self.lightUp;
    }else if ([trayAction.lowercaseString containsString:@"down"]){
        ioIndex = DOWN_SENSOR;
        lightView=self.lightDown;
    }else if ([trayAction.lowercaseString containsString:@"in"]){
        ioIndex = IN_SENSOR;
        lightView=self.lightIn;
    }else if ([trayAction.lowercaseString containsString:@"out"]){
        ioIndex = OUT_SENSOR;
        lightView=self.lightOut;
    }
    
    ATDeviceDIOType in_sensor_stat = [eowyn readIO:ioIndex printLog:NO];
    if (in_sensor_stat==1){
        
        // show_log([NSString stringWithFormat:@"%@ iS ON\r",trayAction.uppercaseString]);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=1) {
                [lightView setImage:[NSImage imageNamed:@"state_on"]];
                lightView.tag=1;
            }
        });
    }
    else if(in_sensor_stat==0){
        
        //show_log([NSString stringWithFormat:@"%@ iS OFF\r",trayAction.uppercaseString]);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=0) {
                [lightView setImage:[NSImage imageNamed:@"state_off"]];
                lightView.tag=0;
            }
        });
    }else{
        dispatch_async(dispatch_get_main_queue(), ^{
            if (lightView.tag!=2) {
                [lightView setImage:[NSImage imageNamed:@"state_error"]];
                lightView.tag=2;
            }
        });
    }
}

-(void)get_state{
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        while (1) {
            if (!isConnect) {
                break;
            }
            if (!is_stop) {
                
                [self get_state_dut:@"Dut1"];
                
                [self get_state_dut:@"Dut2"];
                
                [self get_state_dut:@"Dut3"];
                
                [self get_state_dut:@"Dut4"];
                
                [self get_state_sensor:@"up"];
                
                [self get_state_sensor:@"down"];
                
                [self get_state_sensor:@"in"];
                
                [self get_state_sensor:@"out"];
                
            }
            
            [NSThread sleepForTimeInterval:0.5];
            
        }
        
        
    });
}

- (int)data2Int:(NSData *)data{
    Byte *byte = (Byte *)[data bytes];
    // 有大小端模式问题？
    return (byte[0] << 24) + (byte[1] << 16) + (byte[2] << 8) + (byte[3]);
}

-(NSData*)dataWithHexString:(NSString*)str{
    
    if (!str || [str length] == 0) {
        return nil;
    }
    
    NSMutableData *hexData = [[NSMutableData alloc] initWithCapacity:8];
    NSRange range;
    if ([str length] % 2 == 0) {
        range = NSMakeRange(0, 2);
    } else {
        range = NSMakeRange(0, 1);
    }
    for (NSInteger i = range.location; i < [str length]; i += 2) {
        unsigned int anInt;
        NSString *hexCharStr = [str substringWithRange:range];
        NSScanner *scanner = [[NSScanner alloc] initWithString:hexCharStr];
        
        [scanner scanHexInt:&anInt];
        NSData *entity = [[NSData alloc] initWithBytes:&anInt length:1];
        [hexData appendData:entity];
        
        range.location += range.length;
        range.length = 2;
    }
    return hexData;
    
}
-(NSString *)HexString_Cal_AND:(NSString *)First SEC:(NSString *)Secend
{
    NSMutableString *Value_CMD = [[NSMutableString alloc] init];
    NSString *c = [NSString stringWithFormat:@"%c",[First characterAtIndex:0]];
    unsigned long length = [First length];
    if([c  isEqual: @"0"]){
        NSLog(@"AND FUCNTION first_c NSString===%@",c);
        [Value_CMD appendString:[NSString stringWithFormat:@"%@",First]];
        NSData *data_1 =[self dataWithHexString:Value_CMD];
        NSData *data_2 =[self dataWithHexString:Secend];
        int data_1_int =[self data2Int:data_1];
        int data_2_int =[self data2Int:data_2];
        int data_3_int = data_1_int&data_2_int;
        
        NSString *sss_3b = [NSString stringWithFormat:@"%x",data_3_int];
        NSString *sss_4 = [sss_3b substringToIndex:(length-1)];
        NSString *cmd_result = @"0";
        cmd_result = [cmd_result stringByAppendingString:sss_4];
        NSLog(@"STRING AND FUNCTION the FIRST value is ===%@====The Secend is ===%@==cmd_result===%@",First,Secend,cmd_result);
        return cmd_result;
    }else{
        NSLog(@"AND FUCNTION the first charect is not 0");
        NSData *data_1 =[self dataWithHexString:First];
        NSData *data_2 =[self dataWithHexString:Secend];
        int data_1_int =[self data2Int:data_1];
        int data_2_int =[self data2Int:data_2];
        int data_3_int = data_1_int&data_2_int;
        
        NSString *sss_3b = [NSString stringWithFormat:@"%02x",data_3_int];
        NSString *sss_4 = [sss_3b substringToIndex:length];
        NSString *cmd_result = @"";
        cmd_result = [cmd_result stringByAppendingString:sss_4];
        NSLog(@"STRING AND FUNCTION the FIRST value is ===%@====The Secend is ==%@==cmd_result===%@",First,Secend,cmd_result);
        return cmd_result;
    }
    
}
-(NSString *)HexString_Cal_OR:(NSString *)First SEC:(NSString *)Secend
{
    NSMutableString *Value_CMD = [[NSMutableString alloc] init];
    NSString *c = [NSString stringWithFormat:@"%c",[First characterAtIndex:0]];
    unsigned long length = [First length];
    if([c  isEqual: @"0"]){
        NSLog(@"OR FUCNTION first_c NSString===%@",c);
        [Value_CMD appendString:[NSString stringWithFormat:@"%@",First]];
        NSData *data_1 =[self dataWithHexString:Value_CMD];
        NSData *data_2 =[self dataWithHexString:Secend];
        int data_1_int =[self data2Int:data_1];
        int data_2_int =[self data2Int:data_2];
        int data_3_int = data_1_int|data_2_int;
        
        NSString *sss_3b = [NSString stringWithFormat:@"%x",data_3_int];
        NSString *sss_4 = [sss_3b substringToIndex:(length-1)];
        NSString *cmd_result = @"0";
        cmd_result = [cmd_result stringByAppendingString:sss_4];
        NSLog(@"STRING OR FUNCTION the FIRST value is ===%@====The Secend is ==%@==cmd_result===%@",First,Secend,cmd_result);
        return cmd_result;
    }else{
        NSLog(@"OR FUCNTION the first charect is not 0");
        NSData *data_1 =[self dataWithHexString:First];
        NSData *data_2 =[self dataWithHexString:Secend];
        int data_1_int =[self data2Int:data_1];
        int data_2_int =[self data2Int:data_2];
        int data_3_int = data_1_int|data_2_int;
        
        NSString *sss_3b = [NSString stringWithFormat:@"%02x",data_3_int];
        NSString *sss_4 = [sss_3b substringToIndex:length];
        NSString *cmd_result = @"";
        cmd_result = [cmd_result stringByAppendingString:sss_4];
        NSLog(@"STRING OR FUNCTION the FIRST value is ===%@====The Secend is ==%@==cmd_result===%@",First,Secend,cmd_result);
        return cmd_result;
    }
    
}
-(void)setLedcolor:(NSString *)color uut:(NSString *)uut{
    NSLog(@"first read LED ===color==%@===uut===%@",color,uut);
//    show_log(@"in functionsetLedcolor ");

    //    [eowyn writeI2CWithString:@"02ffff" writeadd:0x42 writelen:3 busId:0];
    //    [eowyn writeI2CWithString:@"02ffff" writeadd:0x44 writelen:3 busId:0];
    //    [eowyn writeI2CWithString:@"02ffff" writeadd:0x46 writelen:3 busId:0];
    //    [eowyn writeI2CWithString:@"02ffff" writeadd:0x48 writelen:3 busId:0];

    low_state_binary = @"FF";
    high_state_binary = @"FF";
    NSString *head = @"02";

    NSString *Value_status = [eowyn readI2C_STR:0x48 readlen:2 busId:0];
    sleep(0.1);
    NSString *Value_slot12 = [eowyn readI2C_STR:0x44 readlen:2 busId:0];
    sleep(0.1);
    NSString *Value_slot34 = [eowyn readI2C_STR:0x4A readlen:2 busId:0];
    sleep(0.1);
    NSLog(@"first read LED value===%@===Value_slot12===%@===Value_slot34====%@",Value_status,Value_slot12,Value_slot34);

    if (![Value_status.lowercaseString containsString:@"ff"] || ![Value_slot12.lowercaseString containsString:@"ff"] ||![Value_slot34.lowercaseString containsString:@"ff"] ){
        NSLog(@"first read is nill====");
        [eowyn writeI2CWithString:@"02FFFF" writeadd:0x48 writelen:3 busId:0];
        sleep(0.05);
        [eowyn writeI2CWithString:@"02FFFF" writeadd:0x4A writelen:3 busId:0];
        sleep(0.05);
        [eowyn writeI2CWithString:@"02FFFF" writeadd:0x44 writelen:3 busId:0];
        sleep(0.2);
        Value_status = [eowyn readI2C_STR:0x48 readlen:2 busId:0];
        Value_slot12 = [eowyn readI2C_STR:0x44 readlen:2 busId:0];
        Value_slot34 = [eowyn readI2C_STR:0x4A readlen:2 busId:0];
        
    }

    Value_status = [head stringByAppendingString:Value_status];
    Value_slot12 = [head stringByAppendingString:Value_slot12];
    Value_slot34 = [head stringByAppendingString:Value_slot34];
    NSLog(@"the led color and uut  is ===%@======%@==",color,uut);
    NSLog(@"Value_RED read laste time is ===Value_status is==%@===Value_slot12 is==%@=====Value_slot34 is ==%@",Value_status,Value_slot12,Value_slot34);
    NSMutableString *cmd = [[NSMutableString alloc] init];
    int addr =0x02;
    [cmd appendString:[NSString stringWithFormat:@"%02x",addr]];

//    if ([color.lowercaseString containsString:@"reset"]) {
////        [eowyn writeI2CWithString:@"02FFFF" writeadd:0x48 writelen:3 busId:0];
////        [eowyn writeI2CWithString:@"02FFFF" writeadd:0x44 writelen:3 busId:0];
////
////        [eowyn writeI2CWithString:@"029F9F" writeadd:0x4A writelen:3 busId:0];
//        return;
//    }



    if ([uut.lowercaseString containsString:@"1"]) {
        Value_slot12 = [self HexString_Cal_OR:Value_slot12 SEC:@"02FF00"];

        if ([color.lowercaseString containsString:@"red"]) {
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02EFFF"];
            NSLog(@"red 0x44 read back=====%@", Value_slot12);

            NSLog(@"color is red  result_red=====%@===result_green is==%@====result_blue is ===%@",Value_slot12,Value_status,Value_slot34);
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];//write green led
        }else if ([color.lowercaseString containsString:@"green"]){
            NSLog(@"green 0x44 read back=====%@", Value_slot12);

            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02DFFF"];
            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"blue"]){
            NSLog(@"blue 0x44 read back=====%@", Value_slot12);
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02BFFF"];
            NSLog(@"0x44 after and value=====%@", Value_slot12);

            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"yellow"]){
            NSLog(@"yellow 0x44 read back=====%@",Value_slot12);
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"027FFF"];
            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"reset"]){
            NSLog(@"0x44 read back=====%@",Value_slot12);
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"027FFF"];
            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x44 writelen:3 busId:0];
        }
        show_log([NSString stringWithFormat:@"Set Slot: %@ Value: %@",uut,Value_slot12]);

    }
    else if ([uut.lowercaseString containsString:@"2"]){
        Value_slot12 = [self HexString_Cal_OR:Value_slot12 SEC:@"0200FF"];

        if ([color.lowercaseString containsString:@"red"]) {
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02FFFE"];
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];//write green led
        }else if ([color.lowercaseString containsString:@"green"]){

            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02FFFD"];
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"blue"]){
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02FFFB"];
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"yellow"]){
            NSLog(@"0x44 read back=====%@",Value_slot12);
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02FFF7"];
            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:Value_slot12 writeadd:0x44 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"reset"]){
            NSLog(@"0x44 read back=====%@",Value_slot12);
            Value_slot12 = [self HexString_Cal_AND:Value_slot12 SEC:@"02FFF7"];
            NSLog(@"======write to 0x44====%@",Value_slot12);
            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x44 writelen:3 busId:0];
        }
        show_log([NSString stringWithFormat:@"Set Slot: %@ Value: %@",uut,Value_slot12]);

    }
    else if ([uut.lowercaseString containsString:@"3"]){
        Value_slot34 = [self HexString_Cal_OR:Value_slot34 SEC:@"02FF00"];

        if ([color.lowercaseString containsString:@"red"]) {
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02EFFF"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];//write green led
        }else if ([color.lowercaseString containsString:@"green"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02DFFF"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"blue"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02BFFF"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"yellow"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"027FFF"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"reset"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"027FFF"];
            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x4A writelen:3 busId:0];
        }
        show_log([NSString stringWithFormat:@"Set Slot: %@ Value: %@",uut,Value_slot34]);

    }
    else if ([uut.lowercaseString containsString:@"4"]){
        Value_slot34 = [self HexString_Cal_OR:Value_slot34 SEC:@"0200FF"];
        if ([color.lowercaseString containsString:@"red"]) {
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02FFFE"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];//write green led
        }else if ([color.lowercaseString containsString:@"green"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02FFFD"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"blue"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02FFFB"];
            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];

        }else if ([color.lowercaseString containsString:@"yellow"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02FFF7"];

            [eowyn writeI2CWithString:Value_slot34 writeadd:0x4A writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"reset"]){
            Value_slot34 = [self HexString_Cal_AND:Value_slot34 SEC:@"02FFF7"];

            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x4A writelen:3 busId:0];
        }
        show_log([NSString stringWithFormat:@"Set Slot: %@ Value: %@",uut,Value_slot34]);

    }
    else if ([uut.lowercaseString containsString:@"fixture"]){//status

        Value_status = [self HexString_Cal_OR:Value_status SEC:@"020810"];

        if ([color.lowercaseString containsString:@"red"]) {
            Value_status = [self HexString_Cal_OR:Value_status SEC:@"02FEFF"];
            NSLog(@"uut===%@===Value_status===%@",uut,Value_status);
            
//            [eowyn writeI2CWithString:Value_status writeadd:0x48 writelen:3 busId:0];//write green led
            [eowyn writeI2CWithString:@"02FEFF" writeadd:0x48 writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"green"]){
            Value_status = [self HexString_Cal_OR:Value_status SEC:@"02FDFF"];
            NSLog(@"uut===%@===Value_status===%@",uut,Value_status);

//            [eowyn writeI2CWithString:Value_status writeadd:0x48 writelen:3 busId:0];//write green led
            [eowyn writeI2CWithString:@"02FDFF" writeadd:0x48 writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"blue"]){
            Value_status = [self HexString_Cal_OR:Value_status SEC:@"02FBFF"];
            NSLog(@"uut===%@===Value_status===%@",uut,Value_status);

//            [eowyn writeI2CWithString:Value_status writeadd:0x48 writelen:3 busId:0];
            [eowyn writeI2CWithString:@"02FBFF" writeadd:0x48 writelen:3 busId:0];//write green led

        }else if ([color.lowercaseString containsString:@"yellow"]){
            Value_status = [self HexString_Cal_OR:Value_status SEC:@"02FF7F"];
            NSLog(@"uut===%@===Value_status===%@",uut,Value_status);
//            [eowyn writeI2CWithString:Value_status writeadd:0x48 writelen:3 busId:0];//write green led

            [eowyn writeI2CWithString:@"02FF7F" writeadd:0x48 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"reset"]){
            Value_status = [self HexString_Cal_OR:Value_status SEC:@"02FF7F"];
            NSLog(@"uut===%@===Value_status===%@",uut,Value_status);
            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x48 writelen:3 busId:0];
        }
        show_log([NSString stringWithFormat:@"Set Slot: %@ Value: %@",uut,Value_status]);

    }

//    if ([uut.lowercaseString containsString:@"fixture"]) {
//        [eowyn writeI2CWithString:cmd writeadd:0x48 writelen:3 busId:0];
//    }
    //    else{
    //        if ([color.lowercaseString containsString:@"red"]) {
    //            NSLog(@"color is red  result_red=====%@===result_green is==%@====result_blue is ===%@",result_red,result_green,result_blue);
    //
    //            [eowyn writeI2CWithString:result_green writeadd:0x46 writelen:3 busId:0];//write green led
    //            [eowyn writeI2CWithString:result_blue writeadd:0x44 writelen:3 busId:0];//write blue led
    //
    //            [eowyn writeI2CWithString:result_red writeadd:0x42 writelen:3 busId:0];//write red led
    //        }else if ([color.lowercaseString containsString:@"green"]){
    //                    NSLog(@"color is green  result_red=====%@===result_green is==%@====result_blue is ===%@",result_red,result_green,result_blue);
    //            [eowyn writeI2CWithString:result_blue writeadd:0x44 writelen:3 busId:0];//write blue led
    //            [eowyn writeI2CWithString:result_red writeadd:0x42 writelen:3 busId:0];//write red led
    //
    //            [eowyn writeI2CWithString:result_green writeadd:0x46 writelen:3 busId:0];//write green led
    //
    //        }else if ([color.lowercaseString containsString:@"blue"]){
    //            NSLog(@"color is blue  result_red=====%@===result_green is==%@====result_blue is ===%@",result_red,result_green,result_blue);
    //
    //            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x42 writelen:3 busId:0];
    //            [eowyn writeI2CWithString:@"02FFFF" writeadd:0x44 writelen:3 busId:0];
    //
    //            [eowyn writeI2CWithString:@"029F9F" writeadd:0x46 writelen:3 busId:0];
    //        }
    //    }

}

-(void)ledWithLowAddr:(int)low_addr high_addr:(int)high_addr uut:(NSString *)uut color:(NSString *)color{
    
    if (!current_low_state.length && !current_high_state.length) {
        unsigned char *read_arr = [eowyn readI2C_arr:0x42 readlen:2 busId:0];
        if (read_arr == NULL) {
            return;
        }
        
        unsigned char stat_low = read_arr[0];//low byte
        unsigned char stat_high = read_arr[1];//high byte
        
        //    NSString *str_low = [NSString stringWithFormat:@"%02x",stat_low];
        //    NSString *str_high = [NSString stringWithFormat:@"%02x",stat_high];
        current_low_state = [self charToString:stat_low];
        current_high_state = [self charToString:stat_high];
    }
    

    NSString *str_color_state = @"110";
    if ([color.lowercaseString containsString:@"red"]) {
        str_color_state = @"110";
    }else if ([color.lowercaseString containsString:@"green"]){
        str_color_state = @"101";
    }else if ([color.lowercaseString containsString:@"blue"]){
        str_color_state = @"011";
    }
    
    NSString *binary_low= [self getBinaryByHex:current_low_state];
    NSString *binary_high= [self getBinaryByHex:current_high_state];
//    NSString *hex_str_low = @"";
//    NSString *hex_str_high = @"";
    if ([uut.lowercaseString containsString:@"uut1"]) {
        
        NSString *binary_new = [binary_low stringByReplacingCharactersInRange:NSMakeRange(5, 3) withString:str_color_state];
         current_low_state = [self getHexByBinary:binary_new];

        //
    } else if([uut.lowercaseString containsString:@"uut2"]) {
        NSString *binary_new = [binary_low stringByReplacingCharactersInRange:NSMakeRange(2, 3) withString:str_color_state];
        current_low_state = [self getHexByBinary:binary_new];
  
    }else if([uut.lowercaseString containsString:@"uut3"]) {
     
        NSString *str_color_state_1 = [str_color_state cw_getSubstringFromIndex:1 toLength:2];//index 1&2
        NSString *str_color_state_2 = [str_color_state cw_getSubstringFromIndex:0 toLength:1];
        
        NSString *binary_new_low = [binary_low stringByReplacingCharactersInRange:NSMakeRange(0, 2) withString:str_color_state_1];
        NSString *binary_new_high = [binary_high stringByReplacingCharactersInRange:NSMakeRange(7, 1) withString:str_color_state_2];
        current_low_state = [self getHexByBinary:binary_new_low];
        current_high_state = [self getHexByBinary:binary_new_high];
        
    }else if([uut.lowercaseString containsString:@"uut4"]) {
        NSString *binary_new = [binary_high stringByReplacingCharactersInRange:NSMakeRange(4, 3) withString:str_color_state];
        current_high_state = [self getHexByBinary:binary_new];
        ;
    }else if([uut.lowercaseString containsString:@"fixture"]) {
        NSString *binary_new = [binary_high stringByReplacingCharactersInRange:NSMakeRange(1, 3) withString:str_color_state];
        current_high_state = [self getHexByBinary:binary_new];
      
    }
    
    NSMutableString *x42_cmd = [[NSMutableString alloc] init];
    int addr =0x02;
   // NSString *x42_cmd_1 = [NSString stringWithFormat:@"%02x",addr];
    [x42_cmd appendString:[NSString stringWithFormat:@"%02x",addr]];
    [x42_cmd appendString: current_low_state];
    [x42_cmd appendString:current_high_state];
    
    [eowyn writeI2CWithString:x42_cmd writeadd:0x42 writelen:3 busId:0];
    
//    [eowyn writeI2CWithString:cmd writeadd:address writelen:3 busId:0];
    
}



-(NSString *)charToString:(char )hex_char{
    
    NSString *mut_hex = [NSString stringWithFormat:@"%02x",hex_char];
    NSString *hex = @"";
    if (mut_hex.length==8 && [mut_hex containsString:@"ffffff"]) {
        hex=[mut_hex stringByReplacingOccurrencesOfString:@"ffffff" withString:@""];
    }
    return hex;
}

/**
 十六进制转换为二进制
 @param hex 十六进制数
 @return 二进制数
 */
- (NSString *)getBinaryByHex:(NSString *)hex {
//    NSString *hex = @"";
//    if (mut_hex.length==8 && [mut_hex containsString:@"ffffff"]) {
//        hex=[mut_hex stringByReplacingOccurrencesOfString:@"ffffff" withString:@""];
//    }
    NSMutableDictionary *hexDic = [[NSMutableDictionary alloc] initWithCapacity:16];
    [hexDic setObject:@"0000" forKey:@"0"];
    [hexDic setObject:@"0001" forKey:@"1"];
    [hexDic setObject:@"0010" forKey:@"2"];
    [hexDic setObject:@"0011" forKey:@"3"];
    [hexDic setObject:@"0100" forKey:@"4"];
    [hexDic setObject:@"0101" forKey:@"5"];
    [hexDic setObject:@"0110" forKey:@"6"];
    [hexDic setObject:@"0111" forKey:@"7"];
    [hexDic setObject:@"1000" forKey:@"8"];
    [hexDic setObject:@"1001" forKey:@"9"];
    [hexDic setObject:@"1010" forKey:@"A"];
    [hexDic setObject:@"1011" forKey:@"B"];
    [hexDic setObject:@"1100" forKey:@"C"];
    [hexDic setObject:@"1101" forKey:@"D"];
    [hexDic setObject:@"1110" forKey:@"E"];
    [hexDic setObject:@"1111" forKey:@"F"];
    
    NSString *binary = @"";
    for (int i=0; i<[hex length]; i++) {
        
        NSString *key = [hex substringWithRange:NSMakeRange(i, 1)];
        NSString *value = [hexDic objectForKey:key.uppercaseString];
        if (value) {
            
            binary = [binary stringByAppendingString:value];
        }
    }
    return binary;
}
/**
 二进制转换成十六进制
 
 @param binary 二进制数
 @return 十六进制数
 */
- (NSString *)getHexByBinary:(NSString *)binary {
    
    NSMutableDictionary *binaryDic = [[NSMutableDictionary alloc] initWithCapacity:16];
    [binaryDic setObject:@"0" forKey:@"0000"];
    [binaryDic setObject:@"1" forKey:@"0001"];
    [binaryDic setObject:@"2" forKey:@"0010"];
    [binaryDic setObject:@"3" forKey:@"0011"];
    [binaryDic setObject:@"4" forKey:@"0100"];
    [binaryDic setObject:@"5" forKey:@"0101"];
    [binaryDic setObject:@"6" forKey:@"0110"];
    [binaryDic setObject:@"7" forKey:@"0111"];
    [binaryDic setObject:@"8" forKey:@"1000"];
    [binaryDic setObject:@"9" forKey:@"1001"];
    [binaryDic setObject:@"A" forKey:@"1010"];
    [binaryDic setObject:@"B" forKey:@"1011"];
    [binaryDic setObject:@"C" forKey:@"1100"];
    [binaryDic setObject:@"D" forKey:@"1101"];
    [binaryDic setObject:@"E" forKey:@"1110"];
    [binaryDic setObject:@"F" forKey:@"1111"];
    
    if (binary.length % 4 != 0) {
        
        NSMutableString *mStr = [[NSMutableString alloc]init];;
        for (int i = 0; i < 4 - binary.length % 4; i++) {
            
            [mStr appendString:@"0"];
        }
        binary = [mStr stringByAppendingString:binary];
    }
    NSString *hex = @"";
    for (int i=0; i<binary.length; i+=4) {
        
        NSString *key = [binary substringWithRange:NSMakeRange(i, 4)];
        NSString *value = [binaryDic objectForKey:key];
        if (value) {
            
            hex = [hex stringByAppendingString:value];
        }
    }
    return hex;
}



- (IBAction)clickFan:(NSButton *)sender {
    
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x42 writelen:3 busId:0];
//    [eowyn writeI2C:@"02ffff" writeadd:0x58 writelen:3];
//    [eowyn writeI2C:@"02ffff" writeadd:0x5E writelen:3];
//    [eowyn readI2C:0x58 readlen:2];
//    [eowyn readI2C:0x5E readlen:2];
////    unsigned char *read_arr = [eowyn readI2C_arr:0x58 readlen:2 busId:1];
//    [eowyn writeI2CWithString:@"02ffff" writeadd:0x58 writelen:3 busId:1];
}

- (IBAction)click_led:(NSButton *)btn {
    [self setLedLight2:btn];
}

///NSInteger IN_GPIO=8;
//NSInteger OUT_GPIO=9;
//NSInteger DOWN_GPIO=10;
//NSInteger UP_GPIO=11;

- (IBAction)click_dout:(NSButton *)sender {
    NSString *DOut = self.DOut.titleOfSelectedItem;
     NSString *ONOFF = sender.title;
    NSInteger Value = 100;
    NSInteger ONOFF_Value = 0;
    if([DOut isEqualToString:@"Megnet"]){
        Value = 13;
    }
    else if ([DOut isEqualToString:@"IN"]){
        Value = 8;
    }
    else if ([DOut isEqualToString:@"OUT"]){
        Value = 9;
    }
    else if ([DOut isEqualToString:@"UP"]){
        Value = 11;
    }
    else if ([DOut isEqualToString:@"DOWN"]){
        Value = 10;
    }
    else if ([DOut isEqualToString:@"NONE"]){
        Value = [_DOut_Value integerValue];
        
        NSLog(@"the valueis ==%ld",(long)Value);
    }
    if([ONOFF isEqualToString:@"ON"]){
        ONOFF_Value = 1;
    }else if ([ONOFF isEqualToString:@"OFF"]){
        ONOFF_Value = 0;

    }
    [eowyn writeIO:Value value:ONOFF_Value];
}

-(void)setLedLight1:(NSButton *)btn{
    
    NSString *device = self.popBtnLedType.titleOfSelectedItem;
    NSString *color = btn.title;
    
    if ([color.lowercaseString containsString:@"reset"]) {
        [eowyn writeI2CWithString:@"02ffff" writeadd:0x42 writelen:3 busId:0];
        
        current_low_state=@"ff";
        current_high_state=@"ff";
        return;
    }
    
    if ([device.lowercaseString containsString:@"uut1"]) {
        
        if ([color.lowercaseString containsString:@"red"]) {
            
            [self ledWithLowAddr:0xfe high_addr:0xff uut:@"uut1" color:@"red"];
        }else if([color.lowercaseString containsString:@"green"]){
            //[self ledWithAddr1:0x02 addr2:0xfd addr3:0xff];
            [self ledWithLowAddr:0xfd high_addr:0xff uut:@"uut1" color:@"green"];
        }else if([color.lowercaseString containsString:@"blue"]){
            //            [self ledWithAddr1:0x02 addr2:0xfb addr3:0xff];
            [self ledWithLowAddr:0xfb high_addr:0xff uut:@"uut1" color:@"blue"];
        }
        
        
        
    }else if ([device.lowercaseString containsString:@"uut2"]){
        if ([color.lowercaseString containsString:@"red"]) {
            [self ledWithLowAddr:0xf7 high_addr:0xff uut:@"uut2" color:@"red"];
            //            [self ledWithAddr1:0x02 addr2:0xf7 addr3:0xff];
        }else if([color.lowercaseString containsString:@"green"]){
            [self ledWithLowAddr:0xef high_addr:0xff uut:@"uut2" color:@"green"];
            //            [self ledWithAddr1:0x02 addr2:0xef addr3:0xff];
        }else if([color.lowercaseString containsString:@"blue"]){
            [self ledWithLowAddr:0xdf high_addr:0xff uut:@"uut2" color:@"blue"];
            //            [self ledWithAddr1:0x02 addr2:0xdf addr3:0xff];
        }
        
        
        
    }else if ([device.lowercaseString containsString:@"uut3"]){
        if ([color.lowercaseString containsString:@"red"]) {
            [self ledWithLowAddr:0xbf high_addr:0xff uut:@"uut3" color:@"red"];
            //            [self ledWithAddr1:0x02 addr2:0xbf addr3:0xff];
        }else if([color.lowercaseString containsString:@"green"]){
            [self ledWithLowAddr:0x7f high_addr:0xff uut:@"uut3" color:@"green"];
            //            [self ledWithAddr1:0x02 addr2:0x7f addr3:0xff];
        }else if([color.lowercaseString containsString:@"blue"]){
            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut3" color:@"blue"];
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfe];
        }
        
        
    }else if ([device.lowercaseString containsString:@"uut4"]){
        if ([color.lowercaseString containsString:@"red"]) {
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfe];
            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"red"];
        }else if([color.lowercaseString containsString:@"green"]){
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfb];
            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"green"];
        }else if([color.lowercaseString containsString:@"blue"]){
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xf7];
            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"blue"];
        }
        
        
    }else if ([device.lowercaseString containsString:@"fixture"]){
        if ([color.lowercaseString containsString:@"red"]) {
            [self ledWithLowAddr:0xff high_addr:0xef uut:@"fixture" color:@"red"];
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xef];
        }else if([color.lowercaseString containsString:@"green"]){
            [self ledWithLowAddr:0xff high_addr:0xdf uut:@"fixture" color:@"green"];
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xdf];
        }else if([color.lowercaseString containsString:@"blue"]){
            [self ledWithLowAddr:0xff high_addr:0xbf uut:@"fixture" color:@"blue"];
            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xbf];
        }
    }
}


-(void)setLedLight2:(NSButton *)btn{
    NSString *uut = self.popBtnLedType.titleOfSelectedItem;
    NSString *color = btn.title;

//    int address = 0x41;
//    if ([color.lowercaseString containsString:@"red"]) {
//        address = 0x41;
//    }else if ([color.lowercaseString containsString:@"green"]){
//        address = 0x42;
//    }else if ([color.lowercaseString containsString:@"bule"]){
//        address = 0x43;
//    }
//
    NSLog(@"LED_color===%@===uut====%@",color,uut);
    NSString *OLD = [eowyn readI2C_STR:0x42 readlen:2 busId:0];
    if(OLD){
        [self ledWithColor:color uut:uut];
    }else{
    [self setLedcolor:color uut:uut];
    }
//    [self ledWithColor_bundle:color uut:uut];
//    if ([device.lowercaseString containsString:@"uut1"]) {
//        [self ledWithLowAddr:color uut:@"uut1"];
//    }else if ([device.lowercaseString containsString:@"uut2"]){
//        [self ledWithLowAddr:color uut:@"uut2"];
//    }else if ([device.lowercaseString containsString:@"uut3"]){
//        [self ledWithLowAddr:color uut:@"uut3"];
//    }else if ([device.lowercaseString containsString:@"uut4"]){
//        [self ledWithLowAddr:color uut:@"uut4"];
//    }
}

-(void)ledWithColor:(NSString *)color uut:(NSString *)uut{
    
    
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x42 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x44 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x46 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x48 writelen:3 busId:0];
    
    if ([color.lowercaseString containsString:@"reset"]) {
        return;
    }
    NSString *low_state_binary = @"11111111";
    NSString *high_state_binary = @"11111111";
    if ([uut.lowercaseString containsString:@"uut1"]) {
        low_state_binary = @"11011111";//11111011
        
    }else if ([uut.lowercaseString containsString:@"uut2"]){
        low_state_binary = @"10111111";
        
    }else if ([uut.lowercaseString containsString:@"uut3"]){
        high_state_binary = @"11011111";
        
    }else if ([uut.lowercaseString containsString:@"uut4"]){
        high_state_binary = @"10111111";
    }else if ([uut.lowercaseString containsString:@"fixture"]){
        
        
        if ([color.lowercaseString containsString:@"red"]) {
            low_state_binary = @"11111110";
        }else if ([color.lowercaseString containsString:@"green"]){
            low_state_binary = @"11111101";
        }else if ([color.lowercaseString containsString:@"blue"]){
            low_state_binary = @"11111011";
        }
        
    }
    
    NSString *low_state = [self getHexByBinary:low_state_binary];
    NSString *high_state = [self getHexByBinary:high_state_binary];
    NSMutableString *cmd = [[NSMutableString alloc] init];
    int addr =0x02;
    // NSString *x42_cmd_1 = [NSString stringWithFormat:@"%02x",addr];
    [cmd appendString:[NSString stringWithFormat:@"%02x",addr]];
    [cmd appendString:low_state];
    [cmd appendString:high_state];
    
    if ([uut.lowercaseString containsString:@"fixture"]) {
        [eowyn writeI2CWithString:cmd writeadd:0x48 writelen:3 busId:0];
    }else{
        if ([color.lowercaseString containsString:@"red"]) {
            [eowyn writeI2CWithString:cmd writeadd:0x42 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"green"]){
            [eowyn writeI2CWithString:cmd writeadd:0x44 writelen:3 busId:0];
        }else if ([color.lowercaseString containsString:@"blue"]){
            [eowyn writeI2CWithString:cmd writeadd:0x46 writelen:3 busId:0];
        }
    }

    
    
}


//- (IBAction)send_click_led:(NSButton *)btn {
//    NSString *device = self.popBtnLedType.titleOfSelectedItem;
//    NSString *color = self.popBtnLedCorlor.titleOfSelectedItem;
//
//    if ([device.lowercaseString containsString:@"uut1"]) {
//
//        if ([color.lowercaseString containsString:@"red"]) {
//
//            [self ledWithLowAddr:0xfe high_addr:0xff uut:@"uut1" color:@"red"];
//        }else if([color.lowercaseString containsString:@"green"]){
//            //[self ledWithAddr1:0x02 addr2:0xfd addr3:0xff];
//            [self ledWithLowAddr:0xfd high_addr:0xff uut:@"uut1" color:@"green"];
//        }else if([color.lowercaseString containsString:@"blue"]){
//            //            [self ledWithAddr1:0x02 addr2:0xfb addr3:0xff];
//            [self ledWithLowAddr:0xfb high_addr:0xff uut:@"uut1" color:@"blue"];
//        }
//
//
//
//    }else if ([device.lowercaseString containsString:@"uut2"]){
//        if ([color.lowercaseString containsString:@"red"]) {
//            [self ledWithLowAddr:0xf7 high_addr:0xff uut:@"uut2" color:@"red"];
//            //            [self ledWithAddr1:0x02 addr2:0xf7 addr3:0xff];
//        }else if([color.lowercaseString containsString:@"green"]){
//            [self ledWithLowAddr:0xef high_addr:0xff uut:@"uut2" color:@"green"];
//            //            [self ledWithAddr1:0x02 addr2:0xef addr3:0xff];
//        }else if([color.lowercaseString containsString:@"blue"]){
//            [self ledWithLowAddr:0xdf high_addr:0xff uut:@"uut2" color:@"blue"];
//            //            [self ledWithAddr1:0x02 addr2:0xdf addr3:0xff];
//        }
//
//
//
//    }else if ([device.lowercaseString containsString:@"uut3"]){
//        if ([color.lowercaseString containsString:@"red"]) {
//            [self ledWithLowAddr:0xbf high_addr:0xff uut:@"uut3" color:@"red"];
//            //            [self ledWithAddr1:0x02 addr2:0xbf addr3:0xff];
//        }else if([color.lowercaseString containsString:@"green"]){
//            [self ledWithLowAddr:0x7f high_addr:0xff uut:@"uut3" color:@"green"];
//            //            [self ledWithAddr1:0x02 addr2:0x7f addr3:0xff];
//        }else if([color.lowercaseString containsString:@"blue"]){
//            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut3" color:@"blue"];
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfe];
//        }
//
//
//    }else if ([device.lowercaseString containsString:@"uut4"]){
//        if ([color.lowercaseString containsString:@"red"]) {
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfe];
//            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"red"];
//        }else if([color.lowercaseString containsString:@"green"]){
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xfb];
//            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"green"];
//        }else if([color.lowercaseString containsString:@"blue"]){
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xf7];
//            [self ledWithLowAddr:0xff high_addr:0xfe uut:@"uut4" color:@"blue"];
//        }
//
//
//    }else if ([device.lowercaseString containsString:@"fixture"]){
//        if ([color.lowercaseString containsString:@"red"]) {
//            [self ledWithLowAddr:0xff high_addr:0xef uut:@"fixture" color:@"red"];
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xef];
//        }else if([color.lowercaseString containsString:@"green"]){
//            [self ledWithLowAddr:0xff high_addr:0xdf uut:@"fixture" color:@"green"];
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xdf];
//        }else if([color.lowercaseString containsString:@"blue"]){
//            [self ledWithLowAddr:0xff high_addr:0xbf uut:@"fixture" color:@"blue"];
//            //            [self ledWithAddr1:0x02 addr2:0xff addr3:0xbf];
//        }
//    }
//}


-(ShowingLogVC *)showingLogVC{
    if (!_showingLogVC) {
        _showingLogVC=[ShowingLogVC new];
        
    }
    return _showingLogVC;
}

-(void)define_eowyn_ports{
    
    NSString *path =[[NSString cw_getResourcePath] stringByAppendingPathComponent:@"Eowyn_ports.json"];
    NSDictionary *cmdList = [CWFileManager cw_serializationWithJsonFilePath:path];
    if (cmdList==nil) {
        return;
    }
    UP_GPIO =[[cmdList objectForKey:@"UP_GPIO"] integerValue];
    DOWN_GPIO =[[cmdList objectForKey:@"DOWN_GPIO"]integerValue];
    IN_GPIO =[[cmdList objectForKey:@"IN_GPIO"]integerValue];
    OUT_GPIO =[[cmdList objectForKey:@"OUT_GPIO"]integerValue];
    
    
    elect_magnet =[[cmdList objectForKey:@"elect_magnet"] integerValue];
    FAN_IN_GPIO =[[cmdList objectForKey:@"FAN_IN_GPIO"]integerValue];
    FAN_OUT_GPIO =[[cmdList objectForKey:@"FAN_OUT_GPIO"]integerValue];
    
    UP_SENSOR =[[cmdList objectForKey:@"UP_SENSOR"]integerValue];
    DOWN_SENSOR =[[cmdList objectForKey:@"DOWN_SENSOR"]integerValue];
    IN_SENSOR =[[cmdList objectForKey:@"IN_SENSOR"]integerValue];
    OUT_SENSOR =[[cmdList objectForKey:@"OUT_SENSOR"]integerValue];
    RESET_SENSOR =[[cmdList objectForKey:@"RESET_SENSOR"]integerValue];
    FAN_IN_SENSOR =[[cmdList objectForKey:@"FAN_IN_SENSOR"]integerValue];
    FAN_OUT_SENSOR =[[cmdList objectForKey:@"FAN_OUT_SENSOR"]integerValue];
    
    GPIO_ON =[[cmdList objectForKey:@"GPIO_ON"]integerValue];
    GPIO_OFF =[[cmdList objectForKey:@"GPIO_OFF"]integerValue];
    IN_OUT_SENSOR_ON =[[cmdList objectForKey:@"IN_OUT_SENSOR_ON"]integerValue];
    IN_OUT_SENSOR_OFF =[[cmdList objectForKey:@"IN_OUT_SENSOR_OFF"]integerValue];
    UP_DOWN_SENSOR_ON =[[cmdList objectForKey:@"UP_DOWN_SENSOR_ON"]integerValue];
    UP_DOWN_SENSOR_OFF =[[cmdList objectForKey:@"UP_DOWN_SENSOR_OFF"]integerValue];
    FAN_IN_OUT_SENSOR_ON =[[cmdList objectForKey:@"FAN_IN_OUT_SENSOR_ON"]integerValue];
    FAN_IN_OUT_SENSOR_OFF =[[cmdList objectForKey:@"FAN_IN_OUT_SENSOR_OFF"]integerValue];
    
    
    IN_STATE =[[cmdList objectForKey:@"IN_STATE"]intValue];
    OUT_STATE =[[cmdList objectForKey:@"OUT_STATE"]intValue];
    DOWN_STATE =[[cmdList objectForKey:@"DOWN_STATE"]intValue];
    UNREADY_STATE =[[cmdList objectForKey:@"UNREADY_STATE"]intValue];
    
    DUT1_STATE =[[cmdList objectForKey:@"DUT1_STATE"]intValue];
    DUT2_STATE =[[cmdList objectForKey:@"DUT2_STATE"]intValue];
    DUT3_STATE =[[cmdList objectForKey:@"DUT3_STATE"]intValue];
    DUT4_STATE =[[cmdList objectForKey:@"DUT4_STATE"]intValue];
    eowyn_IP =[cmdList objectForKey:@"Eowyn_IP"];
    NSString *setIps =[cmdList objectForKey:@"AllowSetIps"];
    if (setIps.length) {
        AllowSetIps = setIps;
    }
    
    Eowyn_Count =[[cmdList objectForKey:@"Eowyn_Count"]intValue];
    
//    FCT_IP =[cmdList objectForKey:@"FCT_IP"];
//    DFU_IP =[cmdList objectForKey:@"DFU_IP"];
    
}

-(void)testlog{
    NSLog(@"UP_GPIO:%ld",(long)UP_GPIO);
    NSLog(@"DOWN_GPIO:%ld",(long)DOWN_GPIO);
    NSLog(@"IN_GPIO:%ld",(long)IN_GPIO);
    NSLog(@"OUT_GPIO:%ld",(long)OUT_GPIO);
    NSLog(@"elect_magnet:%ld",(long)elect_magnet);
    NSLog(@"FAN_IN_GPIO:%ld",(long)FAN_IN_GPIO);
    NSLog(@"FAN_OUT_GPIO:%ld",(long)FAN_OUT_GPIO);
    NSLog(@"UP_SENSOR:%ld",(long)UP_SENSOR);
    NSLog(@"DOWN_SENSOR:%ld",(long)DOWN_SENSOR);
    
    NSLog(@"IN_SENSOR:%ld",(long)IN_SENSOR);
    NSLog(@"OUT_SENSOR:%ld",(long)OUT_SENSOR);
    NSLog(@"RESET_SENSOR:%ld",(long)RESET_SENSOR);
    NSLog(@"FAN_IN_SENSOR:%ld",(long)FAN_IN_SENSOR);
    NSLog(@"FAN_OUT_SENSOR:%ld",(long)FAN_OUT_SENSOR);
    
    
    NSLog(@"GPIO_ON:%ld",(long)GPIO_ON);
    NSLog(@"GPIO_OFF:%ld",(long)GPIO_OFF);
    NSLog(@"IN_OUT_SENSOR_ON:%ld",(long)IN_OUT_SENSOR_ON);
    NSLog(@"IN_OUT_SENSOR_OFF:%ld",(long)IN_OUT_SENSOR_OFF);
    NSLog(@"UP_DOWN_SENSOR_ON:%ld",(long)UP_DOWN_SENSOR_ON);
    NSLog(@"UP_DOWN_SENSOR_OFF:%ld",(long)UP_DOWN_SENSOR_OFF);
    NSLog(@"FAN_IN_OUT_SENSOR_ON:%ld",(long)FAN_IN_OUT_SENSOR_ON);
    NSLog(@"FAN_IN_OUT_SENSOR_OFF:%ld",(long)FAN_IN_OUT_SENSOR_OFF);
    
    
    NSLog(@"IN_STATE:%ld",(long)IN_STATE);
    NSLog(@"OUT_STATE:%ld",(long)OUT_STATE);
    NSLog(@"DOWN_STATE:%ld",(long)DOWN_STATE);
    NSLog(@"UNREADY_STATE:%ld",(long)UNREADY_STATE);
    
}
- (IBAction)click_scriptStop:(id)sender {
    is_run_scipt_stop=YES;
}
-(NSInteger)stringToIndex:(NSString *)cmd{
    if ([cmd.lowercaseString containsString:@"in"]) {
        return 0;
    }else if ([cmd.lowercaseString containsString:@"out"]){
        return 1;
    }else if ([cmd.lowercaseString containsString:@"down"]){
        return 2;
    }else if ([cmd.lowercaseString containsString:@"up"]){
        return 3;
    }
    return 0;
}

- (IBAction)clickScriptStart:(id)sender {
    is_run_scipt_stop = NO;
    NSString *file = self.popBtnScript.titleOfSelectedItem;
    NSString *path =[[NSString cw_getResourcePath] stringByAppendingPathComponent:file];
    NSDictionary *cmdList = [CWFileManager cw_serializationWithJsonFilePath:path];
    if (cmdList==nil) {
        return;
    }
    NSDictionary *par = [cmdList objectForKey:@"parameters"];
    float commandDelay= [[par objectForKey:@"commandDelay"] floatValue];
    NSInteger times=[[par objectForKey:@"loopTimes"] integerValue];
    
    NSArray *arr = [cmdList objectForKey:@"commands"];
    
    // dispatch_async(dispatch_get_global_queue(0, 0), ^{
    for (int i =0; i<times; i++) {
        
        for (int j =0;j<arr.count;j++){
            if (is_run_scipt_stop) {
                times=0;
                break;
            }
            NSString *command = arr[j];
            NSInteger index = [self stringToIndex:command];
            //[self.popDebug selectItemAtIndex]=index;
            [self.popDebug selectItemAtIndex:index];
            [self clickSend:self.btnSend];
            
            [NSThread sleepForTimeInterval:commandDelay];
            
        }
    }
    
    
}
void thread_led(Eowyn * eowyn){
    while (true) {
        if (sign){
            set_button_led(eowyn, @"open");
            [NSThread sleepForTimeInterval:1];
            set_button_led(eowyn, @"close");
            [NSThread sleepForTimeInterval:1];
        }else{
            set_button_led(eowyn, @"close");
        }
    }
}



void trayUp(Eowyn * eowyn){
    int sta = checkPositionSensor(eowyn);
    //    show_log(@"state:%d",sta);
    if(sta == UNREADY_STATE || sta == IN_STATE){
        show_log(@"Already UP, PASS.");
        //        return @"up;DONE;";
    }
    [eowyn writeIO:DOWN_GPIO value:GPIO_OFF];
    [eowyn writeIO:UP_GPIO value:GPIO_ON];
    

}


void trayDown(Eowyn * eowyn)
{
    //    int dutstate = checkDUTSensor(eowyn);//放在最前面，防止I2C被选错
    int sta = checkPositionSensor(eowyn);
    
    if(sta == DOWN_STATE){
        return;
    }else{
        //        if(dutstate == 0){
        if(sta == IN_STATE){                     //In first
            [eowyn writeIO:UP_GPIO value:GPIO_OFF];
            [eowyn writeIO:DOWN_GPIO value:GPIO_ON];

        }else {
            show_log(@"Please IN first!");
        }

    }
}

void trayIn(Eowyn * eowyn)
{
    int sta = checkPositionSensor(eowyn);
    //    show_log(@"state:%d",sta);
    //    CTLog(CTLOG_LEVEL_INFO,@"Fixture IN.");
    
    if(sta == IN_STATE || sta == DOWN_STATE){
        //        return @"in;DONE;";
        return;
    }
    
    [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
    [eowyn writeIO:IN_GPIO value:GPIO_ON];

}

void trayOut(Eowyn * eowyn)
{
    
    int sta = checkPositionSensor(eowyn);

    if(sta == OUT_STATE){
        //        return @"out;DONE;";
        return;
    }
    if( sta == IN_STATE || sta == UNREADY_STATE){                //up first
        
        [eowyn writeIO:IN_GPIO value:GPIO_OFF];
        [eowyn writeIO:OUT_GPIO value:GPIO_ON];

        
    }else {
        show_log(@"Please UP first!");
    }
}




- (IBAction)loopStart:(NSButton *)btn {
    NSInteger loopCount = [self.textField_loopCount.stringValue integerValue];
    if (!loopCount) {
        return;
    }
    is_stop = NO;
    int currentPosition = checkPositionSensor(eowyn);
    int lastPosition = currentPosition;
    self.btnSend.enabled = NO;
    for (int i =0; i<loopCount; i++) {
        //                show_log(@"lastPosition:%d  currentPosition:%d",lastPosition,currentPosition);
        if (is_stop) {
            break;
        }
        lastPosition = currentPosition;
        currentPosition = checkPositionSensor(eowyn);
        
        if(currentPosition == OUT_STATE){      //out
            // count++;
            show_log([NSString stringWithFormat:@"######################Loop Count: %d######################",i+1]);
            trayIn(eowyn);
            while(1){
                [NSThread sleepForTimeInterval:0.1];
                lastPosition = currentPosition;
                currentPosition = checkPositionSensor(eowyn);
                if(currentPosition == IN_STATE){
                    break;
                }
            }
        }
        if(currentPosition == UNREADY_STATE){      //out
            trayOut(eowyn);
            // count ++;
            show_log([NSString stringWithFormat:@"Current count: %d",i]);
            
            while(1){
                [NSThread sleepForTimeInterval:0.1];
                lastPosition = currentPosition;
                currentPosition = checkPositionSensor(eowyn);
                if(currentPosition == OUT_STATE){
                    break;
                }
            }
        }
        if(lastPosition == UNREADY_STATE && currentPosition == IN_STATE){      //in
            [NSThread sleepForTimeInterval:1];
            trayDown(eowyn);
            while(1){
                [NSThread sleepForTimeInterval:0.1];
                lastPosition = currentPosition;
                currentPosition = checkPositionSensor(eowyn);
                if(currentPosition == DOWN_STATE){
                    break;
                }
            }
        }
        if(currentPosition == IN_STATE){      //in
            [NSThread sleepForTimeInterval:1];
            trayOut(eowyn);
            while(1){
                [NSThread sleepForTimeInterval:0.1];
                lastPosition = currentPosition;
                currentPosition = checkPositionSensor(eowyn);
                if(currentPosition == OUT_STATE){
                    break;
                }
            }
        }
        if(currentPosition == DOWN_STATE){      //down
            trayUp(eowyn);
            
            while(1){
                [NSThread sleepForTimeInterval:0.1];
                lastPosition = currentPosition;
                currentPosition = checkPositionSensor(eowyn);
                if(currentPosition == IN_STATE){
                    break;
                }
            }
        }
        //                sensor = 0;
        //                int timeInterval = 0.1;
        [NSThread sleepForTimeInterval:1];
        
    }
    self.btnSend.enabled = YES;
}


- (IBAction)loopStop:(NSButton *)btn {
    is_stop=YES;
}
- (IBAction)clickSend:(NSButton *)sender {
    //self.btnSend.enabled = NO;
    NSInteger b = self.popDebug.indexOfSelectedItem + 1;
    // dispatch_async(dispatch_get_global_queue(0, 0), ^{
    if(b == 1){
        show_log(@"-----------------IN-----------------");
        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];//0
        if (up_io_stat != UP_DOWN_SENSOR_ON){//#UP_DOWN_SENSOR_ON  1
            show_log(@"UP SENSOR NO ON\r");
            //self.btnSend.enabled = YES;
            return;
        }
        
        show_log([NSString stringWithFormat:@"UP SENSOR STATS IS %d\r",up_io_stat]);
        [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
        [eowyn writeIO:IN_GPIO value:GPIO_ON];
        
        [NSThread sleepForTimeInterval:2.0];
        int sleep =2;
        int timeout =8;
        while (1) {
            
            if (sleep >=timeout) {
                break;
            }
            
            ATDeviceDIOType in_sensor_stat = [eowyn readIO:IN_SENSOR];
            if (in_sensor_stat == IN_OUT_SENSOR_ON){
                
                [eowyn writeIO:elect_magnet value:GPIO_ON];//elect_magnet 12
                show_log(@"IN OK\r");
                break;
                
                //                        show_log(@"elect_magnet ON\r");
            }
            else{
                [NSThread sleepForTimeInterval:1.0];
                sleep = sleep+1;
                show_log(@"IN ERROR\r");
                
            }
        }
        show_log([NSString stringWithFormat:@"sleep %ds\r",sleep]);
        
        checkPositionSensor(eowyn);
    }else if(b == 2){
        show_log(@"-----------------OUT-----------------");
        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
        show_log([NSString stringWithFormat:@"UP SENSOR STAT %d\r",up_io_stat]);
        if (up_io_stat != UP_DOWN_SENSOR_ON){
            show_log(@"UP SENSOR IS NOT ON\r");
            //            self.btnSend.enabled = YES;
            return;
        }
        else{
            
            [eowyn writeIO:elect_magnet value:GPIO_OFF];
            show_log(@"elect_magnet OFF\r");
            show_log(@"sleep 1s\r");
            [NSThread sleepForTimeInterval:1];
        }
        [eowyn writeIO:IN_GPIO value:GPIO_OFF];
        [eowyn writeIO:OUT_GPIO value:GPIO_ON];
        show_log(@"sleep 4s\r");
        [NSThread sleepForTimeInterval:4];
        for (int j=0; j<2; j++) {
            
            ATDeviceDIOType out_io_stat = [eowyn readIO:OUT_SENSOR];
            if (out_io_stat==IN_OUT_SENSOR_ON){
                printf("OUT SENSOR IS ON\r");
                [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
                break;
            }
            show_log(@"sleep 1.5s\r");
            [NSThread sleepForTimeInterval:1.5];
            
        }
        checkPositionSensor(eowyn);
        //uint32 begin = [[NSDate date] timeIntervalSince1970];
        //                    [NSThread sleepForTimeInterval:5.0];
        
        //        while (true) {
        //            ATDeviceDIOType out_io_stat = [eowyn readIO:OUT_SENSOR];
        //            if (out_io_stat==IN_OUT_SENSOR_ON){
        //                printf("OUT SENSOR IS ON\r");
        //                [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
        //                break;
        //            }
        //            //                            uint32 end = [[NSDate date] timeIntervalSince1970]*1000;
        ////            uint32 end = [[NSDate date] timeIntervalSince1970];
        ////            if (end - begin>5){
        ////                printf("OUT SENSOR IS NOT ON\r");
        ////                [eowyn writeIO:OUT_GPIO value:GPIO_OFF];
        ////            }
        //        }
        
    }else if(b == 3){
        show_log(@"-----------------DOWN-----------------");
        ATDeviceDIOType in_io_stat = [eowyn readIO:IN_SENSOR];
        show_log([NSString stringWithFormat:@"IN SENSOR STAT IS %d\r",in_io_stat]);
        if (in_io_stat != IN_OUT_SENSOR_ON){
            show_log(@"IN SENSOR IS NOT ON\r");
            //            self.btnSend.enabled = YES;
            return;
        }
        
        [eowyn writeIO:UP_GPIO value:GPIO_OFF];
        [eowyn writeIO:DOWN_GPIO value:GPIO_ON];
        show_log(@"sleep 3s\r");
        [NSThread sleepForTimeInterval:3.0];
        ATDeviceDIOType down_io_stat = [eowyn readIO:DOWN_SENSOR];
        if (down_io_stat == UP_DOWN_SENSOR_ON){
            show_log(@"DOWN SENSOR IS ON\r");
        }
        else{
            show_log(@"DOWN SENSOR IS NOT ON\r");
        }
        checkPositionSensor(eowyn);
    }else if(b == 4){
        //                    ATDeviceDIOType in_io_stat = [eowyn readIO:IN_SENSOR];
        //                    if (in_io_stat != IN_OUT_SENSOR_ON){
        //                        show_log(@"IN SENSOR IS NOT ON\r");
        //                        break;
        //                    }
        show_log(@"-----------------UP-----------------");
        [eowyn writeIO:DOWN_GPIO value:GPIO_OFF];
        [eowyn writeIO:UP_GPIO value:GPIO_ON];
        show_log(@"sleep 3s\r");
        [NSThread sleepForTimeInterval:3.0];
        ATDeviceDIOType up_io_stat = [eowyn readIO:UP_SENSOR];
        if (up_io_stat == UP_DOWN_SENSOR_ON){
            show_log(@"UP SENSOR IS ON\r");
        }
        else{
            show_log(@"UP SENSOR IS NOT ON\r");
        }
        checkPositionSensor(eowyn);
    }else if(b == 5){
        show_log(@"-----------------CHECK CURRENT POSITION-----------------");
        checkPositionSensor(eowyn);
    }else if(b == 6){
        show_log(@"-----------------CHECK DUT STATE-----------------");
        int sta = checkDUTSensor(eowyn);
        if(sta!=0){
            show_log(@"DUT SENSOR ERROR");
        }else{
            show_log(@"DUT SENSOR Right");
        }
    }else if(b == 7){
        show_log(@"-----------------RREAD TEMPERATURE-----------------");
        //                    float temp = readTemp(eowyn);
        //                    show_log(@"\nCurrent Temperature Is:\n%f",temp);
    }else if(b == 8){
        show_log(@"-----------------READ TEMPERATURE-----------------");
        //                    readFanSpeed(eowyn);
    }else if(b == 9){
        show_log(@"-----------------READ FAN SPEED-----------------");
        //                    runFanRpm(eowyn);
    }else if(b == 10){
        show_log(@"-----------------RUN FAN RPM-----------------");
        [eowyn writeIO:elect_magnet value:GPIO_ON];
        [NSThread sleepForTimeInterval:1];
        show_log(@"elect_magnet on!\r");
    }else if(b == 11){
        show_log(@"-----------------ELECT_MAGNET ON-----------------");
        [eowyn writeIO:elect_magnet value:GPIO_OFF];
        [NSThread sleepForTimeInterval:1];
        show_log(@"elect_magnet off!\r");
    }else if (b == 12){
        show_log(@"-----------------ELECT_MAGNET OFF-----------------");
        uut1led(eowyn, @"pass");
        uut2led(eowyn, @"pass");
        uut3led(eowyn, @"pass");
        uut4led(eowyn, @"pass");
        stateled(eowyn, @"pass");
        
        [NSThread sleepForTimeInterval:3];
        uut1led(eowyn, @"fail");
        uut2led(eowyn, @"fail");
        uut3led(eowyn, @"fail");
        uut4led(eowyn, @"fail");
        stateled(eowyn, @"fail");
        
        [NSThread sleepForTimeInterval:3];
        uut1led(eowyn, @"ready");
        uut2led(eowyn, @"ready");
        uut3led(eowyn, @"ready");
        uut4led(eowyn, @"ready");
        stateled(eowyn, @"ready");
        
        [NSThread sleepForTimeInterval:3];
        uut1led(eowyn, @"idle");
        uut2led(eowyn, @"idle");
        uut3led(eowyn, @"idle");
        uut4led(eowyn, @"idle");
        stateled(eowyn, @"ready");
        
        [NSThread sleepForTimeInterval:3];
        uut1led(eowyn, @"init");
        uut2led(eowyn, @"init");
        uut3led(eowyn, @"init");
        uut4led(eowyn, @"init");
        stateled(eowyn, @"init");
        
    }else if (b == 13){
        show_log(@"-----------------CHECK LED-----------------");
        //                    while (true) {
        set_button_led(eowyn, @"open");
        [NSThread sleepForTimeInterval:1];
        set_button_led(eowyn, @"close");
        [NSThread sleepForTimeInterval:1];
        set_button_led(eowyn, @"open");
        [NSThread sleepForTimeInterval:1];
        set_button_led(eowyn, @"close");
        [NSThread sleepForTimeInterval:1];
        set_button_led(eowyn, @"open");
        [NSThread sleepForTimeInterval:1];
        set_button_led(eowyn, @"close");
        [NSThread sleepForTimeInterval:1];
        //                    }
    }
    else if (b == 14){
        show_log(@"-----------------CHECK RESET BUTTON-----------------");
        //                    while (true) {
        //
        //                    ATDeviceDIOType in_io_stat = [eowyn readIO:RESET_SENSOR];
        //                    if (in_io_stat == 0){
        //                        uint32 start = [[NSDate date]timeIntervalSince1970];
        //                        uint32 end = 0;
        //                        while (true) {
        //                            [NSThread sleepForTimeInterval:0.1];
        //                            in_io_stat = [eowyn readIO:RESET_SENSOR];
        //
        //                            end = [[NSDate date]timeIntervalSince1970];
        //
        ////                            if (in_io_stat !=0 && end - start>1.5){
        ////                                break;
        //////                                set_button_led(eowyn, @"close");
        ////                            }
        ////                            if (in_io_stat ==0 && end - start>5){
        ////                                show_log(@"time ----->%d",end-start);
        ////                                break;
        ////
        ////                            }
        //                            if (in_io_stat !=0 || end - start>5){
        //                                show_log(@"time ----->%d",end-start);
        //                                break;
        //
        //                            }
        //                    }
        //                        if (end - start>5){
        //                            show_log(@"BUtton Press more than 5S");
        //                            UP(eowyn);
        //                            [NSThread sleepForTimeInterval:1];
        //                            OUT(eowyn);
        //                        }
        //                        else if (end - start>1.5){
        //                            show_log(@"BUtton Press more than 1.5S");
        //                            set_button_led(eowyn, @"close");
        //
        //                        }
        //                    }
        //                    }
    }else if (b == 15){
        show_log(@"-----------------FAN MOVE IN-----------------");
        [eowyn writeIO:FAN_IN_GPIO value:GPIO_ON];
        [eowyn writeIO:FAN_OUT_GPIO value:GPIO_OFF];
        ATDeviceDIOType fan_in_io_stat = [eowyn readIO:FAN_IN_SENSOR];
        ATDeviceDIOType fan_out_io_stat = [eowyn readIO:FAN_OUT_SENSOR];
        
        show_log([NSString stringWithFormat:@"fan_in_io_stat: %d",fan_in_io_stat]);
        show_log([NSString stringWithFormat:@"fan_out_io_stat: %d",fan_out_io_stat]);
        
        if(fan_in_io_stat == FAN_IN_OUT_SENSOR_ON && fan_out_io_stat == FAN_IN_OUT_SENSOR_OFF){
            show_log(@"FAN MOVE IN OK");
        }
    }else if (b == 16){
        show_log(@"-----------------FAN MOVE OUT-----------------");
        [eowyn writeIO:FAN_IN_GPIO value:GPIO_OFF];
        [eowyn writeIO:FAN_OUT_GPIO value:GPIO_ON];
        ATDeviceDIOType fan_in_io_stat = [eowyn readIO:FAN_IN_SENSOR];
        ATDeviceDIOType fan_out_io_stat = [eowyn readIO:FAN_OUT_SENSOR];
        
        show_log([NSString stringWithFormat:@"fan_in_io_stat: %d",fan_in_io_stat]);
        show_log([NSString stringWithFormat:@"fan_out_io_stat: %d",fan_out_io_stat]);
        
        if(fan_in_io_stat == FAN_IN_OUT_SENSOR_OFF && fan_out_io_stat == FAN_IN_OUT_SENSOR_ON){
            show_log(@"FAN MOVE OUT OK");
        }
    }else if (b == 17){
        //[eowyn writeI2C:@"06f0ff" writeadd:0x44 writelen:3];
        show_log(@"-----------------LED TEST1-----------------");
        
        unsigned char data[3] ;
        memset(data, 0, 3);
        data[0]=0x02;
        unsigned char stat_1 = [eowyn readI2C:0x42 readlen:2];
        stat_1 = stat_1 & 0xfe ;
        data[1] =stat_1;
        data[2]=0xff;
        
        
        [eowyn writeI2C:data writeadd:0x42 writelen:3 busId:0];
        
    }
    else{
        b = 0 ;
        show_log(@"-----------------Wrong Command!-----------------");
        
    }
    
}

void stateled(Eowyn * eowyn,NSString* mode){                  //actually UUT1
    [eowyn writeI2C:@"02" writeadd:0x42 writelen:1];
    unsigned char stat_1 = [eowyn readI2C:0x42 readlen:2];
    
    if([mode isEqualToString:@"ready"]){                    //blue
        stat_1 = (stat_1 & 0x8f) + 0x30;
        
    }else if([mode isEqualToString:@"pass"]){               //green
        stat_1 = (stat_1 & 0x8f) + 0x50;
        
    }else if ([mode isEqualToString:@"fail"]){              //red
        stat_1 = (stat_1 & 0x8f) + 0x60;
        
    }else if ([mode isEqualToString:@"init"]){              //init
        stat_1 = stat_1 | 0x70;
        
    }else{
        show_log(@"Error Mode!");
        return;
    }
    
    NSString *x42_cmd = [NSString stringWithFormat:@"03%02x",stat_1];
    
    show_log([NSString stringWithFormat:@"uut2led ledRecord_x42 %@",x42_cmd]);
    [eowyn writeI2C:x42_cmd writeadd:0x42 writelen:2];
    
}

-(const char* )stringFromHexString:(NSString *)hexString
{
    //    NSString *str=[NSString stringWithCString:hexString encoding:NSUTF8StringEncoding];
    char *myBuffer = (char *)malloc((int)[hexString length] / 2 + 1);
    bzero(myBuffer, [hexString length] / 2 + 1);
    for (int i = 0; i < [hexString length] - 1; i += 2) {
        unsigned int anInt;
        NSString * hexCharStr = [hexString substringWithRange:NSMakeRange(i, 2)];
        NSScanner * scanner = [[NSScanner alloc] initWithString:hexCharStr];
        [scanner scanHexInt:&anInt];
        myBuffer[i / 2] = (char)anInt;
    }
    //    NSString *unicodeString = [NSString stringWithCString:myBuffer encoding:4];
    //    NSLog(@"------字符串=======%@",unicodeString);
    return myBuffer;
}
- (IBAction)write_send:(NSButton *)sender {
    
    NSString *add_str = self.addWriteView.stringValue;
    NSString *cmd = self.cmdWriteView.stringValue;
    NSString * bus_id = self.busIdView.stringValue;
    if (add_str.length ==0 ) {//|| cmd.length ==0 || bus_id.length==0
        
        add_str = self.addWriteView.placeholderString;
    }
    if (cmd.length ==0 ) {//|| cmd.length ==0 || bus_id.length==0
        cmd = self.cmdWriteView.placeholderString;
        
    }

    if (bus_id.length ==0 ) {//|| cmd.length ==0 || bus_id.length==0
        bus_id = self.busIdView.placeholderString;
        
    }

    
    if (add_str.length !=4 || cmd.length %2 == 1) {
        
        return;
    }
    
    int len = (int)cmd.length/2;
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x42 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x44 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x46 writelen:3 busId:0];
    [eowyn writeI2CWithString:@"02ffff" writeadd:0x48 writelen:3 busId:0];
    
    //先以16为参数告诉strtoul字符串参数表示16进制数字，然后使用0x%X转为数字类型
    //    char add_int = strtoul([add_str UTF8String],0,16);
    [eowyn writeI2CWithString:cmd writeadd:strtoul([add_str UTF8String],0,16) writelen:len busId:bus_id.intValue];
    // [eowyn writeI2CWithString:@"02DFFF" writeadd:0x42 writelen:3 busId:0];
    
    
}
-(unsigned char)cw_stringToHex:(NSString *)add_str{
    NSInteger len = add_str.length;
    unsigned char aucKey[len/2] ;
    memset(aucKey, 0, sizeof(aucKey));
    
    int idx = 0;
    for (int j=0; j<len; j+=2)
    {
        NSString *hexStr = [add_str substringWithRange:NSMakeRange(j, 2)];
        NSScanner *scanner = [NSScanner scannerWithString:hexStr];
        unsigned long long longValue ;
        [scanner scanHexLongLong:&longValue];
        unsigned char c = longValue;
        aucKey[idx] = c;
        idx++;
    }
    
    return aucKey[len/2];
}

@end
