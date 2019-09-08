#!/bin/sh

sort | uniq -c | sort -n -r | awk '{print $2; exit}'
