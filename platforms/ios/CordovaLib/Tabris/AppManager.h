//
//  AppManager.h
//  Tabris
//
//  Created by Jordi Böhme López on 06.11.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Tabris/BasicObject.h>

@interface AppManager : BasicObject<ServiceObject>
- (void)home:(NSDictionary *)properties;
@property (strong) NSString *current;
@end
