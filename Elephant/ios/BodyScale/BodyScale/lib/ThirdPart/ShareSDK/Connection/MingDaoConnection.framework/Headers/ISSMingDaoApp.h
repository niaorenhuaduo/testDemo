//
//  ISSMingDaoApp.h
//  MingDaoConnection
//
//  Created by lisa on 14-3-6.
//  Copyright (c) 2014年 lisa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShareSDKCoreService/ShareSDKCoreService.h>
#import <ShareSDK/ShareSDKPlugin.h>
#import "SSMingDaoUser.h"
#import "SSMingDaoErrorInfo.h"

///#begin zh-cn
/**
 *	@brief	请求方式
 */
///#end
///#begin en
/**
 *	@brief	Request method
 */
///#end
typedef enum
{
	SSMingDaoRequestMethodGet = 0, /**< GET方式 */
	SSMingDaoRequestMethodPost = 1, /**< POST方式 */
	SSMingDaoRequestMethodMultipartPost = 2 /**< Multipart POST方式，用于上传文件的api接口 */
}
SSMingDaoRequestMethod;

///#begin zh-cn
/**
 *	@brief	明道应用协议
 */
///#end
///#begin en
/**
 *	@brief	MingDao App Protocol.
 */
///#end
@protocol ISSMingDaoApp <ISSPlatformApp>

///#begin zh-cn
/**
 *	@brief	获取应用Key
 *
 *	@return	应用Key
 */
///#end
///#begin en
/**
 *	@brief	Get app key.
 *
 *	@return	App key.
 */
///#end
- (NSString *)appKey;

///#begin zh-cn
/**
 *	@brief	获取应用密钥
 *
 *	@return	应用密钥
 */
///#end
///#begin en
/**
 *	@brief	Get app secret.
 *
 *	@return	App secret.
 */
///#end
- (NSString *)appSecret;

///#begin zh-cn
/**
 *	@brief	获取应用回调地址
 *
 *	@return	应用回调地址
 */
///#end
///#begin en
/**
 *	@brief	Get redirect uri.
 *
 *	@return	Redirect uri.
 */
///#end
- (NSString *)redirectUri;

///#begin zh-cn
/**
 *	@brief	调用开放平台API
 *
 *	@param 	path 	路径
 *  @param  method  请求方式
 *	@param 	params 	请求参数
 *  @param  user    授权用户,如果传入nil则表示默认的授权用户
 *  @param  result  返回回调
 *  @param  fault   失败回调
 */
///#end
///#begin en
/**
 *	@brief	Call API
 *
 *	@param 	path 	API path.
 *  @param  method  Request method.
 *	@param 	params 	Request parameters.
 *  @param  user    Authorized users, it means that if the incoming nil default authorized users
 *  @param  result  Result handler.
 *  @param  fault   Fault handler.
 */
///#end
- (void)api:(NSString *)path
     method:(SSMingDaoRequestMethod)method
     params:(id<ISSCParameters>)params
       user:(id<ISSPlatformUser>)user
     result:(void(^)(id responder))result
      fault:(void(^)(CMErrorInfo *error))fault;

///#begin zh-cn
/**
 *	@brief	发布一条动态更新
 *
 *	@param 	pmsg 	动态内容
 *  @param  result  回调方法
 */
///#end
///#begin en
/**
 *	@brief	Publish a new status.
 *
 *	@param 	pmsg 	Content string.
 *  @param  result  Result handler.
 */
///#end
- (void)updateWithPmsg:(NSString *)pmsg
                result:(SSShareResultEvent)result;


///#begin zh-cn
/**
 *	@brief	上传图片，文档并发布一条动态更新
 *
 *	@param 	pmsg 	动态内容
 *	@param 	pimg 	图片数据
 *  @param  result  回调方法
 */
///#end
///#begin en
/**
 *	@brief	Upload image and publish a new status.
 *
 *	@param 	pmsg 	Content string.
 *	@param 	pimg 	Image attachment.
 *  @param  result  Result handler.
 */
///#end
- (void)updateWithPmsg:(NSString *)pmsg
                  pimg:(id<ISSCAttachment>)pimg
                result:(SSShareResultEvent)result;


///#begin zh-cn
/**
 *	@brief	调用明道客户端进行网页分享
 *
 *	@param 	mdPageUrl 分享网页内容地址链接
 *	@param 	mdTitle	网页内容标题或者描述
 *	@param 	mdPic 	网页图片链接
 *  @param  result  回调方法
 */
///#end
///#begin en
/**
 *	@brief	Call Sina Weibo client for web page sharing
 *
 *	@param 	mdPageUrl 	Web page link.
 *	@param 	mdTitle 	title.
 *	@param 	mdPic       image.
 *  @param  result  Result handler
 */
///#end
- (void)shareWithmdPageUrl:(NSString *)mdPageUrl
                   mdTitle:(NSString *)mdTitle
                     mdPic:(NSString *)mdPic
                    result:(SSShareResultEvent)result;



@end
