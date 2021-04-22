package com.groovy.entity

interface Behaviour {

    def initialize();

    def tick(float deltaTime);

    def end();

}