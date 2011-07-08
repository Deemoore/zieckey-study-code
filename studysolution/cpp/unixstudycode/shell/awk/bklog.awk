awk '{print $4}' bklog | awk -F= '{ if($2>0 && $2<1000000) printf "%s,",$2}' > ops.cvs
