**Andorid Patch文件增量工具**[ ![Download](https://api.bintray.com/packages/leon4062/maven/patch/images/download.svg?version=1.0.1) ](https://bintray.com/leon4062/maven/patch/1.0.1/link)

基于bsdiff+bzip+NDK实现



**项目目录介绍**

--app     包含c/c++,原始构建module, c/c++ 每次构建比较耗时

--patch   依赖库,直接提取so库,解决重新编译c/c++耗时问题

--demo  测试demo

--prepare 第三方c库

--bsdiff4.3-win32  windows 下bsdiff, 主要用于生成差分包



**如何使用**

```
dependencies {
	implementation 'me.leon406:patch:1.0.1'
}
#若无法使用,请在project build.gradle repositories闭包中加上
#maven {url  "https://dl.bintray.com/leon4062/maven"}
```

```
 // 生成差分包
 int i = PatchUtil.bsDiff(old, newfile, patch);// 返回值 为0表示执行成功
 // 合并成新包
 PatchUtil.bsPatch(old, patch, newfile);
 
```

别忘了配置清单文件

```
 <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
 <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />

 <uses-permission android:name="android.permission.REQUEST_INSTALL_PACKAGES"/>
```



