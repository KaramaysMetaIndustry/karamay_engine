package com.core.graphics;

import java.util.ArrayList;

public class Pipeline {

    public native Pipeline setShaders(ArrayList<String> shaderPaths);

    public native Pipeline setVertexArray(VertexArray vertexArray );

    public native Pipeline setElementArrayBuffer(ElementArrayBuffer elementArrayBuffer);

    public native Pipeline setTransformFeedback(TransformFeedback transformFeedback);

    public native Pipeline addUniformBuffers(ArrayList<UniformBuffer> uniformBuffers);

    public native Pipeline addShaderStorageBuffers(ArrayList<ShaderStorageBuffer> shaderStorageBuffers);

    public native Pipeline addAtomicCounterBuffers(ArrayList<AtomicCounterBuffer> atomicCounterBuffers);

    public native Pipeline addUniforms(ArrayList<Uniform> uniforms);

    public native Pipeline addTextures();

    public native Pipeline setFramebuffer();

    public native Pipeline setFramebuffer(Framebuffer framebuffer);

}
