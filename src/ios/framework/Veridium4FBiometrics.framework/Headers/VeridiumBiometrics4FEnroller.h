//
//  VeridiumBiometrics4FEnroller.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import "VeridiumBiometrics4FCommon.h"

/*!
 Data class for holding the 4F enrollment config params
 */
@interface Veridium4FEnrollConfig : NSObject<VeridiumBiometricEnrollConfig>

/*!
 Number of templates to enroll (defaults to 2)
 
 **_Note:_** Cannot be lower than 2
 */
@property NSInteger templatesToEnroll;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;
/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;


/*!
 Whether to reset timing after each successfully captured template 
 (defaults to TRUE)
 */
@property BOOL resetTimeoutAfterSuccessfulCapture;

/*!
 **EXPERIMENTAL** Whether to compute a custom handguide based on the user's fingers pattern after first enrolled template
 */
@property BOOL computeCustomHandGuide;

/*!
 **EXPERIMENTAL** Whether to compute a custom handguide based on the fov
 */
@property BOOL computeDefaultHandGuide;


/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

/*!
 The UI
 */
@property id<Veridium4FEnrollerUIDelegate> uiDelegate;


/*!
 Whether to use the left or right hand (defaults to Veridium4FExportHandDefaultLeft)
 */
@property Veridium4FAnalyzeHand enrollHand;

@property BOOL twoShotLiveness;
@property BOOL passiveLiveness;
@property BOOL livenessIsHorizontal;
@property BOOL laxLiveness;

@property BOOL keepResource;

@end

/*!
 The 4F biometric enroller.
 */
@interface VeridiumBiometrics4FEnroller : VeridiumBiometrics4FCommon <VeridiumBioEnroller>

///*!
// Ask the biometric engine to perform biometric enrollment
// 
// @param setting   cpature setting
// @param onSuccess the success callback voidBlock
// @param onFail    the fail callback stringBlock; receives the failure reason
// @param onCancel  the cancell callback voidBlock
// @param onError   the error callback stringBlock; receives the error message
// */
//-(void) enrollWithConfig: (Veridium4FEnrollConfig*) setting
//               onSuccess:(biometricVectorBlock _Nonnull) onSuccess
//                  onFail:(stringBlock _Nonnull) onFail
//                onCancel:(voidBlock _Nonnull) onCancel
//                 onError:(stringBlock _Nonnull) onError;


/*!
 Configure the enrollment
 
 @param config the Enroll4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype)configure:(Veridium4FEnrollConfig *)config;

/*!
 Update enrollment config
 
 @param config the Enroll4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype)captureConfigUpdate:(Veridium4FEnrollConfig *)config;


/*!
 The configured Enroll4FBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property (readonly) Veridium4FEnrollConfig* config;

@end



