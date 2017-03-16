package com.clam314.hellojni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class FFmpegHelloActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ffmpeg-hello");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_hello);
        TextView tv = (TextView) findViewById(R.id.tv_info);
        tv.setText(avcodeConfigFromJni());
    }

    public native String avcodeConfigFromJni();
}
