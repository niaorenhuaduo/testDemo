//
//  AppDelegate.h
//  BodyScale
//
//  Created by August on 14-9-27.
//  Copyright (c) 2014年 August. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RESideMenu.h>
#import "BodyScaleBTInterface.h"
@interface AppDelegate : UIResponder <UIApplicationDelegate,RESideMenuDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) RESideMenu *sideMenuViewController;
@property (nonatomic, strong) BlueToothHelper *blueToothHelper;

@property (nonatomic, assign) NSInteger connectType;
@property (nonatomic, strong) NSString *deviceId;

+ (AppDelegate *)currentAppDelegate;




@end
