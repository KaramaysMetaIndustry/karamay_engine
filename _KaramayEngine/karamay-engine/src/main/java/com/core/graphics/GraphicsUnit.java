package com.core.graphics;

public class GraphicsUnit {

    static {
        System.loadLibrary("com_core_graphics_GraphicsUnit");
    }

    public native void start();

    public native void shutdown();


    public native void push();

    public native void remove();

}
