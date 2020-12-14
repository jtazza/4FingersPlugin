//
//  AccountData.h
//  VeridiumCore
//
//  Created by razvan on 1/22/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VeridiumKeychainKeyValueStore.h"
#import "VeridiumUserDefaultsKeyValueStore.h"
#import "VeridiumUtils.h"

@class VeridiumAccount;

/*!
 Groups all the information pertaining to a registered account.
 */
@interface VeridiumAccount : NSObject

/*!
 The account's unique identifier.
 */
@property (readonly, nonnull) NSString* accountId;

/*!
 The Keychain KV Store attached to the account
 
 You can use this to store your app's specific secured data in the context of the account (once it's registered)
 */
@property (readonly, nonnull) VeridiumKeychainKeyValueStore* kcStore;

/*!
 The UserDefaults Store attached to the account
 
 You can use this to store your own data in the user preferences in the context of the account
 */
@property (readonly, nonnull) VeridiumUserDefaultsKeyValueStore* udStore;


/*!
 Designated initializer. It should not be called directly. It is used by the AccountService internally.
 
 @param accountId   The account unique identifier.
 
 @return the initialized AccountData object.
 */
- (instancetype _Nonnull)initWithAccountId:(NSString* _Nonnull) accountId;


/*!
 Clears all account data (everything stored in the keychain and user defaults in the account's context)
 */
-(void)clearAllData;

@end
