//
//  VeridiumBiometrics4FConfig.h
//  Veridium4FBiometrics
//
//  Created by Josiah Kane on 09/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumBiometrics4FConfig_h
#define VeridiumBiometrics4FConfig_h

#import "VeridiumBiometrics4FCommon.h"

typedef float WSQCompressRatio;
extern WSQCompressRatio const COMPRESS_15to1;
extern WSQCompressRatio const COMPRESS_10to1;
extern WSQCompressRatio const COMPRESS_5to1;

typedef int NistType;
extern NistType const Nist_type_T14_9;
extern NistType const Nist_type_T4_9;


@interface VeridiumBiometrics4FConfig : NSObject


/*!
 Whether to use the left or right hand (defaults to Veridium4FExportHandDefaultLeft)
 */
@property Veridium4FAnalyzeHand chosenHand;

/*!
 Whether to use two shot liveness. Defaults to false.
 */
@property BOOL twoShotLiveness;
@property BOOL passiveLiveness;
@property BOOL laxLiveness;



@property VeridiumTemplateFormat exportFormat;

@property BOOL record8F;

@property BOOL keepResource;


@property BOOL pack_debug_data;

@property BOOL pack_wsq;

@property WSQCompressRatio wsq_compression_ratio;

@property BOOL pack_raw;

@property BOOL pack_png;

@property BOOL calculate_nfiq;
@property BOOL background_remove;
@property BOOL extra_scaled_image;
@property BOOL pack_audit_image;
@property BOOL reliability_mask;
@property int nist_type;

@property int fixed_print_width;
@property int fixed_print_height;


@property int padding_width;
@property int padding_height;

@property BOOL targetIndexFinger;
@property BOOL targetLittleFinger;
@property VeridiumThumbMode captureThumb;

@property BOOL individualThumb;
@property BOOL individualIndex;
@property BOOL individualMiddle;
@property BOOL individualRing;
@property BOOL individualLittle;
@property BOOL individualCapture;


-(BOOL) supports4F;
-(BOOL) supports8F;
-(BOOL) supports2Thumb;
-(BOOL) supportsAllFinger;
-(NSString* _Nonnull) formatName;
-(NSString* _Nonnull) formatExtension;



@end

#endif /* VeridiumBiometrics4FConfig_h */
