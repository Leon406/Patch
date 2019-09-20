package me.leon.patch;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("dddd");
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

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
