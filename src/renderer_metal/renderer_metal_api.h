// Header for Metal renderer API struct
#pragma once

#include "renderer_api.h"

#ifdef __APPLE__
extern RendererAPI metalRendererAPI;
void* GetMetalRendererAPI(void);
#endif
