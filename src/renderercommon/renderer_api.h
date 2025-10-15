// Common renderer API interface
#pragma once

typedef struct RendererAPI {
    void (*Init)(void);
    void (*Shutdown)(void);
    void (*RenderFrame)(void);
    void (*BackendDraw)(void);
    void (*UploadTexture)(void* data, int width, int height);
    void (*BeginScene)(void);
    void (*EndScene)(void);
} RendererAPI;
// Add Metal renderer selection for macOS
#ifdef __APPLE__
#include "../renderer_metal/renderer_metal_api.h"
#endif
