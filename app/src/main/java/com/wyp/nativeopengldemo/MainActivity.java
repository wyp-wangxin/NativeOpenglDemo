package com.wyp.nativeopengldemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.wyp.opengl.NativeOpengl;
import com.wyp.opengl.WlSurfaceView;

public class MainActivity extends AppCompatActivity {

    private WlSurfaceView mWlSurfaceView;
    private NativeOpengl mNativeOpengl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mWlSurfaceView = findViewById(R.id.wlsurfaceview);
        Log.d("wwxx","hhhhhhhh 0");
        mNativeOpengl = new NativeOpengl();
        Log.d("wwxx","hhhhhhhh 1");
        mWlSurfaceView.setNativeOpengl(mNativeOpengl);
        Log.d("wwxx","hhhhhhhh 2");
    }

}
