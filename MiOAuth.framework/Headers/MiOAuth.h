//
//  MiOAuth.h
//  MiOAuth
//
//  Created by ssc on 2017/10/16.
//  Copyright © 2017年 xiaomi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import "MOErrorCode.h"

//! Project version number for MiOAuth.
FOUNDATION_EXPORT double MiOAuthVersionNumber;

//! Project version string for MiOAuth.
FOUNDATION_EXPORT const unsigned char MiOAuthVersionString[];


typedef NS_ENUM(NSInteger, MOPlatform) {
    MOPlatformDev = 0,
    MOPlatformShuidi = 1
};

typedef NS_ENUM(NSInteger, MOLoginType) {
    MOLoginTypeTicket = 0,
    MOLoginTypePwd = 1
};

typedef void (^MOCompleteBlock)(id responseObject, NSError *error);

@interface MiOAuth : NSObject

@property (nonatomic) BOOL skipConfirm;             //默认值为true，授权有效期内的用户在已登录情况下，不显示授权页面，直接通过。如果需要用户每次手动授权，设置为false
@property (nonatomic) MOLoginType loginType;        //登录类型，指定登录页面采用短信登录还是密码登录，默认密码方式登录。
@property (nonatomic) BOOL externalAuthEnable;      //是否支持跳转外部app（如 米家）授权，默认为支持
@property (nonatomic) BOOL skipToast;               //是否展示授权成功，默认开启
@property (nonatomic) BOOL fullScreenPresent;       //授权页面是否全屏展示兼容 ios13
@property (nonatomic, strong) WKProcessPool *sharePool;  //处理池，用来共享Web content

+ (instancetype)sharedInstance;

- (void)setLogEnable:(BOOL)logEnable;
- (void)showAccountSDKLogView;

- (void)setTestEnv:(BOOL)test;
- (void)setupWithPlatform:(MOPlatform)platform
                    appId:(NSString *)appId
              redirectUrl:(NSString *)redirectUrl;

- (void)setupTintColor:(UIColor *)tintColor;
- (void)setupBarTintColor:(UIColor *)barTintColor;

- (void)applyAccessTokenWithPermissions:(NSArray *)permissions
                                  state:(NSString *)state
                          completeBlock:(MOCompleteBlock)block;
- (void)applyAccessTokenWithPermissions:(NSArray *)permissions
                                  state:(NSString *)state
                               deviceId:(NSString *)deviceId
                          completeBlock:(MOCompleteBlock)block;
- (void)applyAuthCodeWithPermissions:(NSArray *)permissions
                               state:(NSString *)state
                       completeBlock:(MOCompleteBlock)block;
- (void)applyAuthCodeWithPermissions:(NSArray *)permissions
                            deviceId:(NSString *)deviceId
                               state:(NSString *)state
                       completeBlock:(MOCompleteBlock)block;

- (void)doHttpGetWithUrl:(NSString *)url
                  params:(NSDictionary *)params
                  macKey:(NSString *)macKey
           completeBlock:(MOCompleteBlock)block;

- (void)clearCookie;
- (BOOL)handleOpenUrl:(NSURL *)url;

+ (NSString *)generateHMACHeaderWithMethod:(NSString *)method
                                       url:(NSString *)url
                                    params:(NSDictionary *)params
                                    macKey:(NSString *)macKey;

@end
