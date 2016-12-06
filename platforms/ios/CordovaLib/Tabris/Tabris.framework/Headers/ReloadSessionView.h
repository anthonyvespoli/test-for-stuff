//
//  ReloadSessionView.h
//  Tabris
//
//  Created by Jordi Böhme López on 01.12.11.
//  Copyright (c) 2011-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SystemMenu.h"
#import "SystemMenuDelegate.h"

@interface ReloadSessionView : UIView<SystemMenu>
{
    UIView *_parentView;
    UIView *_contentView;
    UILabel *_resetLabel;
    UIButton *_resetButton;
    id <SystemMenuDelegate> __weak _delegate;
}

@property (weak, nonatomic) id <SystemMenuDelegate> delegate;

@property (weak, nonatomic, readonly) UIView *contentView;

@property (weak, nonatomic, readonly) UILabel *resetLabel;

@property (weak, nonatomic, readonly) UIButton *resetButton;

@property (nonatomic, strong) UIView *parentView;

- (UIView *)viewForView:(UIView *)view;
- (CGRect)displayFrame;
- (void)animateShow;
- (void)animateRemove;
- (void)resetSession;

-(ReloadSessionView *)initWithView:(UIView *)addToView andDelegate:(id<SystemMenuDelegate>)theDelegate;

@end
