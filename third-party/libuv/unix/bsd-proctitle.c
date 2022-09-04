
#include "uv.h"
#include "internal.h"

#include <sys/types.h>
#include <unistd.h>
static uv_mutex_t process_title_mutex;static uv_once_t process_title_mutex_once = UV_ONCE_INIT;static char* process_title;static void init_process_title_mutex_once(void) { if (uv_mutex_init(&process_title_mutex)) abort();}void uv__process_title_cleanup(void) { uv_once(&process_title_mutex_once, init_process_title_mutex_once); uv_mutex_destroy(&process_title_mutex);}char** uv_setup_args(int argc, char** argv) { process_title = argc > 0 ? uv__strdup(argv[0]) : NULL; return argv;}int uv_set_process_title(const char* title) { char* new_title; new_title = uv__strdup(title); if (new_title == NULL) return UV_ENOMEM; uv_once(&process_title_mutex_once, init_process_title_mutex_once); uv_mutex_lock(&process_title_mutex); uv__free(process_title); process_title = new_title; setproctitle("%s", title); uv_mutex_unlock(&process_title_mutex); return 0;}int uv_get_process_title(char* buffer, size_t size) { size_t len; if (buffer == NULL || size == 0) return UV_EINVAL; uv_once(&process_title_mutex_once, init_process_title_mutex_once); uv_mutex_lock(&process_title_mutex); if (process_title != NULL) { len = strlen(process_title) + 1; if (size < len) { uv_mutex_unlock(&process_title_mutex); return UV_ENOBUFS; } memcpy(buffer, process_title, len); } else { len = 0; } uv_mutex_unlock(&process_title_mutex); buffer[len] = '\0'; return 0;}