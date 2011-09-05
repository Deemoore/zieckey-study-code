#python 2.5 

class A:
    def __init__( self, s ):
        print "A __init__", s

class B(A):
    def __init__( self, s ):
        A.__init__(self, s)
        print "B __init__", s

class C(B):
    def __init__( self, s ):
        B.__init__(self, s)
        print "C __init__", s


c = C("A string from C")
