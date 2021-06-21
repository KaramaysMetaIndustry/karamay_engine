package com.pb.framework.nebula.world;

import com.pb.framework.nebula.graphics.scene.KNScene;
import com.pb.framework.nebula.rule.KNWorldRule;

import java.util.ArrayList;

public class KNWorld {

    protected KNWorldRule worldRule;

    private ArrayList<KNScene> scenes;


    protected KNWorldOnTick onTick;

    protected KNWorldPostTick postTick;


    /***/
    public final void tick(float deltaTime)
    {
        if(onTick != null)
            onTick.execute(deltaTime);

        if(postTick != null)
            postTick.execute(deltaTime);
    }

    public void addScene(KNScene scene)
    {
        if(scene != null){
            scenes.add(scene);
        }
    }

    public void removeScene(KNScene scene)
    {
        if(scene != null){
            scenes.remove(scene);
        }
    }

}
