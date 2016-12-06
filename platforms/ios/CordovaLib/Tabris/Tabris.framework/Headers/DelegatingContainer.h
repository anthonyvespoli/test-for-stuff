//
//  DelegatingContainer.h
//  Tabris
//
//  Created by Jochen Krause on 26.02.16.
//  Copyright © 2016 EclipseSource. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DelegatingView.h"

@protocol DelegatingContainer <NSObject>
@optional
- (CGSize)intrinsicContentSize;
- (void)sizeChanged:(CGSize)newSize;
@end

@interface DelegatingContainer : UIView
@property (weak) id<ViewDelegate> delegate;
@property BOOL isHeightRequested;
@property BOOL isWidthRequested;
- (void)parentRequestsHeight;
- (void)parentRequestsWidth;
- (void)contentUpdated:(BOOL)needsPropagation;
- (void)setLayoutDefined:(BOOL)defined;
@end
