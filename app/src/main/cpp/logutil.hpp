
#ifndef LOGUTIL_HPP
#define LOGUTIL_HPP

#define NDK_LOG true
#define C_LOG false
#include <ctime>
#if NDK_LOG
#include <android/log.h>
#include <jni.h>
#endif

#define TAG "LEON_JNI"

#if NDK_LOG
#define log_print_verbose(fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, fmt, __VA_ARGS__)
#define log_print_debug(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, __VA_ARGS__)
#define log_print_info(fmt, ...) __android_log_print(ANDROID_LOG_INFO, TAG, fmt, __VA_ARGS__)
#define log_print_warn(fmt, ...) __android_log_print(ANDROID_LOG_WARN, TAG, fmt, __VA_ARGS__)
#define log_print_error(fmt, ...) __android_log_print(ANROID_LOG_ERROR, TAG, fmt, __VA_ARGS__)
#elif C_LOG
#define log_print_verbose(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#define log_print_debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define log_print_info(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define log_print_warn(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#define log_print_error(fmt, ...) printf(fmt,  ##__VA_ARGS__)
#else
#define log_print_verbose(fmt, ...)
#define log_print_debug(fmt, ...)
#define log_print_info(fmt, ...)
#define log_print_warn(fmt, ...)
#define log_print_error(fmt, ...)
#endif


#define LOGV(fmt, ...) log_print_verbose(fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) log_print_debug(fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) log_print_info(fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) log_print_warn(fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) log_print_error(fmt, ##__VA_ARGS__)

#endif // LOGUTIL_HPP

#define now() time(NULL)
int64_t getCurrentTime()      //直接调用这个函数就行了，返回值最好是int64_t，long long应该也可以
{
    struct timeval tv;
    gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#define currentTimeMills() getCurrentTime()
