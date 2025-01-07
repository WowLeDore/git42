#!/bin/bash
sed "s/:.*//" /etc/passwd | sed -n "n;p" | rev | sort -r | sed "s/\$/,/" | paste -sd" " | cut -f "$FT_LINE1"-"$FT_LINE2" -d" " | sed "s/,$/./" | tr -d "\n"
