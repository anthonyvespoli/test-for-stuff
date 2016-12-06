//
//  EntrypointView.h
//  Tabris
//
//  Created by Jordi Böhme López on 16.03.12.
//  Copyright (c) 2011-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TabrisClient.h"
#import "SystemMenu.h"
#import "SystemMenuDelegate.h"

@interface EntrypointView : UIView<SystemMenu,UIAlertViewDelegate>

@property (weak, nonatomic) id <SystemMenuDelegate> delegate;
@property (strong, nonatomic, readonly) UIView *contentView;
@property (strong, nonatomic, readonly) UIScrollView *listView;
@property (strong, nonatomic) UIView *parentView;

- (EntrypointView *)initWithView:(UIView *)addToView andDelegate:(id<SystemMenuDelegate>)theDelegate;
- (UIView *)viewForView:(UIView *)view;
- (CGRect)displayFrame;
- (void)animateShow;
- (void)animateRemove;

@end
