  
#include "uv.h"

#define UV_STRINGIFY(v) UV_STRINGIFY_HELPER(v)
#define UV_STRINGIFY_HELPER(v) #v

#define UV_VERSION_STRING_BASE UV_STRINGIFY(UV_VERSION_MAJOR) "." UV_STRINGIFY(UV_VERSION_MINOR) "." UV_STRINGIFY(UV_VERSION_PATCH)
 
#if UV_VERSION_IS_RELEASE
# define UV_VERSION_STRING UV_VERSION_STRING_BASE
#else
# define UV_VERSION_STRING UV_VERSION_STRING_BASE "-" UV_VERSION_SUFFIX
#endif
 unsigned int uv_version(void) { return UV_VERSION_HEX; }  const char* uv_version_string(void) { return UV_VERSION_STRING; } 