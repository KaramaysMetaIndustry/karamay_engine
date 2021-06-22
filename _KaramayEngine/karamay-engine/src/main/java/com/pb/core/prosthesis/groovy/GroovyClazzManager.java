package com.pb.core.prosthesis.groovy;

import groovy.lang.GroovyClassLoader;
import groovy.lang.GroovyObject;
import groovy.util.GroovyScriptEngine;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
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
        tryLoadGroovyClazz(clazzName, false);
    }

    public static Object tryInvokeMethod(String clazzName, String funcName, Object[] parameters)
    {
        if(!groovyClazzMap.containsKey(clazzName)) tryLoadGroovyClazz(clazzName);

        if(groovyClazzMap.containsKey(clazzName))
        {
            System.out.println("clazz: "+ clazzName +" has been found");
            try {
                GroovyObject groovyObject = (GroovyObject) groovyClazzMap.get(clazzName).getDeclaredConstructor().newInstance();
                Object result = groovyObject.invokeMethod(funcName, parameters);
                System.out.println("\n" + clazzName + "."+funcName+" has been invoked");
                return result;
            } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
                e.printStackTrace();
                System.out.println(e);
            }
        }else{
            System.out.println("do not find the clazz : " + clazzName);
        }

        return null;
    }

    public static Object tryInvokeMethod(String clazzName, String funcName)
    {
        Object[] parameters= {};
        return tryInvokeMethod(clazzName, funcName, parameters);
    }


    public static void tryInvokeMethod() throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] bytes = md.digest();
        final char[] HEX_DIGITS = "0123456789ABCDEF".toCharArray();
        StringBuilder ret = new StringBuilder(bytes.length * 2);

    }

}
