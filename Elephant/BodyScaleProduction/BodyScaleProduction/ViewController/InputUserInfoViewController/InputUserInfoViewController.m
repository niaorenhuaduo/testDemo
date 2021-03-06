//
//  InputUserInfoViewController.m
//  BodyScaleProduction
//
//  Created by Go Salo on 14-3-14.
//  Copyright (c) 2014年 Go Salo. All rights reserved.
//

#import "InputUserInfoViewController.h"
#import "LoginViewController.h"
#import "ScaleUserDataEntity.h"
#import "DataDetailViewController.h"
#import "SLPickerView.h"
#import "BTModel.h"
#import "AQPickerView.h"
#import "AppDelegate.h"

typedef NS_ENUM(NSInteger, PageControlToPage) {
    PageControlToPageNone,
    PageControlToPageNext,
    PageControlToPageLast
};

typedef NS_ENUM(NSInteger, SelectedUserSex) {
    SelectedUserSexNone = -1,
    SelectedUserSexFemales = 0,
    SelectedUserSexMales = 1,
};

@interface InputUserInfoViewController ()<SLPickerViewDataSource, SLPickerViewDelegate, AQPickerViewDelegate>

@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;

// PAGE 1
@property (weak, nonatomic) IBOutlet UIImageView *selectGenderViewPhotoImageViewLeft;
@property (weak, nonatomic) IBOutlet UIImageView *selectGenderViewPhotoImageViewRight;

// PAGE 2
@property (weak, nonatomic) IBOutlet UILabel *ageLabel;
@property (weak, nonatomic) IBOutlet UIImageView *inputOtherInfoViewPhotoImageView;
@property (weak, nonatomic) IBOutlet UIView *birthView;
@property (weak, nonatomic) IBOutlet UILabel *birthLabel;
@property (weak, nonatomic) IBOutlet UILabel *ageTextLabel;
@property (weak, nonatomic) IBOutlet UILabel *birthTextLabel;

// PAGE 3
@property (weak, nonatomic) IBOutlet UILabel *heightLabel;
@property (weak, nonatomic) IBOutlet UIImageView *bodyImageView;

// Bottom Bar
@property (weak, nonatomic) IBOutlet UIView *lastAndNextBottomBar;
@property (weak, nonatomic) IBOutlet UIView *inputNameBottomBar;
@property (weak, nonatomic) IBOutlet UIButton *lastStepButton;

@end

@implementation InputUserInfoViewController {
    SelectedUserSex         _selectedUserSex;
    NSInteger               _pageNumber;
    SLPickerView            *_agePickerView;
    SLPickerView            *_heightPickerView;
    AQPickerView            *_birthdayPickerView;
    
    UserInfoEntity          *_userInfoEntity;
    BOOL                    _firstAppear;
    BOOL                    _hasAgePicker;
    
    FlowType _type;
    NSString *_checkCode;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [GloubleProperty sharedInstance].registering = NO;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil type:(FlowType)type checkCode:(NSString *)checkCode {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = @"我的个人资料";
        _checkCode = checkCode;
        _type = type;
        _selectedUserSex = SelectedUserSexNone;
        _userInfoEntity  = [UserInfoEntity new];
        _firstAppear = YES;
        _pageNumber = 1;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self configXib];
    
    if (![[GloubleProperty sharedInstance] currentUserEntity]) {
        self.navigationItem.leftBarButtonItem = nil;
    }
    
    [GloubleProperty sharedInstance].registering = YES;
    
    
    
    
}



- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (_firstAppear) {
        _firstAppear = NO;
    } else if (_pageNumber == 3) {
        [self.scrollView setContentOffset:CGPointMake(640, 0)];
        _lastAndNextBottomBar.alpha = 1;
    }
}

