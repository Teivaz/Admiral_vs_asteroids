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

    int width = self.view.frame.size.width;
    int height = self.view.frame.size.height;
    float scale = self.view.contentScaleFactor;
    gameDelegate->init(height*scale, width*scale);
    
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
        float scale = self.view.contentScaleFactor;
        int height = self.view.frame.size.height;
        int width = self.view.frame.size.width;
        gameDelegate->onTouchPressed((height - loc.y) * scale,
                                     (width - loc.x) * scale);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *aTouch in touches)
    {
        CGPoint loc = [aTouch locationInView:self.view];
        CGPoint prevloc = [aTouch previousLocationInView:self.view];
        float scale = self.view.contentScaleFactor;
        int height = self.view.frame.size.height;
        int width = self.view.frame.size.width;
        gameDelegate->onTouchMoved((height - loc.y) * scale,
                                   (width - loc.x) * scale,
                                   (height - prevloc.y) * scale,
                                   (width - prevloc.x) * scale);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *aTouch in touches)
    {
        CGPoint loc = [aTouch locationInView:self.view];
        CGPoint prevloc = [aTouch previousLocationInView:self.view];
        float scale = self.view.contentScaleFactor;
        int height = self.view.frame.size.height;
        int width = self.view.frame.size.width;
        gameDelegate->onTouchReleased((height - loc.y) * scale,
                                      (width - loc.x) * scale,
                                      (height - prevloc.y) * scale,
                                      (width - prevloc.x) * scale);
    }
}
@end

