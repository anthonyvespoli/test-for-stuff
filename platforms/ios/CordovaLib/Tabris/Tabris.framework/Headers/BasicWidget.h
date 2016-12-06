//
//  BasicWidget.h
//  Tabris
//
//  Created by Jordi Böhme López
//  Copyright (c) 2011-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BasicObject.h"
#import "ClientLayout.h"

@protocol LayoutNotAnimatable
@end

@protocol Widget <RemoteObject>
- (UIView *)view;
- (void)didMoveToSuperview:(UIView *)superview;
@end

@interface BasicWidget : BasicObject <Widget>
- (void)didMoveToSuperview:(UIView *)superview NS_REQUIRES_SUPER;
@property (strong) NSNumber *tabIndex;
@property (assign) CGRect bounds;
@property (strong) UIColor *background;
@property (strong) UIColor *foreground;
@property (strong) NSArray *style;
@property (strong) UIFont *font;
@property (strong) NSArray *backgroundImage;
@property (strong) NSDictionary *data;
@property (assign) BOOL enabled;
@property (assign) BOOL visibility;
@property (strong) NSDictionary *layoutData;
@property (strong) NSNumber *opacity;
@property (strong) NSDictionary *transform;
@property (strong) NSNumber *cornerRadius;
@property (strong, readonly) ClientLayout *clientLayout;
- (BOOL)hasStyle:(NSString *)value;
- (BOOL)dataForKey:(NSString *)key is:(id)expected;
- (void)applyBackgroundImage:(NSArray *)image onView:(UIView *)view;
- (NSString *)screenshot;
@end