- (void)configXib {
    _hasAgePicker = NO;
    
    CGFloat scale = (APPLICATION_HEIGHT - 20) / 568.0f;
    
    self.bodyImageView.frame = CGRectMake(self.bodyImageView.frame.origin.x,
                                          self.bodyImageView.frame.origin.y,
                                          self.bodyImageView.width * scale,
                                          self.bodyImageView.height * scale);
    
    BOOL isIOS7_OR_LATER = [[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0f;
    
    switch (_type) {
        case FlowTypeRegister: {
            _birthdayPickerView = [[AQPickerView alloc] initWithFrame:CGRectZero];
            _birthdayPickerView.delegate = self;
            [self.view addSubview:_birthdayPickerView];
        }
            break;
        case FlowTypeGuest: {
            self.inputNameBottomBar.hidden = YES;
            
            _hasAgePicker = YES;
            
            _agePickerView = [[SLPickerView alloc] initWithFrame:CGRectMake(0,
                                                                            APPLICATION_HEIGHT - 2 * self.lastAndNextBottomBar.height - 44 - (isIOS7_OR_LATER ? 20 : 0),
                                                                            SCREEN_WIDTH,
                                                                            self.lastAndNextBottomBar.height)
                                                        delegate:self
                                                      dataSource:self
                                                            type:SLPickerViewTypeHorizontal];
            _agePickerView.alpha = 0;
            [_agePickerView setCurrentIndex:15];
            [self.view addSubview:_agePickerView];
            
            self.ageLabel.hidden = NO;
            self.ageTextLabel.hidden = NO;
            self.birthTextLabel.hidden = YES;
            self.birthView.hidden = YES;
        }
            break;
        case FlowTypeAddUser: {
            _birthdayPickerView = [[AQPickerView alloc] initWithFrame:CGRectZero];
            _birthdayPickerView.delegate = self;
            [self.view addSubview:_birthdayPickerView];
            self.lastStepButton.hidden = YES;
        }
            break;
        default:
            break;
    }
    
    _heightPickerView = [[SLPickerView alloc] initWithFrame:CGRectMake(SCREEN_WIDTH * 3 - 69 - 30,
                                                                       self.bodyImageView.top,
                                                                       69,
                                                                       self.bodyImageView.height - 15)
                                                   delegate:self
                                                 dataSource:self
                                                       type:SLPickerViewTypeVertical];
    _heightPickerView.alpha = 0;
    [self.scrollView addSubview:_heightPickerView];
}

#pragma mark - Actions
- (IBAction)tapBirthView:(id)sender {
    NSLog(@"%s %@",__PRETTY_FUNCTION__,_birthdayPickerView);
    [_birthdayPickerView show];
}

- (IBAction)lasetStepButtonAction:(id)sender {
    [self pageControlToPage:PageControlToPageLast];
}

- (IBAction)nextStepButtonAction:(id)sender {
    [self pageControlToPage:PageControlToPageNext];
}

- (IBAction)loginButtonAction:(id)sender {
    LoginViewController *loginVC = [[LoginViewController alloc] initWithNibName:@"LoginViewController" bundle:nil];
    [self.navigationController pushViewController:loginVC animated:YES];
}

- (IBAction)tapLeftPhotoAction:(id)sender {
    _selectedUserSex = SelectedUserSexMales;
    [self pageControlToPage:PageControlToPageNext];
}

- (IBAction)tapRightPhotoAction:(id)sender {
    _selectedUserSex = SelectedUserSexFemales;
    [self pageControlToPage:PageControlToPageNext];
}



#pragma mark - Private Method
- (void)pageControlToPage:(PageControlToPage)topage {
    
    NSLog(@"control page is %d",_pageNumber);
    
    PageControlToPage control = topage;
    switch (topage) {
        case PageControlToPageLast:
            if (_pageNumber == 1) {
                control = PageControlToPageNone;
            } else {
                _pageNumber --;
            }
            break;
        case PageControlToPageNext:
            if (_pageNumber == 3) {
                if (![self dataVerify]) {  // 数据判断
                    return;
                }
                
                switch (_type) {
                    case FlowTypeAddUser: {
                        NSLog(@"userEntity loginName is %@",_userInfoEntity.UI_loginName);
                        _userInfoEntity.UI_loginName = self.loginName;
                        _userInfoEntity.UI_loginPwd = self.loginPassword;
                        
                        [[InterfaceModel sharedInstance] userRegisterWithUser:_userInfoEntity validCode:_checkCode callBack:^(int code, id userInfo, NSString *errorMsg) {
                            
                            NSLog(@"erroe=r mesage is %@ user info is %@",errorMsg,userInfo);
                            
                            if (userInfo) {
                                AppDelegate *delegate =
                                (AppDelegate *)[UIApplication sharedApplication].delegate;
                                [delegate mainViewAppearWithUserInfo:userInfo];
                            }
                            
                            
                        }];
                    }
                        break;
                    default: {
                        DataDetailViewController *dataDetailVC = [[DataDetailViewController alloc] initWithNibName:@"DataDetailViewController" bundle:nil userInfoEntity:_userInfoEntity type:_type];
                        [self.navigationController pushViewController:dataDetailVC animated:YES];
                    }
                        break;
                }
                control = PageControlToPageNone;
            } else {
                if (![self dataVerify]) {  // 数据判断
                    return;
                }
                _pageNumber ++;
            }
            break;
        default:
            break;
    }
    
    if (_pageNumber == 1) {                                                 // to page 1
        [UIView animateWithDuration:0.6f animations:^{
            self.inputNameBottomBar.alpha = 1;
            self.lastAndNextBottomBar.alpha = 0;
            _agePickerView.alpha = 0;
            
            if (_type == FlowTypeGuest) {
                self.inputNameBottomBar.hidden = YES;
            }
        }];
    } else if (_pageNumber == 2 && control == PageControlToPageNext) {      // page 1 to page 2
        if (_selectedUserSex == SelectedUserSexMales) {
            [_heightPickerView setCurrentIndex:45];
            self.heightLabel.text = @"175";
        } else {
            [_heightPickerView setCurrentIndex:55];
            self.heightLabel.text = @"165";
        }
        
        [UIView animateWithDuration:0.6f animations:^{
            _agePickerView.alpha = 1;
            self.inputNameBottomBar.alpha = 0;
            self.lastAndNextBottomBar.alpha = 1;
        }];
    } else if (_pageNumber == 2 && control == PageControlToPageLast) {      // page 3 to page 2
        [UIView animateWithDuration:0.6f animations:^{
            _agePickerView.alpha = 1;
            _heightPickerView.alpha = 0;
        }];
    } else if (_pageNumber == 3 && control == PageControlToPageNext) {      // page 2 to page 3
        [UIView animateWithDuration:0.6f animations:^{
            _agePickerView.alpha = 0;
            _heightPickerView.alpha = 1;
        }];
    } else if (_pageNumber == 3 && control == PageControlToPageLast) {      // page 4 to page 3
        [UIView animateWithDuration:0.6f animations:^{
            _heightPickerView.alpha = 1;
        }];
    }
    
    // 页面跳转
    if (control != PageControlToPageNone) {
        [self.scrollView setContentOffset:CGPointMake(SCREEN_WIDTH * (_pageNumber - 1), 0) animated:YES];
    }
}

- (BOOL)dataVerify {
    switch (_pageNumber) {
        case 1:
            NSLog(@"page 111");
            if (_selectedUserSex == SelectedUserSexNone) {
                [ViewUtilFactory presentAlertViewWithTitle:@"请选择性别" message:nil delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
                return NO;
            } else {
                if (_selectedUserSex == SelectedUserSexMales) {
                    self.inputOtherInfoViewPhotoImageView.image = [UIImage imageNamed:@"default_photo_males.png"];
                    self.bodyImageView.image = [UIImage imageNamed:@"malesbodyimage.png"];
                } else {
                    self.inputOtherInfoViewPhotoImageView.image = [UIImage imageNamed:@"default_photo_females.png"];
                    self.bodyImageView.image = [UIImage imageNamed:@"femalesbodyimage.png"];
                }
                _userInfoEntity.UI_sex = [NSString stringWithFormat:@"%d", (int)_selectedUserSex];
            }
            break;
        case 2:
                        NSLog(@"page 222");
            if (_type == FlowTypeGuest) {
                // 年龄 10 - 80
                _userInfoEntity.UI_age = [NSString stringWithFormat:@"%d", (int)_agePickerView.selectedIndex + 10];
            } else {
                _userInfoEntity.UI_birthday = self.birthLabel.text;
            }
            break;
        case 3:
            // 身高 100 - 220 cm
                        NSLog(@"page 333 %d",_heightPickerView.selectedIndex);
            _userInfoEntity.UI_height = [NSString stringWithFormat:@"%d", 220 - (int)_heightPickerView.selectedIndex];
            break;
        default:
            break;
    }
    return YES;
}

#pragma mark - AQPickerView Delegate
- (void)cancelButtonTapped:(AQPickerView *)pickerView {
    
}

- (void)savedWithYear:(NSInteger)year month:(NSInteger)month day:(NSInteger)day {
    self.birthLabel.text = [NSString stringWithFormat:@"%04d-%02d-%02d", year, month, day];
}

- (void)pickerViewWillDismiss:(AQPickerView *)pickerView {

}

- (void)pickerViewDidDismiss:(AQPickerView *)pickerView {
    
}

#pragma mark - PickerView Delegate
- (NSInteger)numberOfItemsInPickerView:(id)pickerView {
    
    if (_hasAgePicker) {
        _hasAgePicker = NO;
        return 71;
    } else {
        return 121;
    }
    
}

- (NSString *)pickerView:(id)pickerView titleForItemsIndex:(NSInteger)index {
    if (pickerView == _agePickerView) {
        return [NSString stringWithFormat:@"%d", (int)index + 10];
    } else {
        return [NSString stringWithFormat:@"%d", 220 - (int)index];
    }
}

- (void)pickerView:(id)pickerView indexChaged:(NSInteger)index {
    if (pickerView == _agePickerView) {
        self.ageLabel.text = [NSString stringWithFormat:@"%d", (int)index + 10];
    } else {
        self.heightLabel.text = [NSString stringWithFormat:@"%d", 220 - (int)index];
    }
}

@end
