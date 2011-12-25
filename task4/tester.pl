
print "Begin testing...\n\n";

for(8..12)
{
	$s=$_;
	print "-------------------------------------------\nSize: $s\n";

	open F, ">main.h";
        print F "const int size = $s;\nconst int sT = 0;";
        close F;

	`make`;
	print "\tR:";
        print `time ./main 2`;
	print "\n";
	for(2..6)
	{
		$st = $_;
		open F, ">main.h";
		print F "const int size = $s;\nconst int sT = $st;";
		close F;

		`make`;
		
		print "\tT=$st:";
		print `time ./main`;
		print "\n";
	}
}
