//
//  _ASAsyncTransactionContainer.m
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

#import <AsyncDisplayKit/_ASAsyncTransactionContainer.h>
#import <AsyncDisplayKit/_ASAsyncTransactionContainer+Private.h>
#import <AsyncDisplayKit/_ASAsyncTransaction.h>
#import <AsyncDisplayKit/_ASAsyncTransactionGroup.h>

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


@implementation CALayer (ASAsyncTransactionContainer)
@dynamic asyncdisplaykit_currentAsyncTransaction;
@dynamic asyncdisplaykit_asyncTransactionContainer;

- (ASAsyncTransactionContainerState)asyncdisplaykit_asyncTransactionContainerState{
  return ([self.asyncdisplaykit_asyncLayerTransactions count] == 0) ? ASAsyncTransactionContainerStateNoTransactions : ASAsyncTransactionContainerStatePendingTransactions;
}
- (void)asyncdisplaykit_cancelAsyncTransactions{
  // If there was an open transaction, commit and clear the current transaction. Otherwise:
  // (1) The run loop observer will try to commit a canceled transaction which is not allowed
  // (2) We leave the canceled transaction attached to the layer, dooming future operations
  _ASAsyncTransaction *currentTransaction = self.asyncdisplaykit_currentAsyncTransaction;
  [currentTransaction commit];
  self.asyncdisplaykit_currentAsyncTransaction = nil;

  for (_ASAsyncTransaction *transaction in [self.asyncdisplaykit_asyncLayerTransactions copy]) {
    [transaction cancel];
  }
}
/////////////////////////////////////////////////////////////
/*// 默认行为，强引用集合中的对象，等同于NSSet
 NSHashTableStrongMemory             = 0,
 
 // 在将对象添加到集合之前，会拷贝对象
 NSHashTableCopyIn                   = NSPointerFunctionsCopyIn,
 
 // 使用移位指针(shifted pointer)来做hash检测及确定两个对象是否相等；
 // 同时使用description方法来做描述字符串
 NSHashTableObjectPointerPersonality = NSPointerFunctionsObjectPointerPersonality,
 
 // 弱引用集合中的对象，且在对象被释放后，会被正确的移除。
 NSHashTableWeakMemory               = NSPointerFunctionsWeakMemory
 
 NSHashTableStrongMemory：和NSPointerFunctionsStrongMemory相同，使用此选项为默认的行为，和NSSet的内存策略相同。
 NSHashTableWeakMemory：和NSPointerFunctionsWeakMemory相同，此选项使用weak存储对象，当对象被销毁的时候自动将其从集合中移除。
 NSHashTableCopyIn：和NSPointerFunctionsCopyIn相同，此选项在对象被加入到集合之前copy它们。
 NSHashTableObjectPointerPersonality：和NSPointerFunctionsObjectPointerPersonality相同，此选项是直接使用指针进行isEqual:和hash。
*/
- (_ASAsyncTransaction *)asyncdisplaykit_asyncTransaction{
  _ASAsyncTransaction *transaction = self.asyncdisplaykit_currentAsyncTransaction;
  
  if (transaction == nil) {
    NSHashTable *transactions = self.asyncdisplaykit_asyncLayerTransactions;
    if (transactions == nil) {
      transactions = [NSHashTable hashTableWithOptions:NSHashTableObjectPointerPersonality];
      self.asyncdisplaykit_asyncLayerTransactions = transactions;
    }
    
    __weak CALayer *weakSelf = self;
    transaction = [[_ASAsyncTransaction alloc] initWithCompletionBlock:^(_ASAsyncTransaction *completedTransaction, BOOL cancelled) {
      __strong CALayer *self = weakSelf;
      if (self == nil) {
        return;
      }
      [transactions removeObject:completedTransaction];
      [self asyncdisplaykit_asyncTransactionContainerDidCompleteTransaction:completedTransaction];
    }];
    
    [transactions addObject:transaction];
    self.asyncdisplaykit_currentAsyncTransaction = transaction;
    [self asyncdisplaykit_asyncTransactionContainerWillBeginTransaction:transaction];
  }
  
  [_ASAsyncTransactionGroup.mainTransactionGroup addTransactionContainer:self];
  return transaction;
}
- (CALayer *)asyncdisplaykit_parentTransactionContainer
{
  CALayer *containerLayer = self;
  while (containerLayer && !containerLayer.asyncdisplaykit_isAsyncTransactionContainer) {
    containerLayer = containerLayer.superlayer;
  }
  return containerLayer;
}
@end

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
@implementation UIView (ASAsyncTransactionContainer)

- (BOOL)asyncdisplaykit_isAsyncTransactionContainer
{
  return self.layer.asyncdisplaykit_isAsyncTransactionContainer;
}
- (void)asyncdisplaykit_setAsyncTransactionContainer:(BOOL)asyncTransactionContainer
{
  self.layer.asyncdisplaykit_asyncTransactionContainer = asyncTransactionContainer;
}
- (ASAsyncTransactionContainerState)asyncdisplaykit_asyncTransactionContainerState
{
  return self.layer.asyncdisplaykit_asyncTransactionContainerState;
}
- (void)asyncdisplaykit_cancelAsyncTransactions
{
  [self.layer asyncdisplaykit_cancelAsyncTransactions];
}

- (void)asyncdisplaykit_asyncTransactionContainerStateDidChange
{
  // No-op in the base class.
}
- (void)asyncdisplaykit_setCurrentAsyncTransaction:(_ASAsyncTransaction *)transaction{
  self.layer.asyncdisplaykit_currentAsyncTransaction = transaction;
}
- (_ASAsyncTransaction *)asyncdisplaykit_currentAsyncTransaction{
  return self.layer.asyncdisplaykit_currentAsyncTransaction;
}

@end

