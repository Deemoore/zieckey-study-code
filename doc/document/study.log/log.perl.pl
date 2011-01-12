Perl有三种基本的数据类型：标量（scalar）、数组（array）和散列（hash）。

标量 $
数组 @
散列 %

引用的定义，在变量前面放置一个反斜杠。
$scalarref = \$scalar
$arrayref = \@array
$hashref = \%hash
注意引用都是用一个标量来表示的。


#!/usr/bin/perl -w
$num = 42;
$numref = \$num; #引用构造符"\"是一个一元操作符
$$numref = 6; # $$来访问引用指向的值， 有时候需要加上大括号 ${$numref}
print "num = $num\n";
print "numref = ${ $numref }\n";



箭头操作符“->”
#!/usr/bin/perl -w

%hash = ( '1'=>"Jane", '2'=>"John" );#定义哈希表变量
$hashref = \%hash; #定义一个引用，指向hash
$value = $hashref->{ '1' };#通过引用操作hash
print $value;
print "\n";


正则表达式操作符 =~  !~
#!/usr/bin/perl -w
$text = "hello, this is Jane. Thank you.\n";
$patten = "Jane";

# 查找
print "Found $patten\n" if $text =~ /$patten/;

#查找到之后就替换
print "Found and repalce, " if $text =~ s/$patten/John/;
print $text;



函数传递引用：
my $a = 10;
print "before chg_ref: a = $a\n";
chg_ref( \$a );
print "after chg_ref: a = $a\n";

sub chg_ref
{
    my( $ref ) = @_;
    $$ref++;
}