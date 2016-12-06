//
//  SystemMenuDelegate.h
//  Tabris
//
//  Created by Jordi Böhme López on 19.03.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SystemMenuDelegate <NSObject>
- (void)loadEntryPoint:(NSString *)entrypoint;
- (void)reloadSession;
- (void)systemMenuCanceled;
- (void)systemMenuReopen;
- (NSURL *)serverURL;
@end
