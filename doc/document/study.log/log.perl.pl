Perl�����ֻ������������ͣ�������scalar�������飨array����ɢ�У�hash����

���� $
���� @
ɢ�� %

���õĶ��壬�ڱ���ǰ�����һ����б�ܡ�
$scalarref = \$scalar
$arrayref = \@array
$hashref = \%hash
ע�����ö�����һ����������ʾ�ġ�


#!/usr/bin/perl -w
$num = 42;
$numref = \$num; #���ù����"\"��һ��һԪ������
$$numref = 6; # $$����������ָ���ֵ�� ��ʱ����Ҫ���ϴ����� ${$numref}
print "num = $num\n";
print "numref = ${ $numref }\n";



��ͷ��������->��
#!/usr/bin/perl -w

%hash = ( '1'=>"Jane", '2'=>"John" );#�����ϣ�����
$hashref = \%hash; #����һ�����ã�ָ��hash
$value = $hashref->{ '1' };#ͨ�����ò���hash
print $value;
print "\n";


������ʽ������ =~  !~
#!/usr/bin/perl -w
$text = "hello, this is Jane. Thank you.\n";
$patten = "Jane";

# ����
print "Found $patten\n" if $text =~ /$patten/;

#���ҵ�֮����滻
print "Found and repalce, " if $text =~ s/$patten/John/;
print $text;



�����������ã�
my $a = 10;
print "before chg_ref: a = $a\n";
chg_ref( \$a );
print "after chg_ref: a = $a\n";

sub chg_ref
{
    my( $ref ) = @_;
    $$ref++;
}