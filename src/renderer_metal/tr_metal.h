// Public API for Metal renderer
#pragma once

#ifdef __APPLE__
void Metal_InitRenderer(void);
void Metal_ShutdownRenderer(void);
void Metal_RenderFrame(void);
void Metal_BackendDraw(void);
void Metal_UploadTexture(void* data, int width, int height);
void Metal_BeginScene(void);
void Metal_EndScene(void);
#endif
