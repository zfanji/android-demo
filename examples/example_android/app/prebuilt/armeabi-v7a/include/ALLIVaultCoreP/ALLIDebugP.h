#pragma once

#include "alli_common.h"

#ifdef ALLI_WIN32
#include "win32/ALLIDebugP.h"
#else
#include "unix/ALLIDebugP.h"
#endif