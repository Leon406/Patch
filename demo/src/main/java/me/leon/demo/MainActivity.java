package me.leon.demo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import java.io.File;

import me.leon.patch.PatchUtil;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        String old = "/sdcard/old.apk";
        String newfile = "/sdcard/new.apk";
        String patch = "/sdcard/1.patch";
        findViewById(R.id.diff).setOnClickListener(v -> {
            Log.d("PatchUtil",""+new File(old).exists()+ (""+new File(newfile).exists()));
            int i = PatchUtil.bsDiff(old, newfile, patch);
            Log.d("PatchUtil", "diff result : " + i);
        });
        findViewById(R.id.patch).setOnClickListener(v -> {
            int i = PatchUtil.bsPatch(old, patch, "/sdcard/new2.apk");
            Log.d("PatchUtil", "patch result : " + i);
        });
    }
}
