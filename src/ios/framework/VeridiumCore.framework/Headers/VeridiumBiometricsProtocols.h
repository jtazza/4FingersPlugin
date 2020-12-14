//
//  BiometricsProtocols.h
//  VeridiumCore
//
//  Created by razvan on 11/23/15.
//
//

#import "VeridiumUtils.h"
#import "VeridiumBiometricVector.h"
#import "VeridiumAccount.h"

#pragma mark Biometric interface protocols


/*!
 Block that receives a vector
 @param  the vector
 */
typedef void(^biometricVectorBlock)(VeridiumBiometricVector* _Nonnull);

/*!
  Block that receives a nullable vector
  @param  the nullable vector
 */
typedef void(^biometricVectorUpdateBlock)(VeridiumBiometricVector* _Nullable);


@protocol VeridiumBiometricMatchingStrategy <NSObject>

-(void) match:(VeridiumBiometricVector* _Nonnull)probe whenDone:(boolBlock _Nonnull) whenDone onError:(stringBlock _Nonnull) onError;

@end


/*!
 Protocol implemented by external biometric matching providers with full matching on the server side (eg. BOPS matcher)
 
 An implementor of this protocol should be passed to the authenticator's [VeridiumBioAuthenticator createFullRemoteMatchingStrategyWithRemoteMatchProvider:]
 */
@protocol VeridiumBiometricsFullExternalMatchProvider <NSObject>

/*!
 Ask the external matching provider to perform a biometric match against a remotely stored full enrollment vector
 
 This method is to be implemented by the integrations where storage of the enrollment vector is assured by your app (eg. store the vector on a server)
 
 
 @param probe   the VeridiumBiometricVector to be verified
 @param successBlock       completion callback voidBlock
 @param failBlock       fail callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) match:(VeridiumBiometricVector* _Nonnull) probe onSuccess:(voidBlock _Nonnull) successBlock onFail:(voidBlock _Nonnull) failBlock onError:(stringBlock _Nonnull) onError;

@end


/*!
 Protocol implemented by external biometric matching providers with split matching on the server (eg. BOPS matcher)
 
 An implementor of this protocol should be passed to the authenticator's [VeridiumBioAuthenticator createSplitRemoteMatchingStrategyWithLocalStore:remoteMatchProvider:]
 */
@protocol VeridiumBiometricsSplitExternalMatchProvider <NSObject>

@optional
/*!
 Ask the external mathching provider to perform a biometric match against a locally stored splitted enrollment vector asynchronously
 
 The whenDone completion block aside from the boolean outcome receives a NSData argument that some biometric engines can use to provide an updated private enrollment vector half (e.g. 4F updates its enrollment vector during authentication to improve the
 
 If you integrate a 3rd party biometric into VeridiumSDK you can use this data param to update the enrollment vector and must handle the saving inside your VeridiumBioAuthenticator implementation
 
 @param probe   the VeridiumBiometricVector to be verified
 @param privateVector the enrolled VeridiumBiometricVector stored on the device
 @param successBlock       completion callback biometricVectorUpdateBlock; receives the updated private half of the enrollment biometric data
 @param failBlock       fail callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) match:(VeridiumBiometricVector* _Nonnull) probe privateVector:(VeridiumBiometricVector* _Nonnull) privateVector onSuccess:(biometricVectorUpdateBlock _Nonnull) successBlock onFail:(voidBlock _Nonnull) failBlock onError:(stringBlock _Nonnull) onError;


@end


/*!
 Protocol adopted by an external storage system for updating an externally stored splitted enrollment biometric vector
 */
@protocol VeridiumBioMatchPublicVectorDelegate <NSObject>

