#!/usr/bin/awk -f
# $FreeBSD: stable/9/usr.bin/getconf/fake-gperf.awk 119312 2003-08-22 17:32:07Z markm $
BEGIN {
  state = 0;
  struct_seen = "";
}
/^%{$/ && state == 0 {
  state = 1;
  next;
}
/^%}$/ && state == 1 {
  state = 0;
  next;
}
state == 1 { print; next; }
/^struct/ && state == 0 {
  print;
  struct_seen = $2;
  next;
}
/^%%$/ && state == 0 {
  state = 2;
  if (struct_seen !~ /^$/) {
    print "static const struct", struct_seen, "wordlist[] = {";
  } else {
    print "static const struct map {";
    print "\tconst char *name;";
    print "\tint key;";
    print "\tint valid;";
    print "} wordlist[] = {";
    struct_seen = "map";
  }
  next;
}
/^%%$/ && state == 2 {
  state = 3;
  print "\t{ NULL, 0, 0 }";
  print "};";
  print "#define\tNWORDS\t(sizeof(wordlist)/sizeof(wordlist[0]) - 1)";
  print "static const struct map *";
  print "in_word_set(const char *word)";
  print "{";
  print "\tconst struct", struct_seen, "*mp;";
  print "";
  print "\tfor (mp = wordlist; mp < &wordlist[NWORDS]; mp++) {";
  print "\t\tif (strcmp(word, mp->name) == 0)";
  print "\t\t\treturn (mp);";
  print "\t}";
  print "\treturn (NULL);";
  print "}";
  print "";
  next;
}
state == 2 && NF == 2 {
  name = substr($1, 1, length($1) - 1);
  printf "#ifdef %s\n", $2;
  printf "\t{ \"%s\", %s, 1 },\n", name, $2;
  print "#else";
  printf "\t{ \"%s\", 0, 0 },\n", name, $2;
  print "#endif"
  next;
}
state == 3 { print; next; }
{
				# eat anything not matched.
}
