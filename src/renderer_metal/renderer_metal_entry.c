// Entry point for Metal renderer integration
#include "tr_metal.h"
#include <TargetConditionals.h>
#if TARGET_OS_OSX

// Example: Engine calls this to get Metal renderer API
void* GetMetalRendererAPI(void) {
    // Return pointer to Metal renderer interface struct
    return NULL; // TODO: Fill with actual API struct
}

#endif
