**生成差分包**
bsdiff old.apk new.apk old-to-new.patch

**合并补丁**
bspatch old.apk new2.apk old-to-new.patch

**两个快速使用脚本**

1.拖动新包到这里生成差分包(旧包old.apk).bat

​    将需要原始包命令为old.apk,将新包拖到该文件即可自动生成差分包

2.拖动patch到这里合并生成新包 

   将需要patch 包拖到该文件即可自动合并成新包