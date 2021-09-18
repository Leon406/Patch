<p align="center"><img src="https://profile-counter.glitch.me/Leon406_Patch/count.svg" alt="Patch :: Visitor's Count" />
 <img width=0 height=0 src="https://profile-counter.glitch.me/Leon406/count.svg" alt="Leon406:: Visitor's Count" />
</p>


## Android基于NDK 实现 bsdiff功能实现

### 准备

下载所需要c文件,直接解压即可

[bsdiff](http://www.daemonology.net/bsdiff/) 
[bzip(bsdiff依赖库)](https://sourceforge.net/projects/bzip2/)  

项目prepare目录已经下载好所需的文件

### 项目创建

#### 0.Android Studio新建c++项目

#### 1.解压bzip到 src/main/cpp/bzip目录 (可以删除后缀不是.c或.h文件,保留文件参考项目)

#### 2.解压bsdiff 到 src/main/cpp/目录

#### 3.配置cmakeLists.txt

  

```
#关联bzip目录
file(GLOB bzip bzip/*.c)
#添加需要参与编译的c/c++库
add_library( # Sets the name of the library.
        patch   # 默认native-lib

        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ${bzip}
        bspatch.c
        bsdiff.c
        patch.cpp  # 默认native-lib.cpp
        )
        
  #将bzip目录 include, 不需要写包路径
include_directories(bzip)
```

#### 4.创建工具类PatchUtil.java

```
public class PatchUtil {
    static {
        System.loadLibrary("patch");  // 默认native-lib
    }


    public static native int bsPatch(String old, String patch, String output);

    public static native int bsDiff(String old, String newfile, String patch);
}
```

在方法上使用快捷键ALT+ENTER 自动生成 jni 方法

#### 5.实现bsdiff 和 bspatch 功能

```
// 声明外部c的方法, bsdiff,和bspatch都有main方法,记得改成不同的方法名
extern "C" {
		extern int main(int argc, const char *argv[]);
		extern int diff_main(int argc, const char *argv[]);
}
 
 extern "C" JNIEXPORT jint JNICALL
Java_me_leon_patch_PatchUtil_bsDiff(JNIEnv *env, jclass thiz, jstring old, jstring                                         newfile_,jstring patch_) {
	
    // 将jstring 转char *  ,因为bspatch的参数需要
    const char *oldApk = env->GetStringUTFChars(old, 0);
    const char *newFile = env->GetStringUTFChars(newfile_, 0);
    const char *output = env->GetStringUTFChars(patch_, 0);
    
    // 调用bsDiff c的方法
    const char *argv[] = {"", oldApk, newFile, output};
    int r = diff_main(4, argv);

    
    // jstring 释放  
    // C/C++ 没有java 的gc功能,需要手动释放资源  
    env->ReleaseStringUTFChars(old, oldApk);
    env->ReleaseStringUTFChars(newfile_, newFile);
    env->ReleaseStringUTFChars(patch_, output);
    return r;

}



extern "C" JNIEXPORT jint JNICALL
Java_me_leon_patch_PatchUtil_bsPatch(JNIEnv *env, jclass thiz, jstring old,
									 jstring patch_,
                                     jstring output_) {
    // 将jstring 转char * 
    const char *oldApk = jstringToChar(env, old);
    const char *patch = jstringToChar(env, patch_);
    const char *output = jstringToChar(env, output_);
    
    // 调用bsPatch c的方法
    const char *argv[] = {"", oldApk, output, patch};
    int r = main(4, argv);
   
    // 资源 释放 
    env->ReleaseStringUTFChars(old, oldApk);
    env->ReleaseStringUTFChars(patch_, patch);
    env->ReleaseStringUTFChars(output_, output);
    return r;
}



```



#### 6.编译运行代码

可能会出现CMake Error: CMAKE_C_COMPILER not set, after EnableLanguage

原因:   高版本ndk,默认abiFilters 是 armeabi-v7a

解决:   在module  build.gradle  defaultConfig闭包添加

```
ndk{
     abiFilters "arm64-v8a","armeabi-v7a","x86","x86_64"
}
```

#### 7.编译成功后, 编写测试程序,测试PatchUtil的两个方法

页面跟功能请自行实现,加两个Button,实现PatchUtil的功能

如果使用app或demo,请先准备测试文件,

```
adb push old.apk  /sdcard/
adb push new.apk  /sdcard/
```

#### 8.清单文件配置文件读取权限(高版本需要动态授权)

```
 <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
 <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />

 <uses-permission android:name="android.permission.REQUEST_INSTALL_PACKAGES"/>
```

#### 9.测试

 返回结果为0表示成功,可用adb 命令查看文件情况

```
adb shell
cd /sdcard
ll
```



### 封装lib给他人使用

- 调用gradle命令生成so库

```
graldew build
```

- 新建Android lib项目,包名同c++项目
- 拷贝PatchUtil.java
- 拷贝 \build\intermediates\merged_native_libs\release\out\lib下所有文件夹  到src/main/jniLibs
- 使用(参考demo 的使用)
  - 通过implementation project 方式引入
  - 也可以上传到jcenter 或 maven 私服后 ,直接implementaion

附上个人封装测试好的库:

```
implementation 'me.leon406:patch:1.0.1'
#若无法使用,请在project build.gradle repositories闭包中加上
#maven {url  "https://dl.bintray.com/leon4062/maven"}
```

 项目地址: https://github.com/Leon406/Patch

### 参考:

[CMake Error: CMAKE_C_COMPILER not set, after EnableLanguage](https://blog.csdn.net/ChinaBvb/article/details/81137217)

[Android增量更新（bsdiff使用）](https://www.jianshu.com/p/4ca7933185f7)

