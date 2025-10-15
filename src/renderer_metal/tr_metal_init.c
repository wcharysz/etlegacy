#import <Foundation/Foundation.h>
static id<MTLRenderPipelineState> metalPipelineState = nil;
static id<MTLBuffer> metalVertexBuffer = nil;
    // Load Metal shader library
    NSError *error = nil;
    NSString *shaderSrc = @"using namespace metal;\n"
        "struct Vertex { float4 position [[position]]; float4 color; };\n"
        "vertex Vertex vertex_main(uint vertexID [[vertex_id]]) {\n"
        "    float4 positions[3] = { float4(0.0, 0.5, 0, 1), float4(-0.5, -0.5, 0, 1), float4(0.5, -0.5, 0, 1) };\n"
        "    float4 colors[3] = { float4(1,0,0,1), float4(0,1,0,1), float4(0,0,1,1) };\n"
        "    Vertex v; v.position = positions[vertexID]; v.color = colors[vertexID]; return v;\n"
        "}\n"
        "fragment float4 fragment_main(Vertex in [[stage_in]]) { return in.color; }\n";
    id<MTLLibrary> library = [metalDevice newLibraryWithSource:shaderSrc options:nil error:&error];
    if (!library) {
        printf("Metal: Shader library error: %s\n", [[error localizedDescription] UTF8String]);
        return;
    }
    id<MTLFunction> vertexFunc = [library newFunctionWithName:@"vertex_main"];
    id<MTLFunction> fragmentFunc = [library newFunctionWithName:@"fragment_main"];
    if (!vertexFunc || !fragmentFunc) {
        printf("Metal: Failed to get shader functions\n");
        return;
    }
    MTLRenderPipelineDescriptor *pipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDesc.vertexFunction = vertexFunc;
    pipelineDesc.fragmentFunction = fragmentFunc;
    pipelineDesc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalPipelineState = [metalDevice newRenderPipelineStateWithDescriptor:pipelineDesc error:&error];
    if (!metalPipelineState) {
        printf("Metal: Pipeline error: %s\n", [[error localizedDescription] UTF8String]);
        return;
    }
    // Vertex buffer for triangle (not strictly needed, but stub for future use)
    float vertexData[3 * 4] = { 0.0, 0.5, 0, 1, -0.5, -0.5, 0, 1, 0.5, -0.5, 0, 1 };
    metalVertexBuffer = [metalDevice newBufferWithBytes:vertexData length:sizeof(vertexData) options:MTLResourceStorageModeShared];
    metalPipelineState = nil;
    metalVertexBuffer = nil;
// Metal renderer initialization and teardown for macOS

#include "tr_metal_local.h"
#include <TargetConditionals.h>
#if TARGET_OS_OSX
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

static id<MTLDevice> metalDevice = nil;
static id<MTLCommandQueue> metalCommandQueue = nil;
static CAMetalLayer *metalLayer = nil;

void Metal_InitRenderer(void) {
    metalDevice = MTLCreateSystemDefaultDevice();
    if (!metalDevice) {
        printf("Metal: Failed to create device\n");
        return;
    }
    metalCommandQueue = [metalDevice newCommandQueue];
    if (!metalCommandQueue) {
        printf("Metal: Failed to create command queue\n");
        return;
    }
    // Create Metal layer (in real app, attach to window/view)
    metalLayer = [CAMetalLayer layer];
    metalLayer.device = metalDevice;
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.framebufferOnly = YES;
    printf("Metal: Initialized\n");
}

void Metal_ShutdownRenderer(void) {
    metalCommandQueue = nil;
    metalDevice = nil;
    metalLayer = nil;
    printf("Metal: Shutdown\n");
}
#endif
