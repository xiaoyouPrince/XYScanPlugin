//
//  ISVehicleLicensePreviewController.h
//  ISIDReaderPreviewSDK
//
//  Created by Johnson Zhang on 16/3/31.
//  Copyright © 2016年 IntSig. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ISOpenSDKFoundation/ISOpenSDKFoundation.h>
#import <CoreMedia/CoreMedia.h>

extern NSString *const kVehicleCardItemPlateNumber;//号牌号码
extern NSString *const kVehicleCardItemVehicleType;//车辆类型
extern NSString *const kVehicleCardItemOwner;//所有人
extern NSString *const kVehicleCardItemAddress;//地址
extern NSString *const kVehicleCardItemUseProperty;//使用性质
extern NSString *const kVehicleCardItemBrandModel;//品牌型号
extern NSString *const kVehicleCardItemVIN;//车辆识别代号
extern NSString *const kVehicleCardItemEngineNumber;//发动机号码
extern NSString *const kVehicleCardItemRegisterDate;//注册日期
extern NSString *const kVehicleCardItemIssueDate;//发证日期
extern NSString *const kVehicleCardItemRatifiedSeatingCapacity;//核定载人数
extern NSString *const kVehicleCardItemTotalMass;//总质量
extern NSString *const kVehicleCardItemCurbWeight;//整备质量
extern NSString *const kVehicleCardItemOutlineDimension;//外廓尺寸
extern NSString *const kVehicleCardItemCheckRecord;//检验有效期
extern NSString *const kVehicleCardItemBARCode;//条码

typedef NS_ENUM(NSUInteger,ISVehicleLincenseType)
{
    ISVehicleLincenseTypeMain = 1,  //中国行驶证正本
    ISVehicleLincenseTypeVice = 2,  // 中国行驶证副本
};


typedef void(^ConstructResourcesFinishHandler)(ISOpenSDKStatus status);
typedef void(^DetectCardFinishHandler)(int result, NSArray *borderPointsArray);
typedef void(^RecognizeCardFinishHandler)(NSDictionary *cardInfo);

@interface ISVehicleLicensePreviewController : NSObject<ISPreviewSDKProtocol>

+ (ISVehicleLicensePreviewController *)sharedISOpenSDKController;

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
