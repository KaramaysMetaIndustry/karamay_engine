package com.pb;

import groovy.lang.Binding;
import groovy.util.GroovyScriptEngine;
import groovy.util.ResourceException;
import groovy.util.ScriptException;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

public class Main {
    public static void main(String[] args) throws IOException, ScriptException, ResourceException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {

        GroovyScriptEngine engine =
                new GroovyScriptEngine("src/main/java/com/groovy/script/");

        Binding binding = new Binding();
    }
}