/*!
 Ask the external storage to update the public half of a splitted enrollment biometric vector asynchronously
 
 @param publicVector the VeridiumBiometricVectorWithMatchingPairTag instance that holds the public biometric vector half and a tag (a hash) of the private half for pairing them later during matching
 @param onSuccess the success callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) updateBiometricVector:(VeridiumBiometricVector* _Nonnull) publicVector onSuccess:(voidBlock _Nonnull) onSuccess onError:(stringBlock _Nonnull) onError;

/*!
 Ask the external system to fetch the public half of a splitted enrollment biometric vector asynchronously
 
 @param privateVectorTag the privateVectorTag used to identify the corresponding half in the external system
 @param onSuccess the success callback biometricVectorBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) fetchBiometricVectorCorrespondingToTag:(NSString* _Nonnull) privateVectorTag onSuccess:(biometricVectorBlock _Nonnull) onSuccess onError:(stringBlock _Nonnull) onError;


@end


/*
 Protocol for export configuration options.
 */
@protocol VeridiumBiometricExportConfig <NSObject>
@property (nonatomic, nonnull) NSString* engineName;
@end

/*
 Protocol for enroll configuration options.
 */
@protocol VeridiumBiometricEnrollConfig <NSObject>
@property (nonatomic, nonnull) NSString* engineName;
@end

/*!
 Protocol adopted by biometric engines to provide support for biometric enrollment
 
 Biometric engines usually implement also the BioAuthenticator protocol for handling authentication.
 
 However not all of them do, e.g. `TouchID` whose enrollment is handled by the system
 
 */
@protocol VeridiumBioEnroller <NSObject>



/*!
 The engine name property uniquely identifies biometric engines
 */
@property (readonly, nonatomic, nonnull) NSString* engineName;


///---------------------
/// @name Enrollment
///---------------------

/*!
 Ask the biometric engine to perform biometric enrollment
 
 @param onSuccess the success callback voidBlock
 @param onFail    the fail callback stringBlock; receives the failure reason
 @param onCancel  the cancell callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) enroll:(biometricVectorBlock _Nonnull) onSuccess
        onFail:(stringBlock _Nonnull) onFail
      onCancel:(voidBlock _Nonnull) onCancel
       onError:(stringBlock _Nonnull) onError;

@optional
-(void) updateConfigForEnrollAfterExportWithConfig:(id<VeridiumBiometricExportConfig> _Nonnull)exportConfig;

@end

/*!
 Protocol adopted by biometric engines to provide authentication support
 
 Biometric engines usually implement also the BioAuthenticator protocol for handling authentication.
 
 However not all of them do, e.g. `TouchID` whose enrollment is handled by the system
 */
@protocol VeridiumBioAuthenticator <NSObject>

/*!
 The engine name property uniquely identifies biometric engines
 */
@property (readonly, nonatomic, nonnull) NSString* engineName;


/*!
 Ask the biometric engine to perform the biometric authentication
 
 @param reason         the authentication reason
 @param onSuccess the success callback voidBlock
 @param onFail    the fail callback stringBlock; receives the failure reason
 @param onCancel  the cancell callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) authenticate:(NSString* _Nullable)reason
           onSuccess:(voidBlock _Nonnull) onSuccess
              onFail:(stringBlock _Nonnull) onFail
            onCancel:(voidBlock _Nonnull) onCancel
             onError:(stringBlock _Nonnull) onError;


/*!
 Ask the engine to produce a local only matching strategy configured for a provided KV store

 @param store the KV store

 @return the configured strategy
 */
+(id<VeridiumBiometricMatchingStrategy> _Nonnull) createFullLocalMatchingStrategyWithLocalStore:(id<VeridiumKeyValueStore> _Nonnull) store;


/*!
  Ask the engine to produce a split local matching strategy configured for a provided KV store and a remote public vector delegate

 @param store          the KV store
 @param remoteDelegate <#remoteDelegate description#>

 @return the configured strategy
 */
