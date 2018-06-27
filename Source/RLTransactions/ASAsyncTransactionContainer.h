//
//  ASAsyncTransactionContainer.h
//  AsyncDisplayKit
//
//  Created by wangjufan on 2018/6/26.
//  Copyright © 2018年 Pinterest. All rights reserved.
//

#ifndef ASAsyncTransactionContainer_h
#define ASAsyncTransactionContainer_h


@class _ASAsyncTransaction;
typedef NS_ENUM(NSUInteger, ASAsyncTransactionContainerState) {
  /** 一次提交的事务集合
   The async container has no outstanding transactions. Whatever it is displaying is up-to-date.
   */
  ASAsyncTransactionContainerStateNoTransactions = 0,
  /**
   The async container has one or more outstanding async transactions.
   Its contents may be out of date or showing a placeholder, depending on the configuration of the contained ASDisplayLayers.
   */
  ASAsyncTransactionContainerStatePendingTransactions,
};

@protocol ASAsyncTransactionContainer
/**是否是容器
 @summary If YES, the receiver is marked as a container for async transactions,
 grouping all of the transactions in the container hierarchy
 below the receiver together in a single ASAsyncTransaction.
 @default NO
 */
@property (nonatomic, getter=asyncdisplaykit_isAsyncTransactionContainer, setter=asyncdisplaykit_setAsyncTransactionContainer:) BOOL asyncdisplaykit_asyncTransactionContainer;
/**容器状态
 @summary The current state of the receiver;
 indicates if it is currently performing asynchronous operations
 or if all operations have finished/canceled.
 */
@property (nonatomic, readonly) ASAsyncTransactionContainerState asyncdisplaykit_asyncTransactionContainerState;
/**取消容器内的所有事务
 @summary Cancels all async transactions on the receiver.
 */
- (void)asyncdisplaykit_cancelAsyncTransactions;

//当前事务
@property (nullable, nonatomic, setter=asyncdisplaykit_setCurrentAsyncTransaction:) _ASAsyncTransaction *asyncdisplaykit_currentAsyncTransaction;
@end


#endif /* ASAsyncTransactionContainer_h */
