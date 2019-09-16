#!/bin/sh

sort | uniq -c | sort -nr | head -n 1 | tr -s " " | cut -s -d " " -f 3

#sort | uniq -c | sort -nr | head -n 1 | tr -s " " | sed 's/\s*[0-9]\+\s\+//'

#sort | uniq -c | sort -nr | awk '{ print $2 ; exit }'

#sort | uniq -c | sort -nr | awk 'NR == 1 { print $2 }'

#sort | uniq -c | sort -nr | awk '{ print $2 ; exit }'

#awk '{
	#if (s[max] < ++s[$1])
		#max = $1
#}
#END {
	#if (s[max])
		#print max
#}
#'

#awk '
#{
	#++s[$1]
#}
#END {
	#for (i in s)
		#print s[i], i
#}
#' | awk '
#max < $1 {
	#max = $1
	#v = $2
#}
#END {
	#if (v)
		#print v
#}
#'

# https://github.com/TheMozg/awk-raycaster
