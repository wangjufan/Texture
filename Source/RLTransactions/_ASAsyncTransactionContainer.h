//
//  _ASAsyncTransactionContainer.h
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

#pragma once

#improt "ASAsyncTransactionContainer.h"

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

@interface CALayer (ASAsyncTransactionContainer) <ASAsyncTransactionContainer>
/**当前层的事务  与协议重复内容
 @summary Returns the current async transaction for this layer.
 A new transaction is created if one did not already exist.
 This method will always return an open, uncommitted transaction.
 
 @desc asyncdisplaykit_asyncTransactionContainer does not need to be YES
    for this to return a transaction. Defaults to nil.
 */
@property (nullable, nonatomic, readonly) _ASAsyncTransaction *asyncdisplaykit_asyncTransaction;

/**寻找第一个事务容器， 自己 - 父类 ---
 @summary Goes up the superlayer chain until it finds the first layer with asyncdisplaykit_asyncTransactionContainer=YES (including the receiver) and returns it.
 Returns nil if no parent container is found.
 */
@property (nullable, nonatomic, readonly) CALayer *asyncdisplaykit_parentTransactionContainer;
/**自己是否容器
 @summary Whether or not this layer should serve as a transaction container.
 Defaults to NO.
 */
@property (nonatomic, getter=asyncdisplaykit_isAsyncTransactionContainer, setter = asyncdisplaykit_setAsyncTransactionContainer:) BOOL asyncdisplaykit_asyncTransactionContainer;
@end
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
@interface UIView (ASAsyncTransactionContainer) <ASAsyncTransactionContainer>
@end

NS_ASSUME_NONNULL_END

