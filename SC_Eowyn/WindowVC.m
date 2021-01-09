//
//  WindowVC.m
//  SC_Eowyn
//
//  Created by ciwei luo on 2020/3/31.
//  Copyright © 2020 ciwei luo. All rights reserved.
//

#import "WindowVC.h"
#import "ViewController.h"
#import "ShowingLogVC.h"
#import <CWGeneralManager/NSString+Extension.h>
#import <CWGeneralManager/CWFileManager.h>
@interface WindowVC ()

@end

@implementation WindowVC

- (void)windowDidLoad {
    [super windowDidLoad];
    NSString *path =[[NSString cw_getResourcePath] stringByAppendingPathComponent:@"Eowyn_ports.json"];
    NSDictionary *cmdList = [CWFileManager cw_serializationWithJsonFilePath:path];
    int count =[[cmdList objectForKey:@"Eowyn_Count"] intValue];
   
    if (count<1) {
        count =1;
    }
//    else if (count>8){
//        count =8;
//    }
    
    NSMutableArray *Vcs = [[NSMutableArray alloc]init];
    for (int i = 0; i<count; i++) {
        ViewController *vc =[[ViewController alloc]init];
        vc.title = [NSString stringWithFormat:@"Vc%d",i+1];
        [Vcs addObject:vc];
    }
    if (Vcs.count == 1) {
        [self cw_addViewController:Vcs[0] logVC:[ShowingLogVC new]];
    }else{
        [self cw_addViewControllers:Vcs];
    }
    
 
    
    //
    
}



@end
