%module pair
%{
#include "pair.h"
%}

// Ignore the default constructor
%ignore myn::pair::pair();      

// Parse the original header file
%include "pair.h"

// Instantiate some templates

%template(pairii) myn::pair<int,int>;
%template(pairdi) myn::pair<double,int>;
