//
//  VeridiumExportService.h
//  Veridium
//
//  Created by Josiah Kane on 12/12/2016.
//  Copyright © 2016 Veridium. All rights reserved.
//

#ifndef VeridiumExportService_h
#define VeridiumExportService_h

#import <Foundation/Foundation.h>
#import "VeridiumBiometricsProtocols.h"
#import "VeridiumUtils.h"
#import "VeridiumSDK.h"
#import "VeridiumBiometricVector.h"



@interface VeridiumExportService : NSObject

/*!
 Exports data using the requested biometric export methods
 
 @param config       VeridiumExportConfig filled in with the export information
 @param successBlock success callback accountBlock
 @param failBlock    fail callback stringBlock; receives the failure reason
 @param cancelBlock  cancel callback
 @param errorBlock   error callback stringBlock; receives the failure reason
 */
-(void)exportTemplate:(NSObject<VeridiumBiometricExportConfig> * _Nonnull)config
            onSuccess:(biometricVectorBlock _Nonnull) successBlock
               onFail:(stringBlock _Nonnull) failBlock
             onCancel:(voidBlock _Nullable) cancelBlock
              onError:(stringBlock _Nonnull) errorBlock __attribute__ ((deprecated));

-(void)exportAndEnrollTemplate:(NSObject<VeridiumBiometricExportConfig> * _Nonnull)config
                    onSuccess:(void (^)(VeridiumBiometricVector*, VeridiumBiometricVector*)) successBlock
                       onFail:(stringBlock _Nonnull) failBlock
                     onCancel:(voidBlock _Nullable) cancelBlock
                      onError:(stringBlock _Nonnull) errorBlock __attribute__ ((deprecated));

@end



#endif /* VeridiumExportService_h */
