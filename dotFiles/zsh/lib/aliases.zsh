alias ssh='ssh -Y'
alias ls='ls --color'
alias ll='ls -lhc'
alias la='ls -alhc'
alias less='less -R'
alias root='root -l'
alias pack="tar -pczf"
alias clang++='clang++ -std=c++11'
alias fuck='sudo $(history -p \!\!)'
alias sshproxy='ssh -D 56789'

alias ...='cd ../..'
export IKTPWEB=iktpcopy:public_html
export EDITOR="vim"

# executables
PATH=/bin:$PATH;
PATH=/opt/local/bin:/opt/local/sbin:/usr/local/python:$PATH;
PATH=$CBUTILS/bin:$PATH;
PATH=$HOME/bin:$PATH;
export PATH

## python
export PYTHONPATH=$PYTHONPATH:$CBUTILS/python
export PYTHONTEMP=$CBUTILS/python/template.py
