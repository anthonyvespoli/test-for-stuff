//
//  DelegatingView.h
//  Tabris
//
//  Created by Jordi Böhme López on 15.05.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ViewDelegate <NSObject>
@optional
- (CGSize)intrinsicContentSize;
- (void)sizeChanged:(CGSize)newSize;
- (void)updateConstraints;
- (UIView *)viewForBaselineLayout;
- (BOOL)touchStarted:(NSSet *)touches;
- (BOOL)touchMoved:(NSSet *)touches;
- (BOOL)touchEnded:(NSSet *)touches;
- (void)gestureRecognizerChanged;
@end

@interface DelegatingView : UIView
@property (weak) id<ViewDelegate> delegate;
@end
