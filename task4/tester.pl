
print "Begin testing...\n\n";

for(8..12)
{
	$s=$_;
	print "-------------------------------------------\nSize: $s\n";
	for(2..6)
	{
		$st = $_;
		print "\tSize T: $st\n";
		open F, ">main.h";
		print F "const int size = $s;\nconst int sT = $st;";
		close F;

		`make`;
		
		print "\tT:";
		print `time ./main`;
		print "\tR:";
		print `time ./main 2`;
		print "\n";
	}
}
