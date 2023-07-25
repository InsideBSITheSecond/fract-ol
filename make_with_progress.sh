#!/bin/bash

# Run 'make' with progress bar
make "$@" 2>&1 | pv -p -t -e -s $(make -n "$@" | wc -l) > /dev/null