package com.wyp.nativeopengldemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.wyp.opengl.NativeOpengl;
import com.wyp.opengl.WlSurfaceView;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private WlSurfaceView mWlSurfaceView;
    private NativeOpengl mNativeOpengl;
    byte[] pixels;

    private List<Integer> imgs = new ArrayList<>();
    private int index = -1;
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
        imgs.add(R.drawable.mingren);
        imgs.add(R.drawable.img_1);
        imgs.add(R.drawable.img_2);
        imgs.add(R.drawable.img_3);

        mWlSurfaceView.setOnSurfaceListener(new WlSurfaceView.OnSurfaceListener() {
            @Override
            public void init() {
                readPliex();
            }
        });

    }

    public void changeFilter(View view) {

        if(mNativeOpengl != null)
        {
            mNativeOpengl.surfaceChangeFilter();
        }
    }

    public void changeTexture(View view) {
        readPliex();
    }

    private void readPliex()
    {
        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                getImgeIds());
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        pixels = fcbuffer.array();
        mNativeOpengl.imgData(bitmap.getWidth(), bitmap.getHeight(), pixels.length, pixels);
    }

    private int getImgeIds()
    {
        index ++;
        if(index >= imgs.size())
        {
            index = 0;
        }
        return imgs.get(index);
    }
}
