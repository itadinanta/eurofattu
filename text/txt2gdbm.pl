#! /usr/bin/perl
use GDBM_File ;

if ($#ARGV >= 0) {
  $filename_in=$ARGV[0];
  open SOURCE, "< $filename_in" or die "Could not access $filename_in";
  $FILE_IN=SOURCE;
}
else {
  $filename_in="<STDIN>";
  $FILE_IN=STDIN;
}

if ($#ARGV >=1) {
  $filename_out=$ARGV[1];
} else {
  $filename_out="messages.db";
}

print STDERR "$filename_in -> $filename_out\n";

tie %hash, 'GDBM_File', $filename_out, &GDBM_WRCREAT, 0640;

while (<$FILE_IN>) {
  next if /\s*\#.*/;
  if (/\s*(\S*?)\s*=(.*)/) {
    $key=$1;
    $value=$2;chomp($value);
    $hash{$key}=$value;
    print STDERR "$key=\"$value\"\n";
  }
}

untie %hash ;


exit 0;

