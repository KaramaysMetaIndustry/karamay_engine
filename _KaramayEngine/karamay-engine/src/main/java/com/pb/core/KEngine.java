package com.pb.core;

public class KEngine {

    private KEngine(){}

    static private KEngine instance;

    static public KEngine getInstance(){
        if(instance==null)
            instance = new KEngine();
        return instance;
    }


    public void start(){
        System.out.println("k-engine start now");

        System.out.println("k-engine ready to tick");
        while(!bShouldExit){
            tick(1.0f);
        }

        shutdown();
    }

    private boolean bShouldExit;

    private void tick(float deltaTime){
        System.out.println("k-engine ticking");
    }

    private void shutdown(){
        System.out.println("k-engine shutdown now");
    }


}
