#!/usr/bin/perl

# answer to https://stackoverflow.com/questions/50528383/how-to-append-sort-multiple-set-of-lines-from-multiple-files-to-result-file-us
# run with ./logpat.pl A.txt B.txt > C.txt

my @input = @ARGV;

my @blocks = ();

foreach my $logfile (@input) {
    open(my $f, "<$logfile") or die($!);
    my $state = 0;

    my $cblock = '';
    while(my $x = <$f>) {

	#print "[$x] [c=$cblock] state=$state\n";
	next unless ($x =~ /^\d{2}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}\s+/);
	
	if ($state == 0) {
        # outside any block
	    if ($x =~ /\s+##Start/) {
		$cblock = $x;
		$state = 1;
		next;
	    }
	} elsif ($state == 1) {
        #inside a block, no correct tag yet, waiting for ABC123 or the end tag
	    if ($x =~ /\s+Unique ID - ABC123$/) {
		$state = 2;
		$cblock .= $x;
		next;
	    } elsif ($x =~ /\s+##End/) {
		# discard, go back to state 0
		$cblock = '';
		$state = 0;
		next;
	    }
	} elsif ($state == 2) {
	    #inside a wanted block, waiting for the end tag
	    $cblock .= $x;
	    if ($x =~ /\s+##End/) {
		#print "push=[$cblock]\n";
		# push this block
		push @blocks, $cblock;
		$cblock = '';
		$state = 0;
		next;
	    }
	    
	}
    } # while $_ = <f>
    close($f);
} # for @input


my @sorted = sort { $a cmp $b } @blocks;

foreach my $x (@sorted) {
    print $x;
}


