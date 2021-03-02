package com.framework.nebula.network;

public class Connection {

    static {
        // hello.dll (Windows) or libhello.so (Unixes)
        System.loadLibrary("Connection");
    }

    public native void sendString();

    public native void send(Connection connection);
}
