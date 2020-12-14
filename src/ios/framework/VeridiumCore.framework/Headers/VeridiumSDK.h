//
//  VeridiumSDK.h
//  VeridiumCore
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VeridiumPushHandlerProtocol.h"
#import "VeridiumUtils.h"
#import "VeridiumAccountService.h"
#import "VeridiumAggregationHelpers.h"
#import "VeridiumBiometricsProtocols.h"
#import "VeridiumLicenseStatus.h"

/*!
 This `Veridium SDK` class is the main entry point of any interraction with VeridiumSDK.
 
 This acts as a singleton that must be initialized using the `setup:` static method before use
 
 */
@interface VeridiumSDK : NSObject

///---------------------
/// @name Setting up
///---------------------

/*!
This static initializer used to configure the SDK

If the license provided checks out then all the other SDK functionality can be accessed via the static `sharedSDK` property.

**IMPORTANT!** This method must be called prior to any call to `VeridiumSDK.sharedSDK`.
Best place to put it would be in [AppDelegate application: didFinishLaunchingWithOptions:]

This method initializes the `setupFailureHandler` with a default block that displays an alert with the message `You're using an outdated version of the app.\nPlease update.` (see `setup:failureHandler:` method that allows you to customize this behavior)

@param license The license key issued to you by Veridium
@return initialisation status
*/
+(VeridiumLicenseStatus* _Nonnull) setup:(NSString* _Nonnull)license;

/*!
 This static initializer used to configure the SDK
 
 If the license provided checks out then all the other SDK functionality can be accessed via the static `sharedSDK` property.

**IMPORTANT!** This method must be called prior to any call to `VeridiumSDK.sharedSDK`.
Best place to put it would be in [AppDelegate application: didFinishLaunchingWithOptions:]
 
 The `setupFailureHandler` param is provided as means to "gracefully" force the users to update to a newer version of the integrating app when the license changes
 
 If not provided the SDK will throw and exception on any access of `VeridiumSDK.sharedSDK` property
 
 This block is dispatched **ONLY ONCE** asyncronously on the main queue
 
 @param license The license key issued to you by Veridium
 @param setupFailureHandler Optional block for handling setup failure (e.g. license expired)
 @return initialisation status
 */
+(VeridiumLicenseStatus* _Nonnull) setup:(NSString* _Nonnull)license failureHandler:(voidBlock _Nullable) setupFailureHandler;


///---------------------
/// @name Main entry point after setup
///---------------------

/*!
 This is the entry point for all operations on the SDK. 
 
 If this is called without proper setup it will throw an exception.
 
 @return the SDK shared instance
 
 @exception NSException with name `SDKNotInitialized` if the SDK hasn't been properly initialized
 */
@property (readonly, class, nonnull) VeridiumSDK* sharedSDK;


///---------------------
/// @name Push notifications handling
///---------------------

/*!
 Registers the APNS token
 
 This method should be called from your app's [AppDelegate application: didRegisterForRemoteNotificationsWithDeviceToken:] method
 
 @param pushTokenData the push token data returned by the APNS server
 */
-(void) registerPushToken:(NSData* _Nullable) pushTokenData;

/*!
 Returns the registered push token (if registered previously using [VeridiumSDK registerPushToken:]
 */
@property (readonly, nullable) NSString* pushToken;

/*!
 Registers a custom VeridiumPushHandlerProtocol instance
 
 The SDK uses a publisher-subscriber pattern for the push notifications handling, thus all registered subscribers will receive all notifications
 
  @param pushHandler a VeridiumPushHandlerProtocol instance
 */
-(void) registerPushHandler:(id<VeridiumPushHandlerProtocol> _Nonnull) pushHandler;

/*!
   You need to wire this call in your app's [AppDelegate application:didReceiveRemoteNotification:] and  [AppDelegate application:didFinishLaunchingWithOptions:] methods. For polling this will be called internally by the SDK and it will in turn pass it to each push handlers registered via the registerPushHandler: method
 
   @param pushData The push data
   @param isAPNS Specifies whether this is a push or a serverside notification received via polling. When you call this from AppDelegate you always pass true
 */
-(void) handlePush:(NSDictionary<NSString*,id>* _Nonnull) pushData isAPNS:(BOOL) isAPNS;


///---------------------
/// @name Biometrics
///---------------------

