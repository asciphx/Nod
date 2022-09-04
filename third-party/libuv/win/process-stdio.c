
#include <assert.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include "uv.h"
#include "internal.h"
#include "handle-inl.h"

#define CHILD_STDIO_SIZE(count)  (sizeof(int) +  sizeof(unsigned char) * (count) +  sizeof(uintptr_t) * (count))

#define CHILD_STDIO_COUNT(buffer)  *((unsigned int*) (buffer))

#define CHILD_STDIO_CRT_FLAGS(buffer, fd)  *((unsigned char*) (buffer) + sizeof(int) + fd)

#define CHILD_STDIO_HANDLE(buffer, fd) *((HANDLE*) ((unsigned char*) (buffer) +  sizeof(int) +  sizeof(unsigned char) *  CHILD_STDIO_COUNT((buffer)) +  sizeof(HANDLE) * (fd)))

#define FOPEN 0x01
#define FEOFLAG 0x02
#define FCRLF 0x04
#define FPIPE 0x08
#define FNOINHERIT 0x10
#define FAPPEND 0x20
#define FDEV 0x40
#define FTEXT 0x80
void uv_disable_stdio_inheritance(void) { HANDLE handle; STARTUPINFOW si; handle = GetStdHandle(STD_INPUT_HANDLE); if (handle != NULL && handle != INVALID_HANDLE_VALUE) SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0); handle = GetStdHandle(STD_OUTPUT_HANDLE); if (handle != NULL && handle != INVALID_HANDLE_VALUE) SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0); handle = GetStdHandle(STD_ERROR_HANDLE); if (handle != NULL && handle != INVALID_HANDLE_VALUE) SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0); GetStartupInfoW(&si); if (uv__stdio_verify(si.lpReserved2, si.cbReserved2)) uv__stdio_noinherit(si.lpReserved2);}static int uv__duplicate_handle(uv_loop_t* loop, HANDLE handle, HANDLE* dup) { HANDLE current_process; if (handle == INVALID_HANDLE_VALUE || handle == NULL || handle == (HANDLE) -2) { *dup = INVALID_HANDLE_VALUE; return ERROR_INVALID_HANDLE; } current_process = GetCurrentProcess(); if (!DuplicateHandle(current_process, handle, current_process, dup, 0, TRUE, DUPLICATE_SAME_ACCESS)) { *dup = INVALID_HANDLE_VALUE; return GetLastError(); } return 0;}static int uv__duplicate_fd(uv_loop_t* loop, int fd, HANDLE* dup) { HANDLE handle; if (fd == -1) { *dup = INVALID_HANDLE_VALUE; return ERROR_INVALID_HANDLE; } handle = uv__get_osfhandle(fd); return uv__duplicate_handle(loop, handle, dup);}int uv__create_nul_handle(HANDLE* handle_ptr, DWORD access) { HANDLE handle; SECURITY_ATTRIBUTES sa; sa.nLength = sizeof sa; sa.lpSecurityDescriptor = NULL; sa.bInheritHandle = TRUE; handle = CreateFileW(L"NUL", access, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING, 0, NULL); if (handle == INVALID_HANDLE_VALUE) { return GetLastError(); } *handle_ptr = handle; return 0;}int uv__stdio_create(uv_loop_t* loop, const uv_process_options_t* options, BYTE** buffer_ptr) { BYTE* buffer; int count, i; int err; count = options->stdio_count; if (count < 0 || count > 255) { return ERROR_NOT_SUPPORTED; } else if (count < 3) { count = 3; } buffer = (BYTE*) uv__malloc(CHILD_STDIO_SIZE(count)); if (buffer == NULL) { return ERROR_OUTOFMEMORY; } CHILD_STDIO_COUNT(buffer) = count; for (i = 0; i < count; ++i) { CHILD_STDIO_CRT_FLAGS(buffer, i) = 0; CHILD_STDIO_HANDLE(buffer, i) = INVALID_HANDLE_VALUE; } for (i = 0; i < count; ++i) { uv_stdio_container_t fdopt; if (i < options->stdio_count) { fdopt = options->stdio[i]; } else { fdopt.flags = UV_IGNORE; } switch (fdopt.flags & (UV_IGNORE | UV_CREATE_PIPE | UV_INHERIT_FD | UV_INHERIT_STREAM)) { case UV_IGNORE: if (i <= 2) { DWORD access = (i == 0) ? FILE_GENERIC_READ : FILE_GENERIC_WRITE | FILE_READ_ATTRIBUTES; err = uv__create_nul_handle(&CHILD_STDIO_HANDLE(buffer, i), access); if (err) goto error; CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV; } break; case UV_CREATE_PIPE: { uv_pipe_t* parent_pipe = (uv_pipe_t*) fdopt.data.stream; HANDLE child_pipe = INVALID_HANDLE_VALUE; assert(fdopt.data.stream->type == UV_NAMED_PIPE); assert(!(fdopt.data.stream->flags & UV_HANDLE_CONNECTION)); assert(!(fdopt.data.stream->flags & UV_HANDLE_PIPESERVER)); err = uv__create_stdio_pipe_pair(loop, parent_pipe, &child_pipe, fdopt.flags); if (err) goto error; CHILD_STDIO_HANDLE(buffer, i) = child_pipe; CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FPIPE; break; } case UV_INHERIT_FD: { HANDLE child_handle; err = uv__duplicate_fd(loop, fdopt.data.fd, &child_handle); if (err) { if (fdopt.data.fd <= 2 && err == ERROR_INVALID_HANDLE) { CHILD_STDIO_CRT_FLAGS(buffer, i) = 0; CHILD_STDIO_HANDLE(buffer, i) = INVALID_HANDLE_VALUE; break; } goto error; } switch (GetFileType(child_handle)) { case FILE_TYPE_DISK: CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN; break; case FILE_TYPE_PIPE: CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FPIPE; break; case FILE_TYPE_CHAR: case FILE_TYPE_REMOTE: CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV; break; case FILE_TYPE_UNKNOWN: if (GetLastError() != 0) { err = GetLastError(); CloseHandle(child_handle); goto error; } CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV; break; default: assert(0); return -1; } CHILD_STDIO_HANDLE(buffer, i) = child_handle; break; } case UV_INHERIT_STREAM: { HANDLE stream_handle, child_handle; unsigned char crt_flags; uv_stream_t* stream = fdopt.data.stream; if (stream->type == UV_TTY) { stream_handle = ((uv_tty_t*) stream)->handle; crt_flags = FOPEN | FDEV; } else if (stream->type == UV_NAMED_PIPE && stream->flags & UV_HANDLE_CONNECTION) { stream_handle = ((uv_pipe_t*) stream)->handle; crt_flags = FOPEN | FPIPE; } else { stream_handle = INVALID_HANDLE_VALUE; crt_flags = 0; } if (stream_handle == NULL || stream_handle == INVALID_HANDLE_VALUE) { err = ERROR_NOT_SUPPORTED; goto error; } err = uv__duplicate_handle(loop, stream_handle, &child_handle); if (err) goto error; CHILD_STDIO_HANDLE(buffer, i) = child_handle; CHILD_STDIO_CRT_FLAGS(buffer, i) = crt_flags; break; } default: assert(0); return -1; } } *buffer_ptr = buffer; return 0; error: uv__stdio_destroy(buffer); return err;}void uv__stdio_destroy(BYTE* buffer) { int i, count; count = CHILD_STDIO_COUNT(buffer); for (i = 0; i < count; ++i) { HANDLE handle = CHILD_STDIO_HANDLE(buffer, i); if (handle != INVALID_HANDLE_VALUE) { CloseHandle(handle); } } uv__free(buffer);}void uv__stdio_noinherit(BYTE* buffer) { int i, count; count = CHILD_STDIO_COUNT(buffer); for (i = 0; i < count; ++i) { HANDLE handle = CHILD_STDIO_HANDLE(buffer, i); if (handle != INVALID_HANDLE_VALUE) { SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0); } }}int uv__stdio_verify(BYTE* buffer, WORD size) { unsigned int count; if (buffer == NULL) return 0; if (size < CHILD_STDIO_SIZE(0)) return 0; count = CHILD_STDIO_COUNT(buffer); if (count > 256) return 0; if (size < CHILD_STDIO_SIZE(count)) return 0; return 1;}WORD uv__stdio_size(BYTE* buffer) { return (WORD) CHILD_STDIO_SIZE(CHILD_STDIO_COUNT((buffer)));}HANDLE uv__stdio_handle(BYTE* buffer, int fd) { return CHILD_STDIO_HANDLE(buffer, fd);}