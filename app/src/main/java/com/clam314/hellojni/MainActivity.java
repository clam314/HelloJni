package com.clam314.hellojni;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    // Example of a call to a native method
    findViewById(R.id.bt_ffmpeg_hello).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.bt_ffmpeg_hello:
                startActivity(new Intent(this,FFmpegHelloActivity.class));
                break;
        }
    }

    public native String stringFromJNI();
    public native int stringSizeFormJNI(String s);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


}
