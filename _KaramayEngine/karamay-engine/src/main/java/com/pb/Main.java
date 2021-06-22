package com.pb;

import com.pb.core.prosthesis.groovy.GroovyClazzManager;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.core.Logger;

public class Main {

    public static void main(String[] args) {



        while(true)
        {
            GroovyClazzManager.tryLoadGroovyClazz("com.core.Woda", true);
            Object result = GroovyClazzManager.tryInvokeMethod("com.core.Woda", "start");
        }

        //boolean shouldExit = false;

        //Logger logger = (Logger) LogManager.getLogger();
        //logger.error("aaaa");
    }
}
