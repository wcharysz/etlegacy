// Main entry point for Metal renderer

#include "tr_metal_local.h"
#include <TargetConditionals.h>
#if TARGET_OS_OSX
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

extern id<MTLDevice> metalDevice;
extern id<MTLCommandQueue> metalCommandQueue;
extern CAMetalLayer *metalLayer;

void Metal_RenderFrame(void) {
    if (!metalDevice || !metalCommandQueue || !metalLayer) return;

    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    if (!drawable) return;

    MTLRenderPassDescriptor *passDesc = [MTLRenderPassDescriptor renderPassDescriptor];
    passDesc.colorAttachments[0].texture = drawable.texture;
    passDesc.colorAttachments[0].loadAction = MTLLoadActionClear;
    passDesc.colorAttachments[0].clearColor = MTLClearColorMake(0.1, 0.1, 0.2, 1.0);
    passDesc.colorAttachments[0].storeAction = MTLStoreActionStore;

    id<MTLCommandBuffer> commandBuffer = [metalCommandQueue commandBuffer];
    id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:passDesc];
    [encoder setRenderPipelineState:metalPipelineState];
    // Draw triangle (vertex shader generates positions/colors)
    [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];
    [encoder endEncoding];
    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}
#endif
