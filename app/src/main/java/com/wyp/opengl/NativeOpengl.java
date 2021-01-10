package com.wyp.opengl;

import android.view.Surface;

/**
 * Created by wyp on 2021/1/10.
 */

public class NativeOpengl {
    static {
        System.loadLibrary("native-lib");
    }

    public native void surfaceCreate(Surface surface);
    public native void surfaceChange(int width, int height);
}
