package com.pb;

import com.pb.core.shell.groovy.GroovyClazzManager;

public class Main {

    public static void main(String[] args) {
        GroovyClazzManager.tryLoadGroovyClazz("com.core.Woda");
        GroovyClazzManager.tryInvokeMethod("com.core.Woda", "start1");
    }
}
