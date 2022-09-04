
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR)
#include <crtdbg.h>
#endif

#include "uv.h"
#include "internal.h"
#include "queue.h"
#include "handle-inl.h"
#include "heap-inl.h"
#include "req-inl.h"
static uv_once_t uv_init_guard_ = UV_ONCE_INIT;
#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
UV_THREAD_LOCAL int uv__crt_assert_enabled = TRUE;static int uv__crt_dbg_report_handler(int report_type, char *message, int *ret_val) { if (uv__crt_assert_enabled || report_type != _CRT_ASSERT) return FALSE; if (ret_val) { if(IsDebuggerPresent()) *ret_val = 1; else *ret_val = 0; } return TRUE;}
#else
UV_THREAD_LOCAL int uv__crt_assert_enabled = FALSE;
#endif

#if !defined(__MINGW32__) || __MSVCRT_VERSION__ >= 0x800
static void uv__crt_invalid_parameter_handler(const wchar_t* expression, const wchar_t* function, const wchar_t * file, unsigned int line, uintptr_t reserved) { }
#endif
static uv_loop_t** uv__loops;static int uv__loops_size;static int uv__loops_capacity;
#define UV__LOOPS_CHUNK_SIZE 8
static uv_mutex_t uv__loops_lock;static void uv__loops_init(void) { uv_mutex_init(&uv__loops_lock);}static int uv__loops_add(uv_loop_t* loop) { uv_loop_t** new_loops; int new_capacity, i; uv_mutex_lock(&uv__loops_lock); if (uv__loops_size == uv__loops_capacity) { new_capacity = uv__loops_capacity + UV__LOOPS_CHUNK_SIZE; new_loops = uv__realloc(uv__loops, sizeof(uv_loop_t*) * new_capacity); if (!new_loops) goto failed_loops_realloc; uv__loops = new_loops; for (i = uv__loops_capacity; i < new_capacity; ++i) uv__loops[i] = NULL; uv__loops_capacity = new_capacity; } uv__loops[uv__loops_size] = loop; ++uv__loops_size; uv_mutex_unlock(&uv__loops_lock); return 0;failed_loops_realloc: uv_mutex_unlock(&uv__loops_lock); return ERROR_OUTOFMEMORY;}static void uv__loops_remove(uv_loop_t* loop) { int loop_index; int smaller_capacity; uv_loop_t** new_loops; uv_mutex_lock(&uv__loops_lock); for (loop_index = 0; loop_index < uv__loops_size; ++loop_index) { if (uv__loops[loop_index] == loop) break; } if (loop_index == uv__loops_size) goto loop_removed; uv__loops[loop_index] = uv__loops[uv__loops_size - 1]; uv__loops[uv__loops_size - 1] = NULL; --uv__loops_size; if (uv__loops_size == 0) { uv__loops_capacity = 0; uv__free(uv__loops); uv__loops = NULL; goto loop_removed; } if (uv__loops_capacity < 4 * UV__LOOPS_CHUNK_SIZE) goto loop_removed; smaller_capacity = uv__loops_capacity / 2; if (uv__loops_size >= smaller_capacity) goto loop_removed; new_loops = uv__realloc(uv__loops, sizeof(uv_loop_t*) * smaller_capacity); if (!new_loops) goto loop_removed; uv__loops = new_loops; uv__loops_capacity = smaller_capacity;loop_removed: uv_mutex_unlock(&uv__loops_lock);}void uv__wake_all_loops(void) { int i; uv_loop_t* loop; uv_mutex_lock(&uv__loops_lock); for (i = 0; i < uv__loops_size; ++i) { loop = uv__loops[i]; assert(loop); if (loop->iocp != INVALID_HANDLE_VALUE) PostQueuedCompletionStatus(loop->iocp, 0, 0, NULL); } uv_mutex_unlock(&uv__loops_lock);}static void uv__init(void) { SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX); 
#if !defined(__MINGW32__) || __MSVCRT_VERSION__ >= 0x800
 _set_invalid_parameter_handler(uv__crt_invalid_parameter_handler);
