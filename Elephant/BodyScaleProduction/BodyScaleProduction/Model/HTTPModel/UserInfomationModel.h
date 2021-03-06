//
//  UserInfomationModel.h
//  BodyScaleProduction
//
//  Created by Go Salo on 14-3-18.
//  Copyright (c) 2014年 Go Salo. All rights reserved.
//

#import "HTTPBaseModel.h"

@interface UserInfomationModel : HTTPBaseModel
//体脂仪用户注册
- (void)requestRegisterWithloginName:(NSString *)loginName
                            password:(NSString *)password
                            nickName:(NSString *)nickname
                                 sex:(NSString *)sex
                              weight:(NSString *)weight
                              height:(NSString *)height
                                 age:(NSString *)age
                           validCode:(NSString *)validCode
                                mode:(NSString *)mode
                                plan:(NSString *)plan
                              target:(NSString *)target
                             privacy:(NSString *)privacy
                                data:(id)userData;
//发送验证码
- (void)requestSendValidCodeWithloginName:(NSString *)loginName validType:(NSString *)validType;

//查询登录数据
- (void)requestQueryLoginDataWithsessionId:(NSString *)sessionId userId:(NSString *)userId userInfo:(id)info;

//登录
- (void)requestLoginWithloginName:(NSString *)loginName
                         loginPwd:(NSString *)loginPwd
                         userInfo:(NSDictionary *)userInfo;

//登出
- (void)requestLogoutWithsessionId:(NSString *)sessionId;

//更新用户基本信息
- (void)requestUpdateUserInformationWithsessionId:(NSString *)sessionId
                                          loginId:(NSString *)loginId
                                         passWord:(NSString *)passWord
                                        validCode:(NSString *)validCode
                                              age:(NSString *)age
                                         nickname:(NSString *)nickname
                                          chnName:(NSString *)chnName
                                              sex:(NSString *)sex
                                   homeProvinceId:(NSString *)homeProvinceId
                                 homeProvinceName:(NSString *)homeProvinceName
                                       homeCityId:(NSString *)homeCityId
                                     homeCityname:(NSString *)homeCityname
                                       homeAreaId:(NSString *)homeAreaId
                                     homeAreaName:(NSString *)homeAreaName
                                   locaProvinceId:(NSString *)locaProvinceId
                                 locaProvinceName:(NSString *)locaProvinceName
                                       locaCityId:(NSString *)locaCityId
                                     locaCityName:(NSString *)locaCityName
                                       locaAreaId:(NSString *)locaAreaId
                                     locaAreaName:(NSString *)locaAreaName
                                        photoPath:(NSString *)photoPath
                                         birthday:(NSString *)birthday
                                           height:(NSString *)height
                                           weight:(NSString *)weight
                                       profession:(NSString *)profession
                                     privacyLevel:(NSString *)privacyLevel
                                         authBind:(NSString *)authBind
                                           status:(NSString *)status
                                           remark:(NSString *)remark
                                        regStatus:(NSString *)regStatus
                                     bodyscaleLoc:(NSString *)bodyscaleLoc;

//上传文件
- (void)requestUploadFileWithfileName:(NSString *)fileName
                                 data:(NSData *)data;


//查询时间提示信息
- (void)requestQueryNoticeWithsessionId:(NSString *)sessionId
                               userInfo:(id)userInfo;

//重置密码
-(void)requestResetPWDWithloginName:(NSString *)loginName
                          validCode:(NSString *)validCode
                             newPwd:(NSString *)newPwd;
/**
 *  添加关注
 *
 *  @param sessionId      sessionId + focusUserId +约定串
 *  @param focusUserId    需要关注的用户id
 *  @param focusLoginName 需要关注的用户名 focusUserId && focusLoginName不能同时为空
 *  @param mRight         对方权限 0:无权限;1:查看;2:编辑;
 *  @param specFocusFlag  1特别关注标识，其它值不理会
 *  @param appType        1:血压 2：体脂仪
 */
-(void)requestAddFocusWithSessionId:(NSString *)sessionId
                        focusUserId:(NSNumber *)focusUserId
                     focusLoginName:(NSString *)focusLoginName
                             mRight:(NSNumber *)mRight
                      specFocusFlag:(NSNumber *)specFocusFlag
                            appType:(NSNumber *)appType;

/**
 *  修改好友权限
 *
 *  @param sessionId sessionId + mId +约定串          必填
 *  @param mId       列表下发自增字段Mid                必填
 *  @param mRight    对方权限 0:无权限;1:查看;2:编辑     必填
 *  @param appType   1:血压计 2：体脂仪                 必填
 */
-(void)requestMRightFocusWithSessionId:(NSString *)sessionId
                                   mId:(NSNumber *)mId
                                mRight:(NSNumber *)mRight
                               appType:(NSNumber *)appType;

/**
 *  获取 新消息 （谁对你发起了加好友申请）
 *
 *  @param sessionId sessionId + reqTime + 约定串          必填
 *  @param foucsMe   传1表示 需要查询关注我的新信息            必填
 */
-(void)requestMyMsgCountsWithSessionId:(NSString *)sessionId
                               foucsMe:(NSNumber *)foucsMe;


/**
 *  删除关注人
 *
 *  @param sessionId sessionId+ mId +约定串                            必填
 *  @param mId       列表下发自增字段Mid  FriendInfoEntity.FI_mid        必填
 */
-(void)requestDeleteFocusWithSessionId:(NSString *)sessionId
                                   mId:(NSNumber *)mId;

/**
 *  同意或拒绝关注
 *
 *  @param sessionId sessionId+ mId +约定串
 *  @param mId       查询关注人下发的mid
 *  @param appType   1:血压 2：体脂仪
 *  @param stutas    状态 0:正常(同意); 1:已解除（拒绝）; 2:待确认;
 */
-(void)requestAgreeFocusWithSessionId:(NSString *)sessionId
                                  mId:(NSNumber *)mId
                              appType:(NSNumber *)appType
                               stutas:(NSNumber *)stutas;

/**
 *  关注我的用户列表
 *
 *  @param sessionId sessionId+约定串
 *  @param appType   1:血压 2：体脂仪
 */
-(void)requestFocusMeListWithSessionId:(NSString *)sessionId
                               appType:(NSNumber *)appType;

/**
 *  将关注我的信息置成已读
 *
 *  @param sessionId sessionId+ reqTime +mId+约定串
 *  @param mId       mId 若未 nil 则标记当前用户所有消息为已读
 */
-(void)requestFocusMeSetReadWithSessionId:(NSString *)sessionId
                                      mId:(NSString *)mId;


/**
 *  删除关注人新信息
 *
 *  @param sessionId sessionId+ mId +约定串
 *  @param mId       列表下发自增字段Mid
 */
-(void)requestDelFocusMsgWithSessionId:(NSString *)sessionId
                                   mid:(NSNumber *)mid;

/**
 *  检测用户名是否已经被使用
 *
 *  @param loginName 用户名
 */
-(void)requestCheckLonginWithLoginName:(NSString *)loginName;

/**
 *  京东用户，登陆我方服务器
 *
 *  @param oid JDUserInfo.uid
 */
-(void)requestJDLoginWithOpenId:(NSString *)oid
                       nickName:(NSString *)nickName;



@end
