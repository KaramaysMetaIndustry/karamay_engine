package com.core.graphics;

import com.core.graphics.buffer.AtomicCounterBuffer;
import com.core.graphics.buffer.ElementArrayBuffer;
import com.core.graphics.buffer.ShaderStorageBuffer;
import com.core.graphics.buffer.UniformBuffer;
import com.core.graphics.pipeline.Pipeline;
import com.core.graphics.transformfeedback.TransformFeedback;
import com.core.graphics.uniform.Uniform;
import com.core.graphics.vertex.VertexArray;
import com.core.graphics.vertex.VertexAttributeLayout;

import java.nio.ByteBuffer;
import java.util.ArrayList;

public class Renderer {


    public void construct()
    {
        ArrayList<String> shaderPaths = new ArrayList<>();
        shaderPaths.add("shaders/pbrmesh.vert");
        shaderPaths.add("shaders/pbrmesh.tesc");
        shaderPaths.add("shaders/pbrmesh.tese");
        shaderPaths.add("shaders/pbrmesh.geom");
        shaderPaths.add("shaders/pbrmesh.frag");

        ByteBuffer byteBuffer = ByteBuffer.allocate(100);
        byteBuffer.array();
        byteBuffer.capacity();

        VertexArray vertexArray
                = new VertexArray(new VertexAttributeLayout(), byteBuffer.array(), byteBuffer.capacity());

        ElementArrayBuffer elementArrayBuffer
                = new ElementArrayBuffer();

        TransformFeedback transformFeedback
                = new TransformFeedback();

        ArrayList<Uniform> uniforms = new ArrayList<>();
        ArrayList<UniformBuffer> uniformBuffers = new ArrayList<>();
        ArrayList<ShaderStorageBuffer> shaderStorageBuffers = new ArrayList<>();
        ArrayList<AtomicCounterBuffer> atomicCounterBuffers = new ArrayList<>();



        Pipeline pipeline = new Pipeline();
        pipeline.setShaders(shaderPaths)
                .setVertexArray(vertexArray)
                .setElementArrayBuffer(elementArrayBuffer)
                .setTransformFeedback(transformFeedback)
                .addUniforms(uniforms)
                .addUniformBuffers(uniformBuffers)
                .addShaderStorageBuffers(shaderStorageBuffers)
                .addAtomicCounterBuffers(atomicCounterBuffers)
                .setFramebuffer();

    }

}
