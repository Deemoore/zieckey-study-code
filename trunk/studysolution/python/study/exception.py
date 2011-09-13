import os


try:
    raise OSError("test OSError Exception")
    print "after raise exception"
except Exception, e:
    print "catch the exception:", e

print "after try...catch..."    
