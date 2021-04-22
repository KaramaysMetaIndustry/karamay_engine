package com;

import com.core.KEngine;
import groovy.lang.Binding;
import groovy.lang.GroovyClassLoader;
import groovy.lang.GroovyObject;
import groovy.util.GroovyScriptEngine;
import groovy.util.ResourceException;
import groovy.util.ScriptException;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;

public class Main {
    public static void main(String[] args) throws IOException, ScriptException, ResourceException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {

        GroovyScriptEngine engine = new GroovyScriptEngine("src/main/java/com/groovy/script/");

        Binding binding = new Binding();
        //binding.setVariable("name", "xxx");\
        Object result1 = engine.run("Trace.groovy", binding);



        GroovyClassLoader classLoader = engine.getGroovyClassLoader();
        //Class c = classLoader.loadClass("Tracer.groovy");
        //c.getDeclaredConstructor().newInstance();


//        KEngine engine = KEngine.getInstance();
//        engine.start();
    }
}