/*!
   Registers a biometric authenticator (VeridiumBioAuthenticator implementation) with the SDK
   (_Note:_ the VeridiumTouchIDAuthenticator is automatically registered by the SDK if available on the device)
 
   @param authenticator the VeridiumBioAuthenticator instance
 */
-(void)registerAuthenticator:(id<VeridiumBioAuthenticator> _Nonnull)authenticator;


/*!
   Registerd a biometric enroller (VeridiumBioEnroller implementation) with the SDK
 
   @param enroller the VeridiumBioEnroller instance
 */
-(void)registerEnroller:(id<VeridiumBioEnroller> _Nonnull)enroller;

-(id<VeridiumBioEnroller>)getEnrollerFromBiometricName:(NSString* _Nonnull)biometric;

/*!
 Registers a biometric exporter (VeridiumBioExporter implementation) with the SDK
 
 @param exporter the VeridiumBioExporter instance
 */

-(void)registerExporter:(id<VeridiumBioExporter> _Nonnull)exporter;

-(id<VeridiumBioExporter> _Nullable)getExporterFromBiometricName:(nonnull NSString*)biometric;

/*!
 Creates an aggregated biometric enroller using the registered enrollers for the requsted methods
 
 If no engine is found registered for any of the requested methods the error parameter will be set and the return value will be nil.
 
 @param methods array with methods aka engine names ( eg. "TOUCHID", "4F", "FACE", "YOUR_CUSTOM_ENGINE")
 @param error   the error
 
 @return instance of VeridiumAggregatedBioEnroller in case of success, `nil` otherwise
 */
-(VeridiumAggregatedBioEnroller* _Nullable) aggregatedEnrollerForMethods:(NSArray<NSString *> * _Nonnull)methods error:(NSError * _Nullable __autoreleasing * _Nullable)error;

/*!
 Creates an aggregated biometric enroller using the registered enrollers for the requsted methods
 
 If no engine is found registered for any of the requested methods the error parameter will be set and the return value will be nil.
 
 @param methods array with methods aka engine names ( eg. "TOUCHID", "4F", "FACE", "YOUR_CUSTOM_ENGINE")
 @param error   the error
 
 @return instance of VeridiumAggregatedBioAuthenticator in case of success, `nil` otherwise
 */
-(VeridiumAggregatedBioAuthenticator* _Nullable) aggregatedAuthenticatorForMethods:(NSArray<NSString *> * _Nonnull)methods error:(NSError * _Nullable __autoreleasing * _Nullable)error;

/*!
 Creates an aggregated biometric enroller using the provided enrollers
 
 @param enrollers array of VeridiumBioEnroller instances
 @return instance of VeridiumAggregatedBioEnroller in case of success, `nil` otherwise

 */
-(VeridiumAggregatedBioEnroller* _Nullable) aggregatedEnrollerWithEnrollers:(NSArray<id<VeridiumBioEnroller>>* _Nonnull) enrollers;

/*!
 Creates an aggregated biometric authenticator using the provided enrollers
 
 @param authenticators array of VeridiumBioAuthenticator instances
 @return instance of VeridiumAggregatedBioAuthenticator in case of success, `nil` otherwise
 
 */
-(VeridiumAggregatedBioAuthenticator* _Nonnull) aggregatedAuthenticatorWithAuthenticators:(NSArray<id<VeridiumBioAuthenticator>>* _Nonnull) authenticators;


/*!
 Retuns the registered authenticator for the sepcified method (if any)
 
 @param method the method (aka engine name)
 
 @return the registered authenticator or `nil` if not found
 */
-(id<VeridiumBioAuthenticator> _Nullable) authenticatorForMethod:(NSString * _Nonnull)method;

/*!
 Retuns the registered enroller for the sepcified method (if any)
 
 @param method the method (aka engine name)
 
 @return the registered enroller or `nil` if not found
 */
-(id<VeridiumBioEnroller> _Nullable) enrollerForMethod:(NSString * _Nonnull)method;

/*!
 The list with engines names of all registered biometric authenticators
 */
@property (readonly,nonatomic,nonnull) NSArray<NSString*>* registeredAuthenticationBiometricMethods;

/*!
 The list with engines names of all registered biometric enrollers
 */
@property (readonly,nonatomic,nonnull) NSArray<NSString*>* registeredEnrollBiometricMethods;

/*!
Retuns the registered exporter for the sepcified method (if any)

@param method the method (aka engine name)

@return the registered enroller or `nil` if not found
*/
-(id<VeridiumBioExporter>)exporterForMethod:(NSString *)method;

@end
