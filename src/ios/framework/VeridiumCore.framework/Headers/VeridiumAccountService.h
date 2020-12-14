//
//  VeridiumAccountService.h
//  VeridiumCore
//
//  Created by razvan on 12/23/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VeridiumUtils.h"
#import "VeridiumAccount.h"
#import "VeridiumBiometricsProtocols.h"


/*!
 Abstract class that implements the basic VeridiumAccount manipulation.
 */
@interface VeridiumAccountService : NSObject

/*!
 Property for accessing the currently active VeridiumAccount
 
 This property is nil when there are no accounts registered.
 */

@property (nonatomic, readonly, nullable) VeridiumAccount* activeAccount;

/*!
 Switches the active account to another VeridiumAccount
 
 The passed argument must be a registered account or the call has no effect
 
 @param account a registered VeridiumAccount instance
 */
-(void)switchActiveAccount:(VeridiumAccount* _Nonnull) account;


/*!
  Property for accessing the currently registered accounts.
 
 You can ignore this in sigle account apps (it will always return an array with only one element - the active account)
 */
@property (nonatomic, nonnull, readonly) NSArray<VeridiumAccount*>* registeredAccounts;


/*!
 Clears all locally stored data pertaining to the specified VeridiumAccount (keychain & user defaults)
 
 @param account a registered VeridiumAccount instance
 */
-(void) clearRegisteredAccountData:(VeridiumAccount * _Nonnull)account;

/*!
 Clears all locally stored data pertaining to the currently active account
 
 This is a convenience method. It does the same thing as calling [VeridiumAccountService clearRegisteredAccountData:] with [activeAccount]([VeridiumAccountService activeAccount]) as argument
 */
-(void) clearActiveAccountData;


@end
