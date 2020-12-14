//
//  VeridiumBiometrics4FEnrollment.h
//  Veridium4FBiometrics
//
//  Created by Josiah Kane on 08/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumBiometrics4FEnrollment_h
#define VeridiumBiometrics4FEnrollment_h

#import "VeridiumBiometrics4FCommon.h"

//typedef VeridiumBiometricVector* VeridiumBiometrics4FEnrollment ; // FIXME For the moment, an enrollment is just the data.

@interface VeridiumBiometrics4FEnrollment : NSObject

- (id) initWithSerializedData:(NSData *)data;
- (id) initWithBiometricVector:(VeridiumBiometricVector*)biometricVector;

// For internal use only.
- (void) updateWithSerializedData:(NSData *)data;

- (NSData * _Nonnull) serialize;

- (BOOL) isDirty;

@end


#endif /* VeridiumBiometrics4FEnrollment_h */
