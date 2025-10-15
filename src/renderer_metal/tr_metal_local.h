#ifdef __APPLE__
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
extern id<MTLDevice> metalDevice;
extern id<MTLCommandQueue> metalCommandQueue;
extern CAMetalLayer *metalLayer;
extern id<MTLRenderPipelineState> metalPipelineState;
extern id<MTLBuffer> metalVertexBuffer;
#endif
// Local header for Metal renderer
#pragma once


// Metal global objects
#ifdef __APPLE__
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
extern id<MTLDevice> metalDevice;
extern id<MTLCommandQueue> metalCommandQueue;
extern CAMetalLayer *metalLayer;
#endif

void Metal_InitRenderer(void);
void Metal_ShutdownRenderer(void);
