package com.framework.taichi.application;

import com.framework.taichi.application.event.KTApplicationOnRun;
import com.framework.taichi.application.event.KTApplicationOnTick;
import com.framework.taichi.application.event.KTApplicationPostRun;
import com.framework.taichi.application.event.KTApplicationPostTick;
import com.framework.taichi.world.KTWorld;

public class KTApplication {

    protected KTWorld world;

    protected KTApplicationOnRun onRun;
    protected KTApplicationPostRun postRun;
    protected KTApplicationOnTick onTick;
    protected KTApplicationPostTick postTick;


    public void initialize()
    {}

    public final void run()
    {
        if(onRun != null) onRun.execute();

        if(postRun != null) postRun.execute();
    }

    public final void tick(float deltaTime)
    {
        if(onTick != null) onTick.execute(deltaTime);

        if(postTick != null) postTick.execute(deltaTime);
    }



}
