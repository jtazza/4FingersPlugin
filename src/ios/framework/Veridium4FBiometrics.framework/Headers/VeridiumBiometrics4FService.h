//
//  VeridiumBiometrics4FService.h
//  Veridium4FBiometrics
//
//  Created by Josiah Kane on 07/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumBiometrics4FService_h
#define VeridiumBiometrics4FService_h


#import <Foundation/Foundation.h>
#import "VeridiumBiometrics4FCommon.h"
#import "VeridiumBiometrics4FEnrollment.h"
#import "VeridiumBiometrics4FConfig.h"


#import "VeridiumBiometrics4FAuthenticator.h"
#import "VeridiumBiometrics4FEnroller.h"
#import "VeridiumBiometrics4FExporter.h"



@interface VeridiumBiometrics4FService : NSObject

+(void)enroll:(VeridiumBiometrics4FConfig * _Nonnull) config
            onSuccess:(void (^)(VeridiumBiometrics4FEnrollment* _Nonnull)) successBlock
               onFail:(stringBlock _Nonnull) failBlock
             onCancel:(voidBlock _Nullable) cancelBlock
              onError:(stringBlock _Nonnull) errorBlock;

+(void)authenticate:(VeridiumBiometrics4FConfig* _Nonnull) config
            against:(VeridiumBiometrics4FEnrollment*) enrollment
          onSuccess:(voidBlock _Nonnull) successBlock
             onFail:(stringBlock _Nonnull) failBlock
           onCancel:(voidBlock _Nullable) cancelBlock
            onError:(stringBlock _Nonnull) errorBlock;

/*!
 Exports data using the requested biometric export methods
 
 @param config       VeridiumExportConfig filled in with the export information
 @param successBlock success callback biometricVectorBlock
 @param failBlock    fail callback stringBlock; receives the failure reason
 @param cancelBlock  cancel callback
 @param errorBlock   error callback stringBlock; receives the failure reason
 */
+(void)exportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
            onSuccess:(biometricVectorBlock _Nonnull) successBlock
               onFail:(stringBlock _Nonnull) failBlock
             onCancel:(voidBlock _Nullable) cancelBlock
              onError:(stringBlock _Nonnull) errorBlock;

+(void)enrollAndExportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
                     onSuccess:(void (^)(VeridiumBiometrics4FEnrollment* _Nonnull, VeridiumBiometricVector* _Nonnull)) successBlock
                        onFail:(stringBlock _Nonnull) failBlock
                      onCancel:(voidBlock _Nullable) cancelBlock
                       onError:(stringBlock _Nonnull) errorBlock;

+(void)authenticateAndExportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
                             against:(VeridiumBiometrics4FEnrollment*) enrollment
                           onSuccess:(biometricVectorBlock _Nonnull) successBlock
                              onFail:(stringBlock _Nonnull) failBlock
                            onCancel:(voidBlock _Nullable) cancelBlock
                             onError:(stringBlock _Nonnull) errorBlock;


+(BOOL)checkIfSuppressingAllScreens;

@end


#endif /* VeridiumBiometrics4FService_h */
