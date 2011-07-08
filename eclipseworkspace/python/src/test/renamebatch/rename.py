'''
Created on 2011-6-29

rename file

@author: weizili
'''

import os;

if __name__ == '__main__':
#    dirpath = "E:/zieckey.doc/english/english/U.S.popularlanguagelectures/1-99";
#    if os.path.exists(dirpath) == False :
#        print( dirpath + " not exists." );
#    else:
#        print( "begin to rename:" );
#        for i in range(1, 10):
#            file = dirpath + "/pa0" + str(i) + ".mp3";
#            newname = dirpath + "/pa00" + str(i) + ".mp3";
#            if os.path.exists(file) and False == os.path.exists(newname):
#                print( "rename '" + file + "' to '" + newname + "'" );
#                os.rename(file, newname );
#            else :
#                print( "rename failed : '" + file + "' to '" + newname + "'" );
                
                
    dirpath = "E:/zieckey.doc/english/english/NCE3-word";
    if os.path.exists(dirpath) == False :
        print( dirpath + " not exists." );
    else:
        print( "begin to rename:" );
        for i in range(1, 10):
            file = dirpath + "/30" + str(i) + ".mp3";
            newname = dirpath + "/nce3-0" + str(i) + ".mp3";
            if os.path.exists(file) and False == os.path.exists(newname):
                print( "rename '" + file + "' to '" + newname + "'" );
                os.rename(file, newname );
            else :
                print( "rename failed : '" + file + "' to '" + newname + "'" );
                
        for i in range(10, 60):
            file = dirpath + "/3" + str(i) + ".mp3";
            newname = dirpath + "/nce3-" + str(i) + ".mp3";
            if os.path.exists(file) and False == os.path.exists(newname):
                print( "rename '" + file + "' to '" + newname + "'" );
                os.rename(file, newname );
            else :
                print( "rename failed : '" + file + "' to '" + newname + "'" );                