#!/usr/bin/perl

# Check length of absrev function in .yo file
# Assumes that function starts with label "absrev:"
# and finishes with label "End:"

$startpos = -1;
$endpos = -1;

while (<>) {
  $line = $_;
  if ($line =~ /(0x[0-9a-fA-F]+):.* absrev:/) {
    $startpos = hex($1);
  }
  if ($line =~ /(0x[0-9a-fA-F]+):.* End:/) {
    $endpos = hex($1);
  }
}

if ($startpos >= 0 && $endpos > $startpos) {
  $len = $endpos - $startpos;
  print "absrev length = $len bytes\n";
} else {
  print "Couldn't determine absrev length\n";
}
