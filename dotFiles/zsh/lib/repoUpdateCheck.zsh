#!/usr/bin/env zsh

CURDIR=$PWD
if command -v git > /dev/null; then
    cd $CBUTILS
    if [ `git status | grep -c "nothing to commit"` -eq 0 ]; then
        # not up to date
        echo "$CBUTILS has local changes!"
        git status
    fi
    cd $CURDIR
fi
