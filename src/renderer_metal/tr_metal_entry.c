// Entry point for Metal renderer integration
#include "tr_metal.h"
#include "renderer_api.h"
#include "tr_public.h"
#include <TargetConditionals.h>
#if TARGET_OS_OSX

// Metal renderer's GetRefAPI implementation
refexport_t * QDECL GetRefAPI(int apiVersion, refimport_t *rimp) {
    // TODO: Fill with actual Metal renderer logic
    // For now, return NULL or stub
    return NULL;
}

#endif
