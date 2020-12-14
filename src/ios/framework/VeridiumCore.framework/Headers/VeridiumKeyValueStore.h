//
//  VeridiumKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 3/14/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Protocol abstracting a key-value storage
 */
@protocol VeridiumKeyValueStore <NSObject>

/*!
 Stores a string in the store under the specified key

 For simplicity the values can only be strings. For complex objects you will need to store either your custom serialization into a string or you can use the coveninent [NSArray JSONString] and [NSDictionary JSONString] extensions declared in VeridiumUtils
 
 @param value The value.
 @param key   The key.
 
 */
-(void) store:(NSString* _Nullable)value forKey:(NSString* _Nonnull)key;


/*!
 Retrieves a string stored under the specified key (if available)

 For complex objects you will need to handle the deserialization yourself, i.e. using the [NSString JSONArray], [NSString JSONDictionary] extensions declared in VeridiumUtils (or your custom method if you serialized the string yourself using your own custom way)
 
 @param key The key.
 
 @return the stored value or nil if not found.
 
 */
-(NSString* _Nullable) get:(NSString* _Nonnull) key;


/*!
 Clears all data from the store
 
 __Use with care!__
 */
-(void)clearAllData;

@end
