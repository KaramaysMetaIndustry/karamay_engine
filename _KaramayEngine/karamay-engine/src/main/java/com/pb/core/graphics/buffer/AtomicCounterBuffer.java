package com.pb.core.graphics.buffer;

public class AtomicCounterBuffer {

    public AtomicCounterBuffer()
    {
        _handle = _construct();
    }

    private Long _handle;

    private native Long _construct();

    private native Long _destroy();

}
