//
//  UserFeedbackViewViewController.m
//  BodyScaleProduction
//
//  Created by 刘平伟 on 14-3-27.
//  Copyright (c) 2014年 Go Salo. All rights reserved.
//

#import "UserFeedbackViewViewController.h"
#import "UIViewController+MMDrawerController.h"

@interface UserFeedbackViewViewController ()<UITextFieldDelegate>

@property (nonatomic, assign) CGRect inputOrigiFrame;

@property (nonatomic, retain) NSMutableArray *suggests;
@property (weak, nonatomic) IBOutlet UIView *inputTextFieldBack;
@property (weak, nonatomic) IBOutlet SYUserFeedbackView *suggestListView;
@property (weak, nonatomic) IBOutlet UITextField *inputTextfield;
- (IBAction)submitButtonClicked:(id)sender;

@end

@implementation UserFeedbackViewViewController

#pragma mark - lifeCycle methods

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = @"意见建议";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self configSubViews];
    [self getUserSuggestHistory];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardWillHidden:) name:UIKeyboardWillHideNotification object:nil];
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    self.inputOrigiFrame = self.inputTextFieldBack.frame;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - keyBoard event

-(void)keyBoardWillShow:(NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSInteger curve = [userInfo[UIKeyboardAnimationCurveUserInfoKey] integerValue];
    CGFloat duration = [userInfo[UIKeyboardAnimationDurationUserInfoKey] floatValue];
    CGRect keyBoardEndFrame = [userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat statusH = 64;
    
    [self.view bringSubviewToFront:self.inputTextFieldBack];
    [UIView animateWithDuration:duration
                          delay:0
                        options:curve << 16
                     animations:^{
                         self.inputTextFieldBack.frame = CGRectMake(0,
                                                                    CGRectGetMinY(keyBoardEndFrame)-CGRectGetHeight(self.inputTextFieldBack.frame) - statusH, CGRectGetWidth(self.inputTextFieldBack.frame),
                                                                    CGRectGetHeight(self.inputTextFieldBack.frame));
                     }
                     completion:^(BOOL finished) {
                         
                     }];
}

-(void)keyBoardWillHidden:(NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSInteger curve = [userInfo[UIKeyboardAnimationCurveUserInfoKey] integerValue];
    CGFloat duration = [userInfo[UIKeyboardAnimationDurationUserInfoKey] floatValue];
    [UIView animateWithDuration:duration
                          delay:0
                        options:curve << 16
                     animations:^{
                                 self.inputTextFieldBack.frame = self.inputOrigiFrame;
                     }
                     completion:NULL];

    
}

#pragma mark - UITextFieldDelegate methods

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

#pragma mark - custom methods

-(void)configSubViews
{
    self.suggests = [NSMutableArray array];
    self.mm_drawerController.openDrawerGestureModeMask = MMOpenDrawerGestureModeNone;
    
    NSArray *suggest = [[InterfaceModel sharedInstance] getSuggestFromDB];
    if (suggest) {
        [self.suggests addObjectsFromArray:suggest];
    }
    self.suggestListView.SuggestArr = self.suggests;
    
    self.inputTextfield.placeholder = @"请输入您的反馈内容";
}

-(void)getUserSuggestHistory
{
    [[InterfaceModel sharedInstance] querySuggestWithCallBack:^(int code, id param, NSString *errorMsg) {
        if ([[param class] isSubclassOfClass:[NSArray class]]) {
            [self.suggests removeAllObjects];
            [self.suggests addObjectsFromArray:param];
            self.suggestListView.SuggestArr = param;
        }
        
    }];
}

-(void)submitSuggest
{
    [_inputTextfield resignFirstResponder];
    
    if (_inputTextfield.text.length == 0 || [_inputTextfield.text hasPrefix:@" "]) {
        [self showHUDInView:self.view
               justWithText:@"请输入您的建议/意见"
          disMissAfterDelay:.8];
        
        return;
    }
    
    [self showHUDInView:self.view justWithText:@"正在提交"];
    NSString *content = self.inputTextfield.text;
    self.inputTextfield.text = nil;
    [[InterfaceModel sharedInstance] submitSuggest:content WithCallBack:^(int code, id param, NSString *errorMsg) {

        if (errorMsg == nil) {
            [self disMissHUDWithText:@"提交成功" afterDelay:.5];
            [self getUserSuggestHistory];

        }else{
            [self disMissHUDWithText:@"提交失败" afterDelay:.5];
        }

    }];
    _inputTextfield.text = nil;
}

#pragma mark - manage memory methods

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (IBAction)submitButtonClicked:(id)sender {
    
    [self submitSuggest];
}
@end
