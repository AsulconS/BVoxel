#ifndef COMMON_H
#define COMMON_H

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long long int64;
typedef unsigned long long uint64;

#define LOG_ERROR "Error"
#define LOG_WARNING "Warning"
#define LOG_TYPE_RENDERER "Renderer"
#define LOG_TYPE_IO "IO"
#define DEBUG_LOG(category, level, message, ...) \
    fprintf(stderr, "[%s] ", category); \
    fprintf(stderr, "[%s] (%s:%d): ", level, __FILE__, __LINE__); \
    fprintf(stderr, message, ##__VA_ARGS__); \
    fprintf(stderr, "\n")

#endif // COMMON_H
