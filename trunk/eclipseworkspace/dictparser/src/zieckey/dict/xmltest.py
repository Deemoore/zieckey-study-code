'''
Created on 2011-11-20

@author: Administrator
'''

from xml.dom import minidom


def test_xml(input_file):
    
    xmldoc = minidom.parse(input_file)
    root = xmldoc.documentElement
    
    f = open('test_data/gre_one_word_one_line.txt', 'w+')
    
    for node in root.getElementsByTagName('word'):
        c = node.firstChild
        if c != None:
            print c.data
            f.write(c.data + '\n')
            
        
if __name__ == '__main__':
    test_xml('test_data/gre.xml')
    #test_xml('test_data/study.xml')
