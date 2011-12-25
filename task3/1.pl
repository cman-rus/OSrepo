#!/usr/bin/perl
$\='';
eval("use String::CRC32;");
die ("no String::CRC32 module was found. Please install it.") if $@;

open F, "<", $ARGV[0];
binmode F;
$/=\1;
$l=0;
$file = '';
while(<F>)
{
	++$l;
	$file .= $_;
}

$crc = crc32($file);
print "Length: ", $l, "\n";
printf("%02x\n", $l);
print "CRC32: 0x";
printf("%02x\n", $crc);

if($l > 512 * 16)
{
	print "ERROR!! big file! \n";
}

close F;

# длина

# первый байт
$l1= $l & 0xFF;
# второй байт
$l2 = ($l >> 8) & 0xFF;
# третий байт
$l3 = ($l >> 16) & 0xFF;
# четвертый байт
$l4 = ($l >> 24) & 0xFF;
#print $l1, " ", $l2;

#crc

# первый байт
$crc1= $crc & 0xFF;
# второй байт
$crc2 = ($crc >> 8) & 0xFF;
# третий байт
$crc3 = ($crc >> 16) & 0xFF;
# четвертый байт
$crc4 = ($crc >> 24) & 0xFF;


open F, "1";
binmode F;
open O, ">2";
binmode O;
$/=\1;
$i=0;

while(<F>)
{
    if($i==18)
    {
        print O chr(($l%512==0?(int $l/512 ):(int ($l/512) + 1)));
	print ($l%512==0?(int $l/512 ):(int ($l/512) + 1));
	print "\n";
    }
    elsif($i==300)
    {
	# размер
        print O chr($l1);
    }
    elsif($i==301)
    {
	# размер
        print O chr($l2);
    }
    elsif($i==302)
    {
        # размер
        print O chr($l3);
    }
    elsif($i==303)
    {
        # размер
        print O chr($l4);
    }
    elsif($i==304)
    {
        # crc
        print O chr($crc1);
    }
    elsif($i==305)
    {
        # crc
        print O chr($crc2);
    }
    elsif($i==306)
    {
        # crc
        print O chr($crc3);
    }
    elsif($i==307)
    {
        # crc
        print O chr($crc4);
    }
    else
    {
       print O $_;
    }
    ++$i;	
}
close F;

open F, "<", $ARGV[0];
binmode F;
$/=\1;

while(<F>)
{
	print O $_;
}
close F;
$z = $l % 512;
$z = 512 - $z;

for(0..$z)
{
	print O chr(0);
}
close O;
