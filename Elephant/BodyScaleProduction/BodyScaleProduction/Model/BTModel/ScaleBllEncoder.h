//
//  ScaleBllEncoder.h
//  BodyScale
//
//  Created by Go Salo on 14-2-19.
//  Copyright (c) 2014年 于菲. All rights reserved.
//

#import <Foundation/Foundation.h>

//APP->秤的指令
#define SCALE_COMMAND_EXISTUSER            0xA0
#define SCALE_COMMAND_NEWUSER              0xA1
#define SCALE_COMMAND_DELETEUSER           0xA2
#define SCALE_COMMAND_UPDATEUSER           0xA3
#define SCALE_COMMAND_GETSIMUSER           0xA4
#define SCALE_COMMAND_GETALLUSER           0xA5
#define SCALE_COMMAND_USERSCALE            0xC0
#define SCALE_COMMAND_READSCALEDATA        0xC1
#define SCALE_COMMAND_DELETESCALEDATA      0xC2
#define SCALE_COMMAND_SCALESETTING         0xE0
#define SCALE_COMMAND_CUSTOMTYPE           0xE1
#define SCALE_COMMAND_QUITCUSTOMTYPE       0xE2

#define SCALE_COMMAND_GETALLUSER_BACK      0xFA
#define SCALE_COMMAND_USERSCALE_BACK       0xFA
#define SCALE_COMMAND_READSCALEDATA_BACK   0xFA
#define SCALE_COMMAND_RTIMEWEIGHT_BACK     0xFA

//秤->APP的指令
#define SCALE_COMMAND_BACK_UPLOADUSERINFO  0xB5
#define SCALE_COMMAND_BACK_UPLOADUSERDATA  0xD0
#define SCALE_COMMAND_BACK_READUSERDATA    0xD1
#define SCALE_COMMAND_ASKTIME              0xF8
#define SCALE_COMMAND_BACK                 0xFB
#define SCALE_COMMAND_REALTIMEWEIGHT       0xD2
#define SCALE_COMMAND_READMACADDRESS       0xE3
#define SCALE_COMMAND_RESETSCALE           0xE4
#define SCALE_COMMAND_RESETWEIGHT          0xE5

typedef NS_ENUM(int, methodFlag){
    SAExistUser,         //检查用户是否存在
    SANewUser,           //建新用户
    SADelUser,           //删除用户
    SAUpdateUser,        //更新用户
    SAGetSimUser,        //获取单个用户信息
    SAGetAllUser,        //获取所有用户信息
    SAGetAllUserback,    //获取所有用户信息反馈
    SAUserScale,         //用户称重
    SAUserScaleback,     //用户称重反馈
    SAReadScaledata,     //读取用户称重数据
    SAReadScaledataback, //读取用户称重数据
    SADeleteScaledata,   //删除用户测量数据
    SARtimeWeightlocked, //实时重量传输
    SAScaleSetting,      //设置秤体信息
    SACustomtype,        //客人模式进入
    SAQuitcustomtype,    //客人模式退出
};

typedef struct _SCALE_COMMAND_UPDATETIME_FORMAT
{
    unsigned char h0;
    unsigned char h1;
    char utime[4];
} _SCALE_COMMAND_UPDATETIME_FORMAT;

typedef struct _SCALE_COMMAND_EXISTUSER_FORMAT
{
    unsigned char command;
    char userno[1];//1-8
} _SCALE_COMMAND_EXISTUSER_FORMAT;//__attribute__((packed))

typedef struct _SCALE_COMMAND_NEWUSER_FORMAT
{
    unsigned char command;
    char userno[1];
    char height[1];
    char age[1];
    char gender[1];
    
} _SCALE_COMMAND_NEWUSER_FORMAT;

typedef struct _SCALE_COMMAND_DELETEUSER_FORMAT
{
    unsigned char command;
    char userno[1];
    
} _SCALE_COMMAND_DELETEUSER_FORMAT;

typedef struct _SCALE_COMMAND_UPDATEUSER_FORMAT
{
    unsigned char command;
    char userno[1];
    char height[1];
    char age[1];
    char gender[1];
    
} _SCALE_COMMAND_UPDATEUSER_FORMAT;

typedef struct _SCALE_COMMAND_GETSIMUSER_FORMAT
{
    unsigned char command;
    char userno[1];
    
} _SCALE_COMMAND_GETSIMUSER_FORMAT;

typedef struct _SCALE_COMMAND_GETALLUSER_FORMAT
{
    unsigned char command;
    
} _SCALE_COMMAND_GETALLUSER_FORMAT;

typedef struct _SCALE_COMMAND_GETALLUSER_BACK_FORMAT
{
    unsigned char command;
    unsigned char backcmd;
    char pkgnum[1];
    char pkgid[1];
    
} _SCALE_COMMAND_GETALLUSER_BACK_FORMAT;

