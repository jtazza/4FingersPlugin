//
//  VeridiumMemoryKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 5/10/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VeridiumKeyValueStore.h"

/*!
 NSDictionary implementation of KeyValueStore protocol
 */
@interface VeridiumMemoryKeyValueStore : NSObject  <VeridiumKeyValueStore>

-(NSDictionary *) getMemoryDictionary;

/*!
 Loads data from another dictionary
 
 @param dict the data dictionary
 */
-(void) initWithDictionary: (NSDictionary*) dict;

@end
