// Scene management for Metal renderer
#include "tr_metal_local.h"
#include <TargetConditionals.h>
#if TARGET_OS_OSX

void Metal_BeginScene(void) {
    // Setup Metal scene
}

void Metal_EndScene(void) {
    // Present Metal drawable
}

#endif
