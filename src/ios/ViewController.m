//
//  ViewController.m
//  AdmiralVsAsteroids
//
//  Created by Alexander Kuznietsov on 1/22/14.
//  Copyright (c) 2014 Alexander Kuznietsov. All rights reserved.
//

#import "ViewController.h"
#import "GameDelegate.h"

@interface ViewController () {
    GameDelegate* gameDelegate;
}
@property (strong, nonatomic) EAGLContext *context;

- (void)tearDownGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.view.multipleTouchEnabled = YES;
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    gameDelegate = new GameDelegate;
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    delete gameDelegate;
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        delete gameDelegate;
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];

    gameDelegate->init(self.view.bounds.size.height, self.view.bounds.size.width);
    
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    gameDelegate->update(self.timeSinceLastUpdate * 1000);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.0, 0.2, 0.0, 1.0);
    gameDelegate->render();
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *aTouch in touches)
    {
        CGPoint loc = [aTouch locationInView:self.view];
        gameDelegate->onTouchPressed(loc.x, loc.y);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *aTouch in touches)
    {
        CGPoint loc = [aTouch locationInView:self.view];
        CGPoint prevloc = [aTouch previousLocationInView:self.view];
        gameDelegate->onTouchMoved(loc.x, loc.y, prevloc.x, prevloc.y);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *aTouch in touches)
    {
        CGPoint loc = [aTouch locationInView:self.view];
        CGPoint prevloc = [aTouch previousLocationInView:self.view];
        gameDelegate->onTouchReleased(loc.x, loc.y, prevloc.x, prevloc.y);
    }
}
@end

