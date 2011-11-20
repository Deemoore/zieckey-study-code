# coding=utf-8

'''
Created on 2011-11-19

@author: weizili
'''
from xml.dom import minidom
from xml.etree import ElementTree
    
class Word:
    def __init__(self):
        self._name = ''
        self._phonetic = [ '', '' ] #first is British, second is US pronunciation
        self._meaning = [] #
        self._sentence = [] #('This is a English example.', '这是一个英语例子')
        self._synonym = [] #同义词
        self._antonym = [] #反义词
        self._additional = [] #动词的过去式等
        
    def to_string(self):
        s = self._name + '\t' + self._phonetic[0] + '\t' + self._phonetic[1] + '\n'
        for m in self._meaning:
            s += m + '\n'
        
        if len(self._synonym) > 0:
            s += "同义词： "
            for m in self._synonym:
                s += m + '\t'
            s += '\n'
            
        if len(self._antonym) > 0:
            s += '反义词： '
            for m in self._antonym:
                s += m + ', '
            s += '\n'
        
        if len(self._additional) > 0:
            for m in self._antonym:
                s += m + ', '
            s += '\n'
            
        if len(self._sentence) > 0:    
            s += '例句： \n'
            for (o, t) in self._sentence:
                s += '\t' + o + " " + t + '\n'
                
        return s
    
    def to_youdao_dict_xml(self):
        xmldoc = minidom.getDOMImplementation()
        wordbook = xmldoc.createElement('wordbook')
        word = wordbook.appendChild('word')
        word.appencChild()
        
    def to_xml_element(self):
        item = ElementTree.Element('item')
        word = ElementTree.SubElement('word')
        word.text = self._name
        
        trans = ElementTree.SubElement('trans')
        meaning = ''
        for m in self._meaning:
            if len(meaning) == 0:
                meaning = m
            else:
                meaning = '\n' + m
        trans.text = '<![CDATA[%s]]>' % meaning
        
        phonetic = ElementTree.SubElement('phonetic')
        phonetic.text = '<![CDATA[%s %s]]>' % (self._phonetic[0], self._phonetic[1])
          
#        nameE.text = name  
#        sexE = ElementTree.SubElement(personE, 'sex')  
#        if sex == '0':  
#            sexE.text = '男'  
#        elif sex == '1':  
#            sexE.text = '女'  
#        mobileE = ElementTree.SubElement(personE, 'mobile')  
#        mobileE.text = mobile  
#        rough_string = ElementTree.tostring(root, 'utf-8')  
#        reparsed = minidom.parseString(rough_string)  
#        return reparsed.toprettyxml(indent="  " , encoding="utf-8"); 
        
    def set_name(self, name):
        self._name = name
    
    def set_british_phonetic(self, phonetic):
        self._phonetic[0] = phonetic
    
    def set_us_phonetic(self, phonetic):
        self._phonetic[1] = phonetic
            
    def add_meaning(self, meaning):
        self._meaning.append(meaning)
    
    def add_sentence(self, sentence, translation):
        self._sentence.append((sentence, translation))
        
    def add_synonym(self, synonym):
        self._synonym.append(synonym)
    
    def add_anonym(self, anonym):
        self._anonym.append(anonym)
        
    def add_additional(self, additional):
        self._additional.append(additional)