  
#ifndef UV_DARWIN_STUB_H_
#define UV_DARWIN_STUB_H_

#include <stdint.h>
 struct CFArrayCallBacks; struct CFRunLoopSourceContext; struct FSEventStreamContext; struct CFRange; typedef double CFAbsoluteTime; typedef double CFTimeInterval; typedef int FSEventStreamEventFlags; typedef int OSStatus; typedef long CFIndex; typedef struct CFArrayCallBacks CFArrayCallBacks; typedef struct CFRunLoopSourceContext CFRunLoopSourceContext; typedef struct FSEventStreamContext FSEventStreamContext; typedef uint32_t FSEventStreamCreateFlags; typedef uint64_t FSEventStreamEventId; typedef unsigned CFStringEncoding; typedef void* CFAllocatorRef; typedef void* CFArrayRef; typedef void* CFBundleRef; typedef void* CFDataRef; typedef void* CFDictionaryRef; typedef void* CFMutableDictionaryRef; typedef struct CFRange CFRange; typedef void* CFRunLoopRef; typedef void* CFRunLoopSourceRef; typedef void* CFStringRef; typedef void* CFTypeRef; typedef void* FSEventStreamRef; typedef uint32_t IOOptionBits; typedef unsigned int io_iterator_t; typedef unsigned int io_object_t; typedef unsigned int io_service_t; typedef unsigned int io_registry_entry_t;  typedef void (*FSEventStreamCallback)(const FSEventStreamRef, void*, size_t, void*, const FSEventStreamEventFlags*, const FSEventStreamEventId*); struct CFRunLoopSourceContext { CFIndex version; void* info; void* pad[7]; void (*perform)(void*); }; struct FSEventStreamContext { CFIndex version; void* info; void* pad[3]; }; struct CFRange { CFIndex location; CFIndex length; }; static const CFStringEncoding kCFStringEncodingUTF8 = 0x8000100; static const OSStatus noErr = 0; static const FSEventStreamEventId kFSEventStreamEventIdSinceNow = -1; static const int kFSEventStreamCreateFlagNoDefer = 2; static const int kFSEventStreamCreateFlagFileEvents = 16; static const int kFSEventStreamEventFlagEventIdsWrapped = 8; static const int kFSEventStreamEventFlagHistoryDone = 16; static const int kFSEventStreamEventFlagItemChangeOwner = 0x4000; static const int kFSEventStreamEventFlagItemCreated = 0x100; static const int kFSEventStreamEventFlagItemFinderInfoMod = 0x2000; static const int kFSEventStreamEventFlagItemInodeMetaMod = 0x400; static const int kFSEventStreamEventFlagItemIsDir = 0x20000; static const int kFSEventStreamEventFlagItemModified = 0x1000; static const int kFSEventStreamEventFlagItemRemoved = 0x200; static const int kFSEventStreamEventFlagItemRenamed = 0x800; static const int kFSEventStreamEventFlagItemXattrMod = 0x8000; static const int kFSEventStreamEventFlagKernelDropped = 4; static const int kFSEventStreamEventFlagMount = 64; static const int kFSEventStreamEventFlagRootChanged = 32; static const int kFSEventStreamEventFlagUnmount = 128; static const int kFSEventStreamEventFlagUserDropped = 2; 
#endif 
