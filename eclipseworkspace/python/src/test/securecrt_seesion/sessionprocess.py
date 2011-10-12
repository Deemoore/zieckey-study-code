'''
Created on 2011-10-12

@author: weizili
'''

g_templete_file = 'templete.ini'
g_templete_hostname = 'build7.kill.corp.qihoo.net'


#modify there three parameters
g_leading = 'kill'
g_host = '.safe.zwt.qihoo.net'
g_numbers = range(16,25)

def readfile(path):
    fh = open(path, encoding='utf-8')
    content = fh.read()
    fh.close()
    return content

def writefile(path, data):
    fh = open(path, mode='w', encoding='utf-8')
    fh.write(data)
    fh.close()

if __name__ == '__main__':
    
    content = readfile(g_templete_file)    
    
    for n in g_numbers:
        name = g_leading + str(n) + g_host
        newcontent = content.replace(g_templete_hostname, name)
        writefile(name + '.ini', newcontent)
    
    print('OK')
    