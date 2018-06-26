//
//  _ASAsyncTransactionGroup.h
//  Texture
//
//  Copyright (c) 2014-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the /ASDK-Licenses directory of this source tree. An additional
//  grant of patent rights can be found in the PATENTS file in the same directory.
//
//  Modifications to this file made after 4/13/2017 are: Copyright (c) 2017-present,
//  Pinterest, Inc.  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//

#import <Foundation/Foundation.h>
#import <AsyncDisplayKit/ASBaseDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ASAsyncTransactionContainer;

/// A group of transaction containers,
//  for which the current transactions are committed together at the end of the next runloop tick.
AS_SUBCLASSING_RESTRICTED
@interface _ASAsyncTransactionGroup : NSObject

/// The main transaction group is scheduled to commit on every tick of the main runloop.
/// Access from the main thread only.
@property (class, nonatomic, readonly) _ASAsyncTransactionGroup *mainTransactionGroup;

- (void)commit;
/// Add a transaction container to be committed.
- (void)addTransactionContainer:(id<ASAsyncTransactionContainer>)container;

/// Use the main group.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

/*
 The key point of it is to make full use of the system resources .
 This take two the fatal problems to it :
 First , when fast scrolling even blank cells  can drop down 60 fps ;
 Second , many resources, especially the battery  were wasted .
 
 In my opinion, it is only useful
 when scrolling speed is fast enough that the CPU or GPU cause fps drop ,
 and scrolling speed is slow than the  blank cell's ultimate 60 fps scrolling speed .
 
 So,  work done in Texture is not well pay off .
 we can use cell with placeholder layer and task scheduling technology
 to gain larger scope of better fps .
 Good implementation ,  bad plan !
 */