#endif
 
#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
 _CrtSetReportHook(uv__crt_dbg_report_handler);
#endif
 uv__loops_init(); uv__winapi_init(); uv__winsock_init(); uv__fs_init(); uv__signals_init(); uv__console_init(); uv__util_init(); uv__init_detect_system_wakeup();}int uv_loop_init(uv_loop_t* loop) { uv__loop_internal_fields_t* lfields; struct heap* timer_heap; int err; uv__once_init(); loop->iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1); if (loop->iocp == NULL) return uv_translate_sys_error(GetLastError()); lfields = (uv__loop_internal_fields_t*) uv__calloc(1, sizeof(*lfields)); if (lfields == NULL) return UV_ENOMEM; loop->internal_fields = lfields; err = uv_mutex_init(&lfields->loop_metrics.lock); if (err) goto fail_metrics_mutex_init; loop->time = 0; uv_update_time(loop); QUEUE_INIT(&loop->wq); QUEUE_INIT(&loop->handle_queue); loop->active_reqs.count = 0; loop->active_handles = 0; loop->pending_reqs_tail = NULL; loop->endgame_handles = NULL; loop->timer_heap = timer_heap = uv__malloc(sizeof(*timer_heap)); if (timer_heap == NULL) { err = UV_ENOMEM; goto fail_timers_alloc; } heap_init(timer_heap); loop->check_handles = NULL; loop->prepare_handles = NULL; loop->idle_handles = NULL; loop->next_prepare_handle = NULL; loop->next_check_handle = NULL; loop->next_idle_handle = NULL; memset(&loop->poll_peer_sockets, 0, sizeof loop->poll_peer_sockets); loop->active_tcp_streams = 0; loop->active_udp_streams = 0; loop->timer_counter = 0; loop->stop_flag = 0; err = uv_mutex_init(&loop->wq_mutex); if (err) goto fail_mutex_init; err = uv_async_init(loop, &loop->wq_async, uv__work_done); if (err) goto fail_async_init; uv__handle_unref(&loop->wq_async); loop->wq_async.flags |= UV_HANDLE_INTERNAL; err = uv__loops_add(loop); if (err) goto fail_async_init; return 0;fail_async_init: uv_mutex_destroy(&loop->wq_mutex);fail_mutex_init: uv__free(timer_heap); loop->timer_heap = NULL;fail_timers_alloc: uv_mutex_destroy(&lfields->loop_metrics.lock);fail_metrics_mutex_init: uv__free(lfields); loop->internal_fields = NULL; CloseHandle(loop->iocp); loop->iocp = INVALID_HANDLE_VALUE; return err;}void uv_update_time(uv_loop_t* loop) { uint64_t new_time = uv__hrtime(1000); assert(new_time >= loop->time); loop->time = new_time;}void uv__once_init(void) { uv_once(&uv_init_guard_, uv__init);}void uv__loop_close(uv_loop_t* loop) { uv__loop_internal_fields_t* lfields; size_t i; uv__loops_remove(loop);  loop->wq_async.async_sent = 0; loop->wq_async.close_cb = NULL; uv__handle_closing(&loop->wq_async); uv__handle_close(&loop->wq_async); for (i = 0; i < ARRAY_SIZE(loop->poll_peer_sockets); ++i) { SOCKET sock = loop->poll_peer_sockets[i]; if (sock != 0 && sock != INVALID_SOCKET) closesocket(sock); } uv_mutex_lock(&loop->wq_mutex); assert(QUEUE_EMPTY(&loop->wq) && "thread pool work queue not empty!"); assert(!uv__has_active_reqs(loop)); uv_mutex_unlock(&loop->wq_mutex); uv_mutex_destroy(&loop->wq_mutex); uv__free(loop->timer_heap); loop->timer_heap = NULL; lfields = uv__get_internal_fields(loop); uv_mutex_destroy(&lfields->loop_metrics.lock); uv__free(lfields); loop->internal_fields = NULL; CloseHandle(loop->iocp);}int uv__loop_configure(uv_loop_t* loop, uv_loop_option option, va_list ap) { uv__loop_internal_fields_t* lfields; lfields = uv__get_internal_fields(loop); if (option == UV_METRICS_IDLE_TIME) { lfields->flags |= UV_METRICS_IDLE_TIME; return 0; } return UV_ENOSYS;}int uv_backend_fd(const uv_loop_t* loop) { return -1;}int uv_loop_fork(uv_loop_t* loop) { return UV_ENOSYS;}static int uv__loop_alive(const uv_loop_t* loop) { return uv__has_active_handles(loop) || uv__has_active_reqs(loop) || loop->pending_reqs_tail != NULL || loop->endgame_handles != NULL;}int uv_loop_alive(const uv_loop_t* loop) { return uv__loop_alive(loop);}int uv_backend_timeout(const uv_loop_t* loop) { if (loop->stop_flag == 0 && (uv__has_active_handles(loop) || uv__has_active_reqs(loop)) && loop->pending_reqs_tail == NULL && loop->idle_handles == NULL && loop->endgame_handles == NULL) return uv__next_timeout(loop); return 0;}static void uv__poll_wine(uv_loop_t* loop, DWORD timeout) { DWORD bytes; ULONG_PTR key; OVERLAPPED* overlapped; uv_req_t* req; int repeat; uint64_t timeout_time; uint64_t user_timeout; int reset_timeout; timeout_time = loop->time + timeout; if (uv__get_internal_fields(loop)->flags & UV_METRICS_IDLE_TIME) { reset_timeout = 1; user_timeout = timeout; timeout = 0; } else { reset_timeout = 0; } for (repeat = 0; ; ++repeat) { if (timeout != 0) uv__metrics_set_provider_entry_time(loop); GetQueuedCompletionStatus(loop->iocp, &bytes, &key, &overlapped, timeout); if (reset_timeout != 0) { timeout = user_timeout; reset_timeout = 0; } uv__metrics_update_idle_time(loop); if (overlapped) { req = uv__overlapped_to_req(overlapped); uv__insert_pending_req(loop, req); uv_update_time(loop); } else if (GetLastError() != WAIT_TIMEOUT) { uv_fatal_error(GetLastError(), "GetQueuedCompletionStatus"); } else if (timeout > 0) { uv_update_time(loop); if (timeout_time > loop->time) { timeout = (DWORD)(timeout_time - loop->time); timeout += repeat ? (1 << (repeat - 1)) : 0; continue; } } break; }}static void uv__poll(uv_loop_t* loop, DWORD timeout) { BOOL success; uv_req_t* req; OVERLAPPED_ENTRY overlappeds[128]; ULONG count; ULONG i; int repeat; uint64_t timeout_time; uint64_t user_timeout; int reset_timeout; timeout_time = loop->time + timeout; if (uv__get_internal_fields(loop)->flags & UV_METRICS_IDLE_TIME) { reset_timeout = 1; user_timeout = timeout; timeout = 0; } else { reset_timeout = 0; } for (repeat = 0; ; ++repeat) { if (timeout != 0) uv__metrics_set_provider_entry_time(loop); success = pGetQueuedCompletionStatusEx(loop->iocp, overlappeds, ARRAY_SIZE(overlappeds), &count, timeout, FALSE); if (reset_timeout != 0) { timeout = user_timeout; reset_timeout = 0; } uv__metrics_update_idle_time(loop); if (success) { for (i = 0; i < count; ++i) { if (overlappeds[i].lpOverlapped) { req = uv__overlapped_to_req(overlappeds[i].lpOverlapped); uv__insert_pending_req(loop, req); } } uv_update_time(loop); } else if (GetLastError() != WAIT_TIMEOUT) { uv_fatal_error(GetLastError(), "GetQueuedCompletionStatusEx"); } else if (timeout > 0) { uv_update_time(loop); if (timeout_time > loop->time) { timeout = (DWORD)(timeout_time - loop->time); timeout += repeat ? (1 << (repeat - 1)) : 0; continue; } } break; }}int uv_run(uv_loop_t *loop, uv_run_mode mode) { DWORD timeout; int r; int can_sleep; r = uv__loop_alive(loop); if (!r) uv_update_time(loop); while (r != 0 && loop->stop_flag == 0) { uv_update_time(loop); uv__run_timers(loop); can_sleep = loop->pending_reqs_tail == NULL && loop->idle_handles == NULL; uv__process_reqs(loop); uv__idle_invoke(loop); uv__prepare_invoke(loop); timeout = 0; if ((mode == UV_RUN_ONCE && can_sleep) || mode == UV_RUN_DEFAULT) timeout = uv_backend_timeout(loop); if (pGetQueuedCompletionStatusEx) uv__poll(loop, timeout); else uv__poll_wine(loop, timeout); for (r = 0; r < 8 && loop->pending_reqs_tail != NULL; ++r) uv__process_reqs(loop); uv__metrics_update_idle_time(loop); uv__check_invoke(loop); uv__process_endgames(loop); if (mode == UV_RUN_ONCE) { uv_update_time(loop); uv__run_timers(loop); } r = uv__loop_alive(loop); if (mode == UV_RUN_ONCE || mode == UV_RUN_NOWAIT) break; } if (loop->stop_flag != 0) loop->stop_flag = 0; return r;}int uv_fileno(const uv_handle_t* handle, uv_os_fd_t* fd) { uv_os_fd_t fd_out; switch (handle->type) { case UV_TCP: fd_out = (uv_os_fd_t)((uv_tcp_t*) handle)->socket; break; case UV_NAMED_PIPE: fd_out = ((uv_pipe_t*) handle)->handle; break; case UV_TTY: fd_out = ((uv_tty_t*) handle)->handle; break; case UV_UDP: fd_out = (uv_os_fd_t)((uv_udp_t*) handle)->socket; break; case UV_POLL: fd_out = (uv_os_fd_t)((uv_poll_t*) handle)->socket; break; default: return UV_EINVAL; } if (uv_is_closing(handle) || fd_out == INVALID_HANDLE_VALUE) return UV_EBADF; *fd = fd_out; return 0;}int uv__socket_sockopt(uv_handle_t* handle, int optname, int* value) { int r; int len; SOCKET socket; if (handle == NULL || value == NULL) return UV_EINVAL; if (handle->type == UV_TCP) socket = ((uv_tcp_t*) handle)->socket; else if (handle->type == UV_UDP) socket = ((uv_udp_t*) handle)->socket; else return UV_ENOTSUP; len = sizeof(*value); if (*value == 0) r = getsockopt(socket, SOL_SOCKET, optname, (char*) value, &len); else r = setsockopt(socket, SOL_SOCKET, optname, (const char*) value, len); if (r == SOCKET_ERROR) return uv_translate_sys_error(WSAGetLastError()); return 0;}int uv_cpumask_size(void) { return (int)(sizeof(DWORD_PTR) * 8);}int uv__getsockpeername(const uv_handle_t* handle, uv__peersockfunc func, struct sockaddr* name, int* namelen, int delayed_error) { int result; uv_os_fd_t fd; result = uv_fileno(handle, &fd); if (result != 0) return result; if (delayed_error) return uv_translate_sys_error(delayed_error); result = func((SOCKET) fd, name, namelen); if (result != 0) return uv_translate_sys_error(WSAGetLastError()); return 0;}