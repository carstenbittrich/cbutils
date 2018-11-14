#!/usr/bin/env zsh

CURDIR=$PWD
cd $CBUTILS
if [ `git status | grep -c "nothing to commit"` -eq 0 ]; then
    # not up to date
    echo "$CBUTILS has local changes!"
    git status
fi
cd $CURDIR
