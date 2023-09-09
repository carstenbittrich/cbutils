#!/bin/zsh

# this script reads in configurations of some common applications and stores them in repo
#
# content:
# - Moom
# - Terminal


# Moom
if [ -e ~/Library/Application\ Support/Many\ Tricks ]
then
    if [ -e $CBUTILS/OtherSettings/Moom.plist ]
    then
        rm $CBUTILS/OtherSettings/Moom.plist
    fi
    defaults export com.manytricks.Moom $CBUTILS/OtherSettings/Moom.plist
    # apply with `defaults import ...`
fi

# Terminal
if [ -e $CBUTILS/OtherSettings/com.apple.Terminal.plist ]
then
    rm $CBUTILS/OtherSettings/com.apple.Terminal.plist
fi
cp ~/Library/Preferences/com.apple.Terminal.plist $CBUTILS/OtherSettings/com.apple.Terminal.plist
# apply by copying back

# Terminal
if [ -e $CBUTILS/lists/code-extensions.txt ]
then
    rm $CBUTILS/lists/code-extensions.txt
fi
code --list-extensions > $CBUTILS/lists/code-extensions.txt