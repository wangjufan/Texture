//
//  ASTransactionNote.h
//  AsyncDisplayKit
//
//  Created by wangjufan on 2018/6/26.
//  Copyright © 2018年 Pinterest. All rights reserved.
//
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

/*
 事务如何实现集合化处理？
 通过 视图类别 和 层类别 的响应者链模式
 
 */


