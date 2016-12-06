//
//  TabrisApplication.m
//  TabrisJS
//
//  Created by Patryk Mol on 15/09/16.
//
//

#import "TabrisApplication.h"

@interface TabrisApplication ()
@property (strong) NSMutableArray *timers;
@property (strong) NSTimer *timer;
@property (assign) NSTimeInterval lastEventTime;
@end

@implementation TabrisApplication

- (instancetype)init {
    self = [super init];
    if (self) {
        self.timers = [NSMutableArray new];
        NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
        [center addObserver:self selector:@selector(addInactivityTimer:) name:@"TabrisNewInactivityTimerNotification" object:nil];
        [center addObserver:self selector:@selector(cancelInactivityTimer:) name:@"TabrisCancelInactivityTimerNotification" object:nil];
    }
    return self;
}

- (void)sendEvent:(UIEvent *)event {
    [super sendEvent:event];
    if (!self.timer) {
        return;
    }
    NSSet *allTouches = [event allTouches];
    if ([allTouches count] > 0) {
        UITouchPhase phase = ((UITouch *)[allTouches anyObject]).phase;
        if (phase == UITouchPhaseBegan) {
            self.lastEventTime = [[NSDate date] timeIntervalSince1970];
        }
    }
}

- (void)addInactivityTimer:(NSNotification *)notification {
    NSMutableDictionary *timerDict = [notification.userInfo mutableCopy];
    [self.timers addObject:timerDict];
    [self startTimer];
}

- (void)cancelInactivityTimer:(NSNotification *)notification {
    [self removeInactivityTimer:[notification.userInfo objectForKey:@"objectId"]];
}

- (void)removeInactivityTimer:(NSString *)objectId {
    NSString *timerId = nil;
    NSMutableDictionary *timerToRemove;
    for (NSMutableDictionary *timerDict in self.timers) {
        timerId = [timerDict objectForKey:@"objectId"];
        if ([timerId isEqualToString:objectId]) {
            timerToRemove = timerDict;
            break;
        }
    }
    [self.timers removeObject:timerToRemove];
    [timerToRemove removeAllObjects];
    [self stopTimer];
}

- (void)checkTimers:(NSTimer *)timer {
    for (NSMutableDictionary *timerDict in [self.timers copy]) {
        NSTimeInterval currentTime = [[NSDate date] timeIntervalSince1970];
        NSTimeInterval timeToFire = self.lastEventTime + [[timerDict objectForKey:@"interval"] doubleValue]/1000.f;
        if (currentTime >= timeToFire) {
            [self fireTimerWithId:[timerDict objectForKey:@"objectId"]];
        }
    }
}

- (void)fireTimerWithId:(NSString *)objectId {
    [[NSNotificationCenter defaultCenter] postNotificationName:[NSString stringWithFormat:@"InactivityTimerFired%@", objectId] object:nil];
    [self removeInactivityTimer:objectId];
}

- (void)startTimer {
    if (self.timer) {
        return;
    }
    self.timer = [NSTimer scheduledTimerWithTimeInterval:1.f target:self selector:@selector(checkTimers:) userInfo:nil repeats:YES];
    self.lastEventTime = [[NSDate date] timeIntervalSince1970];
}

- (void)stopTimer {
    if ([self.timers count] > 0) {
        return;
    }
    [self.timer invalidate];
    self.timer = nil;
}

@end
