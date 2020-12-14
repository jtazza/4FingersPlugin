//
//  VeridiumSDK+4F.h
//  Veridium4FBiometrics
//
//  Created by Catalin Stoica on 04/07/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
@import VeridiumCore;
#import "VeridiumBiometrics4FAuthenticator.h"
#import "VeridiumBiometrics4FEnroller.h"
#import "VeridiumBiometrics4FExporter.h"

/*!
 SDK 4F additions
 */
@interface VeridiumSDK (FourFAdditions)


@property (class, readonly) BOOL isDevice4FCapable;

/*!
 Setup touchlessID with a licence
 
 @param license a touchlessID license
 */
-(Veridium4FLicenseStatus *_Nullable)setupTouchlessID:(NSString *)license;

/*!
 Register a 4F authenticator with a custom UI
 
 @param ui the custom UI
 */
-(void)register4FAuthenticator:(id<Veridium4FAuthenticatorUIDelegate> _Nonnull)ui;
/*!
 Register a 4F enroller with a custom UI
 
 @param ui the custom UI
 */
-(void) register4FEnroller:(id<Veridium4FEnrollerUIDelegate> _Nonnull)ui;

/*!
  Register a 4F exporter with a custom UI
     
  @param ui the custom UI
*/
-(void) register4FExporter:(id<Veridium4FExporterUIDelegate> _Nonnull)ui;

    
    
/*!
 Helper method to configure the registered 4F authenticator
 
 @param config the config
 */
-(void)configure4FAuthenticator:(Veridium4FAuthenticationConfig* _Nonnull)config;

/*!
 Helper method for grabbing the registered 4F authenticator
 
 @return the registered 4F authenticator (or nil if not registered)
 */
-(VeridiumBiometrics4FAuthenticator* _Nullable) authenticator4F;

/*!
 Helper method to configure the registered 4F enroller
 
 @param config the config
 */
-(void)configure4FEnroler:(Veridium4FEnrollConfig * _Nonnull)config;

/*!
 Helper method for grabbing the registered 4F enroller
 
 @return the registered 4F enroller (or nil if not registered)
 */
-(VeridiumBiometrics4FEnroller* _Nullable) enroller4F;

/*!
 Helper method for grabbing the registered 4F explorter
 
 @return the registered 4F exporter (or nil if not registered)
 */
-(VeridiumBiometrics4FExporter* _Nullable) exporter4F;


/*!
 Helper method for creating a 4F enroller and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4F enroller
 */
-(VeridiumBiometrics4FEnroller* _Nonnull) create4FEnrollerWithConfig:(Veridium4FEnrollConfig * _Nonnull) config;

/*!
 Helper method for creating a 4F authenticator and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4F authenticator
 */
-(VeridiumBiometrics4FAuthenticator* _Nonnull) create4FAuthenticatorWithConfig:(Veridium4FAuthenticationConfig * _Nonnull) config;


@end
