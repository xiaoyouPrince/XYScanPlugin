//
//  ISIDCardReaderController.h
//  ISIDReaderPreviewSDK
//
//  Created by Simon liu on 17/2/7.
//  Copyright (c) 2015年 xzliu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ISOpenSDKFoundation/ISOpenSDKFoundation.h>
#import <CoreMedia/CoreMedia.h>

extern NSString * const kOpenSDKCardResultTypeOriginImage;//origin image(原图)
extern NSString * const kOpenSDKCardResultTypeImage;//cropped image(切边后的图)
extern NSString * const kOpenSDKCardResultTypeHeadImage;//headImage(头像)
extern NSString * const kOpenSDKCardResultTypeCardName;//card name(卡/证名,字符串值)
extern NSString * const kOpenSDKCardResultTypeCardType;//card type(卡/证类型,整型值)
extern NSString * const kOpenSDKCardResultTypeCardItemInfo;//card item info dictionary(卡/证的详细信息)
extern NSString * const kOpenSDKCardResultTypeCardRotate;//origin image rotate(原图的旋转角度，暂时只可能返回0,90,180,270)

extern NSString *const kCardItemName;//姓名
extern NSString *const kCardItemGender;//性别
extern NSString *const kCardItemNation;//民族
extern NSString *const kCardItemBirthday;//出生日期
extern NSString *const kCardItemAddress;//住址
extern NSString *const kCardItemIDNumber;//号码
extern NSString *const kCardItemIssueAuthority;//签发机关
extern NSString *const kCardItemValidity;//有效期限

extern NSString *const kIDCardNumberPointsInOriginImage;//身份证号码在原图中的四个坐标点，分别为：左上、右上、右下、左下
extern NSString *const kIDCardNumberRectInCroppedImage;//身份证号码在切边后的图中所在矩形框
extern NSString *const kIDCardNumberImage;//身份证号码截图

extern NSString *const kIDCardImageCompletenessType;//身份证完整的状态
extern NSString *const kIDCardColorImage;//身份证是否为彩色图
extern NSString *const kIDCardIQAHotspot;//身份证图像光斑范围值
extern NSString *const kIDCardIQABlur;//身份证图像清晰度值


typedef NS_ENUM(NSUInteger, ISOpenSDKIDCardType)//身份证类型枚举
{
    ISOpenSDKIDCardTypeSecondMain = 0,//第二代身份证正面
    ISOpenSDKIDCardTypeFirst = 1,//第一代身份证
    ISOpenSDKIDCardTypeSecondCover = 2,//第二代身份证背面
};

typedef NS_ENUM(NSInteger, ISIDCardImageCompletenessType)//身份证完整性状态枚举
{
    ISIDCardImageCompletenessTypeNone = 0,//未知状态
    ISIDCardImageCompletenessTypeComplete = 1,//质量完好
    ISIDCardImageCompletenessTypeImageCover = -1,//图像有遮挡
    ISIDCardImageCompletenessTypePhotoCover = -2,//正面人物头像质量不好
    ISIDCardImageCompletenessTypeNationalEmblemCover = -3,//反面国徽有遮挡
};

//typedef NS_ENUM(NSInteger,ISIDCardImageQualityJudgmentType)//身份证图像质量判断
//{
//    ISIDCardImageQualityJudgmentTypeNone = 0, //未知状态
//    ISIDCardImageQualityJudgmentTypeComplete = 1, //图像完整
//    ISIDCardImageQualityJudgmentTypeHotspot = 2, //图像有光斑
//    ISIDCardImageQualityJudgmentTypeBlur = 3 ,//图像模糊
//};

typedef void(^ConstructResourcesFinishHandler)(ISOpenSDKStatus status);//初始化结果的回调Block
typedef void(^DetectCardFinishHandler)(int result, NSArray *borderPointsArray);//边缘检测的回调Block
typedef void(^RecognizeCardFinishHandler)(NSDictionary *cardInfo);//识别成功的回调Block

@interface ISIDCardReaderController : NSObject<ISPreviewSDKProtocol>

/**
 *  单例对象
 *
 *  @return 身份证预览识别控制器单例
 */
+ (ISIDCardReaderController *)sharedISOpenSDKController;

/**
 *  初始化相机模块，如果使用Intsig自带的相机模块，请使用该方法进行初始化
 *
 *  @param appKey    申请获得的SDK，用于授权
 *  @param subAppKey 为扩展而留，当前请传空
 *
 *  @return 相机模块实体
 */
