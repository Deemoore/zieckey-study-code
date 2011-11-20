'''
Created on 2011-11-19

@author: Administrator
'''

import time 
import urllib
import string

def test_list():
    l = [ 0, 1]
    l[0] = 100
    l[1] = 101
    
    print l
    
def crawl_words(input_words_file):
    f = open(input_words_file, 'r')
    while True:
        wordname = string.strip(f.readline())
        if len(wordname) == 0:
            break;
        url = 'http://dict.youdao.com/search?q=%s&ue=utf8' % wordname 
        sock = urllib.urlopen(url)
        htmlSource = sock.read()
        sock.close()
        
        f1 = open('original_word_html/' + wordname + '.html', 'w+')
        f1.write(htmlSource)
        f1.close()
        
        print wordname + " done."
        time.sleep(0.1)
        
    f.close();
    
if __name__ == '__main__':
    #crawl_words('test_data/gre_one_word_one_line.txt')
    crawl_words('test_data/gre_one_word_one_line__need_crawl_again.txt')


