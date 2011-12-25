#!/usr/bin/perl

open F, "tmp123" or die "can't read file: $!";
binmode F;
$/=\1;
$i=0;
$z=0;
while(<F>)
{
	$a=$_;
	$i++;
	while($a eq chr(hex("55")))
	{
		$a=<F>;
		$i++;
		if($a eq chr(hex("aa")))
		{
			print $i, "\n";
			$l=$i if($i > 511);
		}
		if($l>511)
		{
			$a[$z] = $l;
			++$z;
		}
	}
}

close F;


for(@a)
{
	$l = $_;	

	open F, "tmp123" or die "can't read file: $!";
	binmode F;

	$d = $l - 512;

	while($d>0)
	{
		$d--;
		$_=<F>;
	}

	open W, ">bin123".$l or die "can't write file: $!";
	binmode W;
	$\="";
	$d=512;
	while($d>0)
	{
		$d--;
		$_=<F>;
		print W $_;
	}
	close W;
	close F;
}