+(id<VeridiumBiometricMatchingStrategy> _Nonnull) createSplitLocalMatchingStrategyWithLocalStore:(id<VeridiumKeyValueStore> _Nonnull) store remoteVectorDelegate:(id<VeridiumBioMatchPublicVectorDelegate> _Nullable) remoteDelegate;



/*!
  Ask the engine to produce a split remote matching strategy configured for a provided KV store and an external match provider

 @param store          the KV store
 @param remoteMatchProvider the external match provider

 @return the configured strategy
 */
+(id<VeridiumBiometricMatchingStrategy> _Nonnull) createSplitRemoteMatchingStrategyWithLocalStore:(id<VeridiumKeyValueStore> _Nonnull) store remoteMatchProvider:(id<VeridiumBiometricsSplitExternalMatchProvider> _Nonnull) remoteMatchProvider;


/*!
  Ask the engine to produce a full remote matching strategy configured for a provided KV store and an external match provider

 @param store          the KV store
 @param remoteMatchProvider the external match provider

 @return the configured strategy
 */
+(id<VeridiumBiometricMatchingStrategy> _Nonnull) createFullRemoteMatchingStrategyWithLocalStore:(id<VeridiumKeyValueStore> _Nonnull)store remoteMatchProvider:(id<VeridiumBiometricsFullExternalMatchProvider> _Nonnull) remoteMatchProvider;



/*!
 Configure the matching strategy for the next authentication

 @param matchingStrategy the configured matching strategy
 */
-(void) configureMatchingStrategy:(id<VeridiumBiometricMatchingStrategy> _Nonnull) matchingStrategy;

-(BOOL)useLeftHand;

/*!
 Call this to check whether the engine can authenticate using the provided KV store

 @param store the store

 @return `TRUE` if the engine can perform the authentication, `FALSE` otherwise
 */
-(BOOL) canAuthenticateWithLocalStore:(id<VeridiumKeyValueStore> _Nonnull) store;

@optional
-(void) updateConfigForAuthenticateAfterExportWithConfig:(id<VeridiumBiometricExportConfig> _Nonnull)exportConfig;

@end


/*!
 Protocol adopted by biometric engines to provide support for biometric enrollment
 
 Biometric engines usually implement also the BioAuthenticator protocol for handling authentication.
 
 However not all of them do, e.g. `TouchID` whose enrollment is handled by the system
 
 */
@protocol VeridiumBioExporter <NSObject>


/*!
 The engine name property uniquely identifies biometric engines
 */
@property (readonly, nonatomic, nonnull) NSString* engineName;


///---------------------
/// @name Export
///---------------------

/*!
 Ask the biometric engine to export a biometric in a configurable format.
 
 @param settings  an object containing configuration options.
 @param onSuccess the success callback voidBlock
 @param onFail    the fail callback stringBlock; receives the failure reason
 @param onCancel  the cancell callback voidBlock
 @param onError   the error callback stringBlock; receives the error message
 */
-(void) exportTemplateWithSettings:(id<VeridiumBiometricExportConfig> _Nonnull) settings
                         onSuccess:(biometricVectorBlock _Nonnull) onSuccess
                            onFail:(stringBlock _Nonnull) onFail
                          onCancel:(voidBlock _Nonnull) onCancel
                           onError:(stringBlock _Nonnull) onError;

/*
 Indicate whether a configuration is supported. This is most useful for consumers which afford the user multiple configuration options.
 */
-(BOOL) verifyConfigure:(id<VeridiumBiometricExportConfig> _Nonnull)config;

@end


#pragma mark UI Delegate protocols

/*!
 Base protocol used to connect the biometric engine and it's hangling UI implementation.
 
 It specifies the contract for common UI traits shared by all biometric engine types. This protocol is extended by each biometric implementation that adds specific UI methods specs.
 */
@protocol VeridiumBiometricsUIDelegate <NSObject>

/*!
 Ask the UI to present itself and waits for completion
 
 @param doneBlock the completion callback voidBlock
 */
