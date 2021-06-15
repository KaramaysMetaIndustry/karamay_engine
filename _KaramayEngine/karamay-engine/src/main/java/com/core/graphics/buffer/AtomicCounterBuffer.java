package com.core.graphics.buffer;

import java.nio.ByteBuffer;

public class AtomicCounterBuffer {

    public AtomicCounterBuffer()
    {
        _handle = _construct();
    }

    private Long _handle;

    private native Long _construct();

    private native Long _destroy();

}
