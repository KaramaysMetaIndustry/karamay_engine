package com.framework.nebula.graphics.material;

import com.framework.nebula.graphics.texture.KNTexture2D;

/*
* Metallic/Roughness Workflow
* */
public class KNMaterialMR extends KNMaterialBase{

    private KNTexture2D albedoMap; // sRGB non-metal-  metal-

    private KNTexture2D metallicMap; // linear 0 non-metal (0,1] pure-metal

    private KNTexture2D roughnessMap; // linear glossy[0,1]rough

}
