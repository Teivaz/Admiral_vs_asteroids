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

    gameDelegate->init(self.view.bounds.size.width, self.view.bounds.size.height);
    
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
    gameDelegate->render();
}
@end

