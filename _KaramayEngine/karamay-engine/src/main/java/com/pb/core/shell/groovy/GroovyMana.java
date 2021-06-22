package com.pb.core.shell.groovy;

import groovy.lang.GroovyClassLoader;
import groovy.lang.GroovyObject;
import groovy.util.GroovyScriptEngine;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;

public class GroovyMana {

    private static GroovyScriptEngine groovyScriptEngine;

    private static GroovyClassLoader groovyClassLoader;


    private static HashMap<String, Class<?>> groovyClazzMap;

    //private static HashMap<String, GroovyObject> groovyObjectHashMap;

    static {
        try {
            groovyScriptEngine = new GroovyScriptEngine("/src/main/groovy/");
            groovyClassLoader = groovyScriptEngine.getGroovyClassLoader();

            groovyClazzMap = new HashMap<>();

            Class<?> clazz = groovyClassLoader.loadClass("com.core.Woda");

            tryLoadGroovyClazz("com.core.Woda", false);
            tryLoadGroovyClazz("com.core.Woda", true);
            //tryLoadGroovyClazz("com.core.Woda", true);

            //GroovyObject groovyObject = (GroovyObject) groovyClassLoader.loadClass("com.core.Woda").getDeclaredConstructor().newInstance();


            Object[] params = {};
            tryInvokeMethod("com.core.Woda", "start", params);

        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }


    private static void tryLoadGroovyClazz(String clazzName, boolean forced)
    {
        if(!groovyClazzMap.containsKey(clazzName) | forced) {
            try {
                Class<?> clazz = groovyClassLoader.loadClass(clazzName);
                groovyClazzMap.put(clazzName, clazz);

                String str = ".";
                if(forced) str = " forcedly.";
                System.out.println(clazzName + " has been loaded" + str);

            } catch (ClassNotFoundException e) {
                System.out.println(e);
            }
        }
    }

    private static void tryInvokeMethod(String clazzName, String funcName, Object[] params)
    {
        if(groovyClazzMap.containsKey(clazzName))
        {
            System.out.println("the clazz has been found");
            try {
                GroovyObject groovyObject = (GroovyObject) groovyClazzMap.get(clazzName).getDeclaredConstructor().newInstance();
                groovyObject.invokeMethod(funcName, params);
                System.out.println(clazzName + "."+"funcName"+" has been invoked successfully");
            } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
                e.printStackTrace();
            }
        }else
            System.out.println("do not find the clazz");
    }




}
