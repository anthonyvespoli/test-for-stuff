//
//  ClientLayout.h
//  Tabris
//
//  Created by Jordi Böhme López on 13.05.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DelegatingView.h"

@class TabrisClient;

@interface ClientLayout : NSObject
+ (instancetype)newAbsoluteLayoutWithView:(UIView *)view data:(NSDictionary *)data andClient:(TabrisClient *)client;
+ (instancetype)newRelativeLayoutWithView:(UIView *)view data:(NSDictionary *)data andClient:(TabrisClient *)client;
- (void)layout;
- (void)dispose;
@property (nonatomic, weak, readonly) TabrisClient *client;
@property (nonatomic, weak, readonly) UIView *view;
@property (nonatomic, strong, readonly) NSDictionary *data;
@property (assign, getter = isAnimated) BOOL animated;
@end
