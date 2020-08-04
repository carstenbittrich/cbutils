#!/bin/zsh

# this script reads in and applies configurations of some common applications from repo
#
# content:
# - Moom
# - Terminal


# Moom
if [ -e ~/Library/Application\ Support/Many\ Tricks ]
then
    if [ -e $CBUTILS/OtherSettings/Moom.plist ]
    then
        defaults import com.manytricks.Moom $CBUTILS/OtherSettings/Moom.plist
    else
        echo "Could not find settings for Moom"
    fi
fi

# Terminal
if [ -e $CBUTILS/OtherSettings/com.apple.Terminal.plist ]
then
    cp $CBUTILS/OtherSettings/com.apple.Terminal.plist ~/Library/Preferences/com.apple.Terminal.plist
else
    echo "Could not find settings for Terminal"
fi