typedef struct _SCALE_COMMAND_USERSCALE_FORMAT
{
    unsigned char command;
    char userno[1];
    char height[1];
    char age[1];
    char gender[1];
    
} SCALE_COMMAND_USERSCALE_FORMAT;

typedef struct _SCALE_COMMAND_USERSCALE_BACK_FORMAT
{
    unsigned char command;
    unsigned char backcmd;
    char pkgnum[1];
    char pkgid[1];
    
} _SCALE_COMMAND_USERSCALE_BACK_FORMAT;

typedef struct _SCALE_COMMAND_READSCALEDATA_FORMAT
{
    unsigned char command;
    char userno[1];
    
} _SCALE_COMMAND_READSCALEDATA_FORMAT;

typedef struct _SCALE_COMMAND_READSCALEDATA_BACK_FORMAT
{
    unsigned char command;
    unsigned char backcmd;
    char pkgnum[1];
    char pkgid[1];
    
} _SCALE_COMMAND_READSCALEDATA_BACK_FORMAT;

typedef struct _SCALE_COMMAND_DELETESCALEDATA_FORMAT
{
    unsigned char command;
    char userno[1];
    
} _SCALE_COMMAND_DELETESCALEDATA_FORMAT;

typedef struct _SCALE_COMMAND_RTIMEWEIGHT_BACK_FORMAT
{
    unsigned char command;
    unsigned char backcmd;
    char weightlock[1];
} _SCALE_COMMAND_RTIMEWEIGHT_BACK_FORMAT;

typedef struct _SCALE_COMMAND_SCALESETTING_FORMAT
{
    unsigned char command;
    char weightrange[1];
    char elecrange[1];
} _SCALE_COMMAND_SCALESETTING_FORMAT;

typedef struct _SCALE_COMMAND_CUSTOMTYPE_FORMAT
{
    unsigned char command;
    
} _SCALE_COMMAND_CUSTOMTYPE_FORMAT;

typedef struct _SCALE_COMMAND_QUITCUSTOMTYPE_FORMAT
{
    unsigned char command;
    
} _SCALE_COMMAND_QUITCUSTOMTYPE_FORMAT;


//秤到APP的结构体-上传用户信息
typedef struct _SCALE_COMMAND_BACK_UPLOADUSERINFO_FORMAT
{
    int command;
    int pkgnum;
    int pkgid;
    int userid;
    int height;
    int age;
    int gender;
} _SCALE_COMMAND_BACK_UPLOADUSERINFO_FORMAT;

typedef struct _SCALE_COMMAND_BACK_UPLOADUSERDATA_FORMAT
{
    int command;
    int pkgnum;
    int pkgid;
    int userid;
    int tmie1;
    int tmie2;
    int tmie3;
    int tmie4;
    int weighth;
    int weightl;
    int bfh;
    int bfl;
    int waterh;
    int waterl;
    int muscleh;
    int musclel;
    int boneh;
    int bonel;
    int bmrh;
    int bmrl;
    int sfath;
    int sfatl;
    int infat;
    int bodyage;
} _SCALE_COMMAND_BACK_UPLOADUSERDATA_FORMAT;


@interface ScaleBllEncoder : NSObject

@property (nonatomic,strong) NSString *msDotype;
@property (nonatomic,strong) NSString *msRecMsg;

- (NSData *)dataEncordeUpdateTime;
- (NSData *)dataEncordeExistUser:(int)pno;
- (NSData *)dataEncordeNewUser:(int)pno height:(int)height age:(int)age gender:(int)gender;
- (NSData *)dataEncordeDeleteUser:(int)pno;
- (NSData *)dataEncordeUpdateUser:(int)pno height:(int)height age:(int)age gender:(int)gender;
- (NSData *)dataEncordeGetSimUser:(int)pno;
- (NSData *)dataEncordeGetAllUser;
- (NSData *)dataEncordeGetAllUserConfirm:(int)pkgnum pkgid:(int)pkgid;
- (NSData *)dataEncordeUserScale:(int)pno height:(int)height age:(int)age gender:(int)gender;
- (NSData *)dataEncordeGetUserScaleConfirm:(int)pkgnum pkgid:(int)pkgid;
- (NSData *)dataEncordeReadScaleData:(int)pno;
- (NSData *)dataEncordeGetReadScaleDataConfirm:(int)pkgnum pkgid:(int)pkgid;
- (NSData *)dataEncordeDeleteScaleData:(int)pno;
- (NSData *)dataEncordeRealtimeWeight:(int)locked;
- (NSData *)dataEncordeScaleSetting:(int)weightrange elecrange:(int)elecrange;
- (NSData *)dataEncordeCustomtype;
- (NSData *)dataEncordeQuitcustomtype;

@end
