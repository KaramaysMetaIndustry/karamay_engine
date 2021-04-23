package com.groovy.script

import groovy.xml.XmlParser
import groovy.xml.XmlSlurper
import groovy.xml.slurpersupport.GPathResult

def str = '''
    <kanas>
        <button>
            <text>Groovy</text>
        </button>
    </kanas>
'''

def kanas = new XmlSlurper().parseText(str)
assert kanas instanceof GPathResult
assert kanas.button.text == 'Groovy'

def Test()
{
    print("Test")
}

def handleXML()
{
    def langs = new XmlParser().parse("scripts/languages.xml")
    println "type = ${langs.attribute("type")}"

    langs.language.each{
        println it.text()
    }


    def parser = new XmlParser();
    def doc = parser.parse("scripts/languages.xml")

    doc.Kanas.each{

    }

}

//handleXML();


def createPluginTemplateDir(String name)
{
    def outerLoop = ['one', 'two', 'three', 'four']
    def innerLoop = ['a', 'b']

    def out = new StringWriter()
    def xml = new groovy.xml.MarkupBuilder(out)

    def friendList  =  [ ' Tony ' ,  ' Alan ' ,  ' Leona ' ,  ' Cloudy ' ,  ' terry ' ]

    xml.Kanas {
        Button(type: "primary" , " 按钮0 " )
        Button(type: "warning", "按钮1 ")
        ViewList(num: friendList.size()) {
            for  (f in friendList) {
                Row(f)
            }
        }
    }

    def dir = new File("scripts/"+name).mkdirs()
    def file = new File("scripts/"+name+"/"+name+".xml")
    def fileScript = new File("scripts/"+name+"/"+name+".groovy")

    def xmlString = """<?xml version='1.0' encoding='UTF-8'?>""";
    file.write(xmlString.toString() +"\n"+ out.toString())
    fileScript.write("def tick(float DeltaTime){}")
}

createPluginTemplateDir("Maker")












