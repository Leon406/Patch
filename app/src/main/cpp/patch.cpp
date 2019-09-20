#include <jni.h>
#include <string>
#include "logutil.hpp"
#include <ctime>

extern "C" {
extern int main(int argc, const char *argv[]);
extern int diff_main(int argc, const char *argv[]);
}

char *jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C"
JNIEXPORT jint JNICALL
Java_me_leon_patch_PatchUtil_bsPatch(JNIEnv *env, jclass thiz, jstring old, jstring patch_,
                                     jstring output_) {
    LOGD("PATCH:  %s","patch start");
    int64_t start = currentTimeMills();
    const char *oldApk = jstringToChar(env, old);
    const char *patch = jstringToChar(env, patch_);
    const char *output = jstringToChar(env, output_);
    LOGD("PATCH: %s + %s = %s" , oldApk, patch, output);
    const char *argv[] = {"", oldApk, output, patch};
    int r = main(4, argv);
    int64_t end = currentTimeMills();
    LOGD("PATCH:  it takes %lld ms to patch",end-start);

    env->ReleaseStringUTFChars(old, oldApk);
    env->ReleaseStringUTFChars(patch_, patch);
    env->ReleaseStringUTFChars(output_, output);
    return r;
}
extern "C"
JNIEXPORT jint JNICALL
Java_me_leon_patch_PatchUtil_bsDiff(JNIEnv *env, jclass thiz, jstring old, jstring newfile_,
                                    jstring patch_) {
    LOGD("PATCH:  %s","diff start");
    int64_t start = currentTimeMills();
    const char *oldApk = env->GetStringUTFChars(old, 0);
    const char *newFile = env->GetStringUTFChars(newfile_, 0);
    const char *output = env->GetStringUTFChars(patch_, 0);
    LOGD("PATCH  diff:   %s - %s = %s", newFile, oldApk, output);
    const char *argv[] = {"", oldApk, newFile, output};
    int r = diff_main(4, argv);
    int64_t end = currentTimeMills();
    LOGD("PATCH:  it takes %lld ms to patch",end-start);
    env->ReleaseStringUTFChars(old, oldApk);
    env->ReleaseStringUTFChars(newfile_, newFile);
    env->ReleaseStringUTFChars(patch_, output);
    return r;

}