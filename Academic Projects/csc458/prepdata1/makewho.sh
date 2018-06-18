#!/bin/bash

for userid in `who | cut -d" " -f1`
do
    # Look at what everyone on a terminal + root (superuser) are running.
    # Send to stdout. Let the makefile redirect to a file.
    echo "ps USER: $userid" >&2
    ps -fu $userid
done
echo "ps USER: root" >&2
ps -fu root
