package me.leon.patch;

/**
 * <p>description：</p>
 * <p>author：Leon</p>
 * <p>date：2019/9/19 0019</p>
 * <p>e-mail：deadogone@gmail.com</p>
 */
public class PatchUtil {
    static {
        System.loadLibrary("patch");
    }


    /**
     * 耗时操作,建议放到子线程
      * <p>需添加权限 {@code <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>}</p>
     * @param old 旧文件地址
     * @param patch  补丁地址
     * @param output  生成的新文件
     * @return 状态码 {@code 0 成功}
     */
    public static native int bsPatch(String old, String patch, String output);

    /**
     * 耗时操作,建议放到子线程
     * <p>需添加权限 {@code <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>}</p>
     * @param old 旧文件地址
     * @param newfile 新文件地址
     * @param patch  生成补丁包地址
     * @return 状态码 {@code 0 成功}
     */
    public static native int bsDiff(String old, String newfile, String patch);
}
