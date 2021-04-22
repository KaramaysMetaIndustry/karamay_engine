package com.template;

import com.framework.nebula.application.KNApplicationInstance;

import java.util.ArrayList;

public class KNTApplicationInstance extends KNApplicationInstance {

    @Override
    public void initialize() {
        super.initialize();

        applicationRule = new KNTApplicationRule();
        world = new KNTWorld();

        onRun = () -> {
            System.out.println("ready to run");
        };

        postRun = () -> {
            System.out.println("run end");
        };



    }






}
