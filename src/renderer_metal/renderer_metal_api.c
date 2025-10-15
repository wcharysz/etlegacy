// Implementation of Metal renderer API struct
#include "renderer_api.h"
#include "tr_metal.h"

static RendererAPI metalRendererAPI = {
    Metal_InitRenderer,
    Metal_ShutdownRenderer,
    Metal_RenderFrame,
    Metal_BackendDraw,
    Metal_UploadTexture,
    Metal_BeginScene,
    Metal_EndScene
};

void* GetMetalRendererAPI(void) {
    return &metalRendererAPI;
}
