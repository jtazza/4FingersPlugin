//
//  VeridiumUserDefaultsKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 3/14/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import "VeridiumKeyValueStore.h"

/*!
 NSUserDefaults implementation of KeyValueStore protocol
 */
@interface VeridiumUserDefaultsKeyValueStore : NSObject <VeridiumKeyValueStore>

/*!
 Designated initializer
 
 @param masterKey the master key of the instance (all values will be stored as sub keys of this key)
 */
-(instancetype _Nonnull)initWithMasterKey:(NSString* _Nonnull)masterKey;

@end