- (ISOpenSDKCameraViewController *)cameraViewControllerWithAppkey:(NSString *)appKey
                                                        subAppkey:(NSString *)subAppKey;

/**
 *  初始化相机模块，如果使用Intsig自带的相机模块，请使用该方法进行初始化
 *
 *  @param appKey           申请获得的SDK，用于授权
 *  @param subAppKey        为扩展而留，当前请传空
 *  @param needCompleteness 是否需要进行完整性识别的参数，NO为不进行完整性识别，YES为进行完整性识别，默认为YES
 *
 *  @return 相机模块实体
 */
- (ISOpenSDKCameraViewController *)cameraViewControllerWithAppkey:(NSString *)appKey
                                                        subAppkey:(NSString *)subAppKey
                                                 needCompleteness:(BOOL)needCompleteness;

/**
 *  初始化SDK，调用识别函数之前请先调用该接口
 *
 *  @param appKey    申请获得的SDK，用于授权
 *  @param subAppKey 为扩展而留，当前请传空
 *  @param handler   初始化结果的回调Block，授权状态定义在ISOpenSDKStatus.h
 */
- (void)constructResourcesWithAppKey:(NSString *)appKey
                           subAppkey:(NSString *)subAppKey
                       finishHandler:(ConstructResourcesFinishHandler)handler;

/**
 *  设置是否需要进行完整性识别
 *
 *  @param needCompleteness 是否需要进行完整性识别的参数，NO为不进行完整性识别，YES为进行完整性识别，默认为YES
 */
- (void)setNeedCompleteness:(BOOL)needCompleteness;

/**
 *  设置PS证件识别
 *
 *  @param crossCheck ：0开启PS识别，1不开启，默认1
 */
- (void)setPSCrossCheck:(int)kCrossCheck;

/**
 *  设置拍摄识别灵敏度
 *
 *  @param kMaxRang 参数建议：60、80、120、160、200、240
 */
- (void)setMaxRang:(int)kMaxRang;

/**
 *  设置是否需要将切边返回图片坐标边界点扩大
 *
 *  @param needExpandBorderPoints 是否需要进行切边图片坐标边界点扩大；YES进行扩大，NO不进行扩大；默认为NO不扩大
 *  @param expandPoints 设置扩大边缘范围值，默认为35;
 */
- (void)setNeedExpandDewarpImageBorderPoints:(BOOL)needExpandBorderPoints expandPoints:(int )expandPoints;

/**
 *  检测和识别卡/证的方法
 *
 *  @param sampleBuffer            需要识别的的图像数据，YUV格式
 *  @param rect                    需要识别的图像位置
 *  @param detectCardFinishHandler 边缘检测的回调Block，result为检测结果，大于0表示检测成功，borderPointsArray为检测出的8个角点数组
 *  @param recognizeFinishHandler  识别成功的回调Block，只有在识别成功时才会回调，cardInfo里面包含了识别结果信息
 *
 *  @return SDK的授权状态，如果SDK未授权或者之前授权不成功，将不会返回边缘检测结果和识别结果
 */
- (ISOpenSDKStatus)detectCardWithOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                           cardRect:(CGRect)rect
                            detectCardFinishHandler:(DetectCardFinishHandler)detectCardFinishHandler
                         recognizeCardFinishHandler:(RecognizeCardFinishHandler)recognizeFinishHandler;

/**
 *  拍照/选图识别
 *
 *  @param image 需要识别的图片
 *  @param handler 识别成功的回调Block，只有在识别成功时才会回调，cardInfo里面包含了识别结果信息
 */
- (ISOpenSDKStatus)processCardImage:(UIImage *)image
                  withFinishHandler:(RecognizeCardFinishHandler)handler;


- (void)setSaveRAW:(BOOL)isSaveRAW;

- (void)setIQA:(BOOL)isIQA;


- (ISOpenSDKStatus)autoDetectCardWithOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
                  cardRect:(CGRect)rect
               cornerPoint:(NSArray *)cornerPoint
   detectCardFinishHandler:(DetectCardFinishHandler)detectCardFinishHandler
recognizeCardFinishHandler:(RecognizeCardFinishHandler)recognizeFinishHandler;

/**
 *  释放资源
 */
- (void)destructResources;
/*
 Use this method to get the current SDK version information
 */
+ (NSString *)getSDKVersion;

@end
