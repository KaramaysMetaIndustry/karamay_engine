package com.pb.core.graphics.pipeline;

import com.pb.core.graphics.transformfeedback.TransformFeedback;
import com.pb.core.graphics.uniform.Uniform;
import com.pb.core.graphics.vertex.VertexArray;
import com.pb.core.graphics.buffer.AtomicCounterBuffer;
import com.pb.core.graphics.buffer.ElementArrayBuffer;
import com.pb.core.graphics.buffer.ShaderStorageBuffer;
import com.pb.core.graphics.buffer.UniformBuffer;
import com.pb.core.graphics.framebuffer.Framebuffer;

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