//-(void) show:(voidBlock _Nonnull) doneBlock;

/*!
 Ask the UI to present itself and waits for completion
 
 @param doneBlock the completion callback voidBlock
 */
-(void) show:(voidBlock _Nonnull) doneBlock withThumb:(BOOL)captureThumb andIndividualCapture:(BOOL)individualCapture andIndividualThumb:(BOOL)thumbPresent andIndividualIndex:(BOOL)indexPresent andIndividualMiddle:(BOOL)middlePresent andIndividualRing:(BOOL)ringPresent andIndividualLittle:(BOOL)littlePresent;

/*!
 Ask the UI to handle the successful outcome of the auth/enroll operation (e.g. show message and remove itself from the UI stack) and waits for completion
 
 @param doneBlock the completion callback voidBlock
 */
-(void) handleSuccess:(voidBlock _Nonnull)doneBlock;

/*!
 Ask the UI to handle the failure of the auth/enroll operation (e.g. show the failure reason and remove itself from the UI stack) and waits for completion
 
 @param message   the failure reason (e.g. match fail, timeout)
 @param doneBlock the completion callback voidBlock
 */
-(void) handleFail:(NSString* _Nonnull) message whenDone:(voidBlock _Nonnull)doneBlock;

/*!
 Ask the UI to handle the successful outcome of the auth/enroll operation (e.g. remove itself from the UI stack) and waits for completion
 
 @param doneBlock the completion callback voidBlock
 */
-(void) handleCancel:(voidBlock _Nonnull)doneBlock;

/*!
 Ask the UI to handle the erroneous outcome of the auth/enroll operation (e.g. show the error message and remove itself from the UI stack) and waits for completion
 
 @param message   the failure message
 @param doneBlock the completion callback voidBlock
 */
-(void) handleError:(NSString* _Nonnull) message whenDone:(voidBlock _Nonnull)doneBlock;

@optional

/*!
 By calling this function the engine provides a block to be called by the UI when the user initiates a cancel action (e.g. when the user hits a cancel button).
 
 The block is to be stored by the implementor of the protocol and used later when the user initiates the cancel action.
 
 The engine will do all the internal operations pertaining to the cancel procedure (ie. turn off camera, release allocated resources,etc..) and then call the cancel the handleCancel: method of the delegate to allow the UI to peform its post cancel UI actions
 
 @param cancelActionBlock The cancel callback action block to be stored and called by the delegate when the user initiates a cancel action
 */
-(void) connectCancelAction:(voidBlock _Nonnull) cancelActionBlock;

-(void) connectTapToCaptureAction:(voidBlock _Nonnull) tapToCaptureActionBlock;

/*!
 Ask the UI to handle the state in which the engine is waiting for the user to manually start the operation
 
 You can skip the implementation of this method if you always configure the engine to start automatically
 
 Usually this method makes available to the user a start button (or a tap recognizer) to manually start the operation and calls the callback block in the UI handler of the tap event.
 
 Calling the callback block begins the enroll/auth operation and starts the timeout timer
 
 @param manualStartBlock the manual start callback voidBlock
 */
-(void) handleWaitingForManualStart:(voidBlock _Nonnull) manualStartBlock;

/*!
 Ask UI to handle the overall progress update.
 The UI usually uses the passed value to update a progress bar or a label displaying the progress
 
 @param progressPercent progress value between 0 and 1 (1 = 100%)
 */
-(void) handleNormalizedProgressUpdate:(float) progressPercent;

/*!
 Ask UI to handle the progress update with exact seconds passeed out of total seconds
 
 The UI usually uses the passed values to display a countdown or a x/y seconds
 
 @param progressPassedSeconds the passed seconds
 @param totalSeconds the total number of seconds until operation times out
 */
-(void) handleProgressUpdateWithPassedSeconds:(float) progressPassedSeconds outOfTotalSeconds:(float) totalSeconds;


@end
