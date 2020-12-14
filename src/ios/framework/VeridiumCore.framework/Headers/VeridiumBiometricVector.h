//
//  VeridiumBiometricVector.h
//  VeridiumCore
//
//  Created by razvan on 5/11/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "VeridiumKeyValueStore.h"

#define kVeridiumBiometricVectorFormatFullVector @"FULL"
#define kVeridiumBiometricVectorFormatLocalShadow @"LOCAL_SHADOW"
#define kVeridiumBiometricVectorFormatEncryptedVisualCrypto @"ENCRYPTED_VC"


/*!
 Data class for holding a biometric vector and its metadata.
 */
@interface VeridiumBiometricVector : NSObject

/*!
 Vector type - produced by the biometric engine (and is equal with the engine name)
 */
@property (readonly, nonnull) NSString* type;

/*!
 Vector version - produced by the biometric engine
 */
@property (readonly, nonnull) NSString* version;

/*!
 Vector format - custom string interpreted by the biometric engine
 */
@property (readonly, nonnull) NSString* format;

/*!
 The actual binary data of the biometric vector (encrypted)
 */
@property (readonly, nonnull) NSData* biometricData;

/*!
 Convenience property for getting the vector with its metadata in a JSON format
 */
@property (readonly, nonnull) NSString* asJSON;


/*!
 Extra meta data stored alongside with the raw biometric vector data
 */
@property (nullable) NSDictionary* extraData;

/*!
 Convenience property for getting the vector with its metadata as a NSDictionary
 */
@property (readonly, nonnull) NSDictionary<NSString*,id>* asDictionary;


/*!
 Call this to store the vector data into the provided KV store

 @param store the taget KV store
 */
-(void) storeInto:(id<VeridiumKeyValueStore> _Nonnull) store;


/*!
 Static initializer that loads the vector from the provided KV store

 @param store the source KV store
 @param key   the key under which the vector was stored (typically the engine name)

 @return the loaded vector if the load was successful, `nil` otherwise
 */
+(instancetype _Nullable) loadFrom:(id<VeridiumKeyValueStore> _Nonnull)store underKey:(NSString* _Nonnull) key;

/*!
 Static initializer that reverses the asJSON process
 
 @param serialized the text representation of the VeridiumBiometricVector
 
 @return the loaded vector if the load was successful, `nil` otherwise
 */
+(instancetype _Nullable) loadJSON:(NSString* _Nonnull)serialized;

/*!
 Designated initializer
 
 @param type                   type
 @param version                version
 @param format                 format
 @param encryptedBiometricData biometric data
 @param extraData              dictionary with any extra data to be stored 
 
 @return The initialized vector
 */
-(instancetype _Nonnull)initWithType:(NSString* _Nonnull) type
                    version:(NSString* _Nonnull) version
                     format:(NSString* _Nonnull) format
              biometricData:(NSData* _Nonnull) encryptedBiometricData
                  extraData:(NSDictionary* _Nullable) extraData;

@end


/*!
 Utility class for managing split biometric vectors
 */
@interface VeridiumBiometricSplitVectors : NSObject


/*!
 Static initializer that constructs an instance from the 2 public/private vector parts

 @param publicVector  the public part
 @param privateVector the private part

 @return the constructed instance if the decryption was successful, `nil` otherwise
 */
+(VeridiumBiometricVector* _Nullable) reconstructFromPublic:(VeridiumBiometricVector* _Nonnull) publicVector andPrivate:(VeridiumBiometricVector* _Nonnull) privateVector;


/*!
 
 Static initialzer that constructs an instance from a source full vector by splitting it into a public/private pair
 
 @param fullVector the source vector

 @return the constructed instance
 */
+(instancetype _Nonnull) createBySplitting:(VeridiumBiometricVector* _Nonnull) fullVector;


/*!
 Getter for the public vector part
 */
@property (readonly, nonnull) VeridiumBiometricVector* publicVector;


/*!
 Getter for the private vector part
 */
@property (readonly, nonnull) VeridiumBiometricVector* privateVector;

@end



/*!
 Utility class for holding a collection of multiple vectors from different engines. Used by the enrollment/authentication aggregation helpers.
 */
@interface VeridiumAggregatedBiometricVector : VeridiumBiometricVector

/*!
 Adds a vector to the collection
 
 @param newVector a new vector
 */
-(void) addVector:(VeridiumBiometricVector* _Nonnull) newVector;

/*!
 Returns all vectors in the collection
 */
@property (readonly, nonnull) NSArray<VeridiumBiometricVector*>* allVectors;
/*!
 Returns all vectors in the collection serialized as an array of dictionaries (for easier serialization)
 */
@property (readonly, nonnull) NSArray<NSDictionary<NSString*,id>*>* asArrayOfDictionaries;

@end
