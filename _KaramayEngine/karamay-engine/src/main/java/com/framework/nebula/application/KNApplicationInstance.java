package com.framework.nebula.application;

import com.framework.nebula.application.event.*;
import com.framework.nebula.rule.KNApplicationRule;
import com.framework.nebula.world.KNWorld;

public class KNApplicationInstance {

    protected KNApplicationRule applicationRule;

    protected KNWorld world;

    /*
    * 仅建议：在继承该类后，可以扩展这些逻辑，并不允许将事件使用权暴露给该类以外的任何其他类
    * */
    protected KNApplicationInstanceOnRun onRun;
    protected KNApplicationInstancePostRun postRun;
    protected KNApplicationInstanceOnExit onExit;
    protected KNApplicationInstancePostExit postExit;
    protected KNApplicationInstanceOnTick onTick;
    protected KNApplicationInstancePostTick postTick;

    public void initialize() {}

    public final void tick(float deltaTime){
        if(onTick != null)
            onTick.execute(deltaTime);


        if(postTick != null)
            postTick.execute(deltaTime);
    }

    public final void run(){
        if(onRun != null)
            onRun.execute();


        if(postRun != null)
            postRun.execute();
    }

    public final void exit(){
        if(onExit != null){
            onExit.execute();
        }


        if(postExit != null){
            postExit.execute();
        }
    }


    public final KNApplicationRule getApplicationRule(){return applicationRule;}

    public final KNWorld getWorld() {return world;}

    public KNApplicationInstance() {}
}
