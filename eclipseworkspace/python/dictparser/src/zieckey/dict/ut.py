'''
Created on 2011-11-19

@author: Administrator
'''

import time 
import urllib
import string
import os
import sys 

def test_list():
    l = [ 0, 1]
    l[0] = 100
    l[1] = 101
    
    print l
    
def crawl_words(input_words_file):
    file_base_path = os.path.basename(input_words_file)
    output_dir = './original_youdao_html/%s' % file_base_path
    try:
        os.mkdir(output_dir)
    except:
        pass

    f = open(input_words_file, 'r')
    while True:
        wordname = string.strip(f.readline())
        if len(wordname) == 0:
            continue

        url = 'http://dict.youdao.com/search?q=%s&ue=utf8' % wordname 
        sock = urllib.urlopen(url)
        htmlSource = sock.read()
        sock.close()
        
        f1 = open(output_dir + '/' + wordname + '.html', 'w+')
        f1.write(htmlSource)
        f1.close()
        
        print wordname + " done."
        time.sleep(0.2)
        
    f.close();
    
if __name__ == '__main__':
    #crawl_words('test_data/gre_one_word_one_line.txt')
    if len(sys.argv) != 2:
        print 'Usage : %s word_list_file\n' % sys.argv[0];
        sys.exit(1)

    crawl_words(sys.argv[1])


