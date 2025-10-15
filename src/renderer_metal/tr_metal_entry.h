// Header for Metal renderer entry point
#pragma once

#ifdef __APPLE__
#include "tr_public.h"
refexport_t * QDECL GetRefAPI(int apiVersion, refimport_t *rimp);
#endif
