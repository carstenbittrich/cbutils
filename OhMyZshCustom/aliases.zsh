alias ssh='ssh -Y'
alias ll='ls -lhc'
alias la='ls -alhc'
alias less='less -R'
alias root='root -l'
alias pack="tar -pczf"
alias fuck='sudo $(history -p \!\!)'
alias sshproxy='ssh -D 56789'
alias nw='emacs -nw'

setopt auto_cd
alias ...='cd ../..'

source ~/.environment.sh

export EDITOR="vim"

# executables
PATH=/bin:$PATH;
PATH=/opt/local/bin:/opt/local/sbin:/usr/local/python:/usr/local/sbin:$PATH;
PATH=$CBUTILS/bin:$PATH;
PATH=$HOME/bin:$PATH;
export PATH

## python
export PYTHONPATH=$PYTHONPATH:$CBUTILS/python
export PYTHONTEMP=$CBUTILS/python/template.py

## C++
export CPPTEMP=$CBUTILS/templates/cpp

# Add Visual Studio Code (code)
export PATH="$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
