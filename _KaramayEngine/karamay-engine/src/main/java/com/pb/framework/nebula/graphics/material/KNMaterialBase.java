package com.pb.framework.nebula.graphics.material;

import com.pb.framework.nebula.graphics.texture.KNTexture2D;

public class KNMaterialBase {

    private KNTexture2D emissiveColorMap;

    private KNTexture2D normalMap;

    private KNTexture2D tangentMap;

    private KNTexture2D heightMap;

    private float heightMapScalar;

    private KNTexture2D ambientOcclusionMap;

    private KNTexture2D subsurfaceColorMap;

    private float Refraction;

    private float Opacity;


    public KNTexture2D getEmissiveColorMap() {
        return emissiveColorMap;
    }

    public void setEmissiveColorMap(KNTexture2D emissiveColorMap) {
        this.emissiveColorMap = emissiveColorMap;
    }

    public KNTexture2D getNormalMap() {
        return normalMap;
    }

    public void setNormalMap(KNTexture2D normalMap) {
        this.normalMap = normalMap;
    }

    public KNTexture2D getTangentMap() {
        return tangentMap;
    }

    public void setTangentMap(KNTexture2D tangentMap) {
        this.tangentMap = tangentMap;
    }

    public KNTexture2D getHeightMap() {
        return heightMap;
    }

    public void setHeightMap(KNTexture2D heightMap) {
        this.heightMap = heightMap;
    }

    public KNTexture2D getAmbientOcclusionMap() {
        return ambientOcclusionMap;
    }

    public void setAmbientOcclusionMap(KNTexture2D ambientOcclusionMap) {
        this.ambientOcclusionMap = ambientOcclusionMap;
    }

    public KNTexture2D getSubsurfaceColorMap() {
        return subsurfaceColorMap;
    }

    public void setSubsurfaceColorMap(KNTexture2D subsurfaceColorMap) {
        this.subsurfaceColorMap = subsurfaceColorMap;
    }

    public float getRefraction() {
        return Refraction;
    }

    public void setRefraction(float refraction) {
        Refraction = refraction;
    }

    public float getOpacity() {
        return Opacity;
    }

    public void setOpacity(float opacity) {
        Opacity = opacity;
    }
}
