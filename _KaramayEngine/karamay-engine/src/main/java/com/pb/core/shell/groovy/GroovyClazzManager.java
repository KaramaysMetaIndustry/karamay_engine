package com.pb.core.shell.groovy;

import groovy.lang.GroovyClassLoader;
import groovy.lang.GroovyObject;
import groovy.util.GroovyScriptEngine;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;

public class GroovyClazzManager {

    public GroovyClazzManager(){}

    private static GroovyScriptEngine groovyScriptEngine;

    private static GroovyClassLoader groovyClassLoader;

    private static HashMap<String, Class<?>> groovyClazzMap;

    static {
        try {
            groovyScriptEngine = new GroovyScriptEngine("/src/main/groovy/");
            groovyClassLoader = groovyScriptEngine.getGroovyClassLoader();
            groovyClazzMap = new HashMap<>();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void tryLoadGroovyClazz(String clazzName, boolean forced)
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

    public static void tryLoadGroovyClazz(String clazzName)
    {
        if(!groovyClazzMap.containsKey(clazzName)) {
            try {
                Class<?> clazz = groovyClassLoader.loadClass(clazzName);
                groovyClazzMap.put(clazzName, clazz);
                System.out.println(clazzName + " has been loaded.");
            } catch (ClassNotFoundException e) {
                System.out.println(e);
            }
        }
    }

    public static void tryInvokeMethod(String clazzName, String funcName, Object[] parameters)
    {
        if(!groovyClazzMap.containsKey(clazzName)){
            tryLoadGroovyClazz(clazzName);
        }

        if(groovyClazzMap.containsKey(clazzName))
        {
            System.out.println("the clazz has been found");
            try {
                GroovyObject groovyObject = (GroovyObject) groovyClazzMap.get(clazzName).getDeclaredConstructor().newInstance();
                Object result = groovyObject.invokeMethod(funcName, parameters);

                System.out.println(clazzName + "."+funcName+" has been invoked successfully");
            } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
                e.printStackTrace();
            }
        }else{
            System.out.println("Do not find the clazz : " + clazzName);
        }

    }

    public static void tryInvokeMethod(String clazzName, String funcName)
    {
        if(groovyClazzMap.containsKey(clazzName))
        {
            System.out.println("the clazz has been found");
            try {
                GroovyObject groovyObject = (GroovyObject) groovyClazzMap.get(clazzName).getDeclaredConstructor().newInstance();
                Object[] params = {};
                Object result = groovyObject.invokeMethod(funcName, params);

                System.out.println(clazzName + "."+"funcName"+" has been invoked successfully");
            } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
                //e.printStackTrace();
                System.out.println(e);
            }
        }else{
            System.out.println("Do not find the clazz : " + clazzName);
        }
    }


}
