//
//  InputUserInfoViewController.h
//  BodyScaleProduction
//
//  Created by Go Salo on 14-3-14.
//  Copyright (c) 2014年 Go Salo. All rights reserved.
//

#import "AQBaseViewController.h"
#import "DataDetailViewController.h"

@interface InputUserInfoViewController : AQBaseViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil type:(FlowType)type checkCode:(NSString *)checkCode;

@property (nonatomic, copy) NSString *loginName;
@property (nonatomic, copy) NSString *loginPassword;

@end
