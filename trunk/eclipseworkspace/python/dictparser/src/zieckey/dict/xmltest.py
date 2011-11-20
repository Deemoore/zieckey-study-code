# -*- coding:UTF-8 -*-  

'''
Created on 2011-11-20

@author: Administrator
'''

from xml.dom import minidom

from xml.etree import ElementTree

def test_xml(input_file):
    
    xmldoc = minidom.parse(input_file)
    root = xmldoc.documentElement
    
    f = open('test_data/gre_one_word_one_line.txt', 'w+')
    
    for node in root.getElementsByTagName('word'):
        c = node.firstChild
        if c != None:
            print c.data
            f.write(c.data + '\n')
            
        
        
# -*- coding:UTF-8 -*-  
  
class Person(object):  
    '''  
    联系人：姓名，性别(0:男，1:女)，手机  
    '''  
    name = None  
    sex = None  
    mobile = None  
      
  
    def __init__(self,name,sex,mobile):  
          
        self.name = name  
        self.sex = sex  
        self.mobile = mobile  
      
    def setName(self,name):  
        self.name = name  
      
    def setSex(self,sex):  
        self.sex = sex  
      
    def setMobile(self,mobile):  
        self.mobile = mobile  
          
          
def personToXML(person):  
        '''将Person对象转换成xml格式的数据'''  
        name = person.name  
        sex = person.sex  
        mobile = person.mobile  
        root = ElementTree.Element('personList')  
        personE = ElementTree.SubElement(root, 'person')  
        nameE = ElementTree.SubElement(personE, 'name')  
        nameE.text = name  
        sexE = ElementTree.SubElement(personE, 'sex')  
        if sex == '0':  
            sexE.text = '男'  
        elif sex == '1':  
            sexE.text = '女'  
        mobileE = ElementTree.SubElement(personE, 'mobile')  
        mobileE.text = mobile  
        rough_string = ElementTree.tostring(root, 'utf-8')  
        reparsed = minidom.parseString(rough_string)  
        return reparsed.toprettyxml(indent="  " , encoding="utf-8");
        

if __name__ == '__main__':
    #test_xml('test_data/gre.xml')
    person = Person('janny', '1', '15801463655')
    print personToXML(person)
