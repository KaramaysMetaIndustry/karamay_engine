package com.pb.core.shell.groovy;

import groovy.lang.GroovyClassLoader;
import groovy.util.GroovyScriptEngine;

import java.io.IOException;

public class GroovyShell {

    private static GroovyScriptEngine groovyScriptEngine;

    private static GroovyClassLoader groovyClassLoader;

    static {
        try {
            groovyScriptEngine = new GroovyScriptEngine("");
            groovyClassLoader = new GroovyClassLoader();

            new GroovyShell();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
