//
//  VeridiumBiometrics4FAuthenticator.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import "VeridiumBiometrics4FCommon.h"

/*!
 Data class for holding the 4F authentication config params
 */
@interface Veridium4FAuthenticationConfig : NSObject

typedef enum : NSUInteger{
  Veridium4FAuthenticatingHandLeft = 0,
  Veridium4FAuthenticatingHandRight,
  Veridium4FAuthenticatingHandFromStore
} Veridium4FAuthenticatingHand;
/*!
 Whether to use the left or right hand (defaults to TRUE)
 */
@property Veridium4FAuthenticatingHand authenticationHand;

/*!
 The allowed number of retries in case the authentication fails (defaults to 0)
 */
@property NSInteger numberOfRetries;

/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;


/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

@property BOOL twoShotLiveness;
@property BOOL passiveLiveness;
@property BOOL livenessIsHorizontal;
@property BOOL laxLiveness;


/*!
 The UI
 */
@property (nullable) id<Veridium4FAuthenticatorUIDelegate> uiDelegate;



@end

/*!
 The 4F biometric authenticator.
 */
@interface VeridiumBiometrics4FAuthenticator : VeridiumBiometrics4FCommon <VeridiumBioAuthenticator>

/*!
 Configure the authentication
 
 @param config the Authenticate4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)configure:(Veridium4FAuthenticationConfig * _Nonnull)config;

/*!
 Update enrollment config
 
 @param config the Authenticate4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)captureConfigUpdate:(Veridium4FAuthenticationConfig * _Nonnull)config;


/*!
 The configured Authenticate4FBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property(readonly, nonnull) Veridium4FAuthenticationConfig* config;

@end

