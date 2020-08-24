//
//  ISDrivingLicensePreviewController.h
//  ISIDReaderPreviewSDK
//
//  Created by Johnson Zhang on 16/3/30.
//  Copyright © 2016年 IntSig. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ISOpenSDKFoundation/ISOpenSDKFoundation.h>
#import <CoreMedia/CoreMedia.h>

extern NSString *const kDrivingCardItemIDNumber;//驾驶证号
extern NSString *const kDrivingCardItemName;//姓名
extern NSString *const kDrivingCardItemSex;//性别
extern NSString *const kDrivingCardItemNationality;//国籍
extern NSString *const kDrivingCardItemAddress;//地址
extern NSString *const kDrivingCardItemBirthDay;//出生日期
extern NSString *const kDrivingCardItemIssueDate;//初次申领日期
extern NSString *const kDrivingCardItemDriveType;//准驾车型
extern NSString *const kDrivingCardItemValidFrom;//有效起始日期
extern NSString *const kDrivingCardItemValidFor;//截止日期
extern NSString *const kDrivingCardItemValidity;//有效期限

typedef void(^ConstructResourcesFinishHandler)(ISOpenSDKStatus status);
typedef void(^DetectCardFinishHandler)(int result, NSArray *borderPointsArray);
typedef void(^RecognizeCardFinishHandler)(NSDictionary *cardInfo);

@interface ISDrivingLicensePreviewController : NSObject<ISPreviewSDKProtocol>

+ (ISDrivingLicensePreviewController *)sharedISOpenSDKController;

- (ISOpenSDKCameraViewController *)cameraViewControllerWithAppkey:(NSString *)appKey subAppkey:(NSString *)subAppKey;

- (void)constructResourcesWithAppKey:(NSString *)appKey
                           subAppkey:(NSString *)subAppKey
                       finishHandler:(ConstructResourcesFinishHandler)handler;

- (ISOpenSDKStatus)detectCardWithOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                           cardRect:(CGRect)rect//rect should be a golden rect for driving license that are shaped with its proportions
                            detectCardFinishHandler:(DetectCardFinishHandler)detectCardFinishHandler
                         recognizeCardFinishHandler:(RecognizeCardFinishHandler)recognizeFinishHandler;

- (void)destructResources;

+ (NSString *)getSDKVersion;


@end
