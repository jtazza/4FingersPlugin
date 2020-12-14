//
//  SimpleAggregatedBioEnroller.h
//  VeridiumCore
//
//  Created by razvan on 5/11/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VeridiumBiometricsProtocols.h"


/*!
 Subprotocol of VeridiumBioEnroller that adds to an enroller the ability to be skipped during an aggregated biometric enrollment
 
 Skippable enrollers will trigger an 'enroll next' action when the user cancels
 */
@protocol VeridiumSkippableEnrollerProtocol <VeridiumBioEnroller>

/*!
 Return `true` if you wish your enroller to be skippable or `false` if you it want to be mandatory
 */
@property (readonly) BOOL canBeSkipped;

@end

/*!
 The VeridiumSkippableEnrollerProtocol default implementation that wraps an existing enroller into a skippable implementation
 */
@interface VeridiumSkippableEnrollerDecorator : NSObject <VeridiumSkippableEnrollerProtocol>

/*!
 Designated initializer
 
 @param enroller     an existing enroller
 @param canBeSkipped pass `true` if the enroller can be skipped `false` otherwise
 */
-(instancetype)init:(id<VeridiumBioEnroller>)enroller skippable:(BOOL) canBeSkipped;

@end


/*!
 A VeridiumBioEnroller implementation that chains multiple enrollers into a single enrollment process
 */
@interface VeridiumAggregatedBioEnroller : NSObject <VeridiumBioEnroller>


/*!
 Static initializer
 
 @param enrollers the enrollers to be chained
 */
+(instancetype) newWithEnrollers:(NSArray<id<VeridiumBioEnroller>>*)enrollers;

/*!
 Designated initializer
 
 @param enrollers the enrollers to be chained
 */
-(instancetype)init:(NSArray<id<VeridiumBioEnroller>>*) enrollers;

@end



/*!
 A VeridiumBioAuthenticator implementation that chains multiple authenticators into a single authentication process
 */
@interface VeridiumAggregatedBioAuthenticator : NSObject

/*!
 Static initializer
 
 @param authenticators authenticators to be chained
 */
+(instancetype) newWithAuthenticators:(NSArray<id<VeridiumBioAuthenticator>>*) authenticators;

/*!
 Designated initializer
 
 @param authenticators authenticators to be chained
 */
-(instancetype)init:(NSArray<id<VeridiumBioAuthenticator>>*)authenticators;

@property (readonly) NSArray<id<VeridiumBioAuthenticator>>* authenticators;


-(void)chainAuthenticate:(NSString*)reason onSuccess:(voidBlock)onSuccessBlock onFail:(stringBlock)onFailBlock onCancel:(voidBlock)onCancelBlock onError:(stringBlock)onErrorBlock;

/*!
 Autentication aggregated results in the form 'Engine name':'Result' (e.g. '4F':'AUTHENTICATED')
 */
@property (readonly) NSDictionary<NSString*,NSString*>* authAggregatedResults;

@end
