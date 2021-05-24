package com.core.graphics.buffer;

import java.nio.ByteBuffer;

public class AtomicCounterBuffer {

    public AtomicCounterBuffer()
    {
        handle = construct();
    }

    private int handle;

    private native int construct();



    public native void fill(ByteBuffer byteBuffer);

}
