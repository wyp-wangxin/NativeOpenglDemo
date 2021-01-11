package com.wyp.nativeopengldemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.wyp.opengl.NativeOpengl;
import com.wyp.opengl.WlSurfaceView;

import java.nio.ByteBuffer;

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

        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                R.drawable.mingren);
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        byte[] pixels = fcbuffer.array();
        mNativeOpengl.imgData(bitmap.getWidth(), bitmap.getHeight(), pixels.length, pixels);
    }

}
