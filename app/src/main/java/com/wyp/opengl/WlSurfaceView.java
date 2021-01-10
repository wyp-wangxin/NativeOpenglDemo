package com.wyp.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by wyp on 2021/1/10.
 */

public class WlSurfaceView extends SurfaceView implements SurfaceHolder.Callback{


    private NativeOpengl nativeOpengl;

    public WlSurfaceView(Context context) {
        this(context,null);
    }

    public WlSurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs,0);
    }

    public WlSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
    }

    public void setNativeOpengl(NativeOpengl nativeOpengl) {
        this.nativeOpengl = nativeOpengl;
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        if(nativeOpengl != null)
        {
            nativeOpengl.surfaceCreate(surfaceHolder.getSurface());
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {
        if(nativeOpengl != null)
        {
            nativeOpengl.surfaceChange(width, height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }

}
