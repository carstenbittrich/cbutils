autoload -Uz git-prompt
autoload colors

SEGMENT_SEPARATOR=$'\ue0b0'

BKG1=006
FG1=yellow
BKG2=006
FG2=yellow
BKG3=003
FG3=black

# Default values for the appearance of the prompt.
ZSH_THEME_GIT_PROMPT_PREFIX="%{$reset_color%}%{$BG[$BKG3]%}%{$FG[$BKG2]%}$SEGMENT_SEPARATOR%{$fg[$FG3]%} on %{$reset_color%}%{$BG[$BKG3]%}"
ZSH_THEME_GIT_PROMPT_SUFFIX=""
ZSH_THEME_GIT_PROMPT_SEPARATOR="%{$BG[$BKG3]%} %{$reset_color%}%{$FG[$BKG3]%}$SEGMENT_SEPARATOR%{$reset_color%} "
ZSH_THEME_GIT_PROMPT_BRANCH="%{$fg_bold[$FG3]%}"
ZSH_THEME_GIT_PROMPT_STAGED="%{$fg[green]%}%{✚%G%}"
ZSH_THEME_GIT_PROMPT_CONFLICTS="%{$fg[red]%}%{≠%G%}"
ZSH_THEME_GIT_PROMPT_CHANGED="%{$fg[yellow]%}%{✖%G%}"
ZSH_THEME_GIT_PROMPT_BEHIND="%{↓%G%}"
ZSH_THEME_GIT_PROMPT_AHEAD="%{↑%G%}"
ZSH_THEME_GIT_PROMPT_UNTRACKED=""
ZSH_THEME_GIT_PROMPT_CLEAN=""
ZSH_THEME_GIT_PROMPT_NOGIT="%{$reset_color%}%{$FG[$BKG2]%}$SEGMENT_SEPARATOR%{$reset_color%}"
ZSH_THEME_GIT_PROMPT_CACHE="yes"

# zsh knows black, red, green, yellow, blue, magenta, cyan and white
# PROMPT=$'%{$fg_bold[green]%}%D{[%H:%M:%S]} %{$reset_color%}at %{$fg_bold[white]%}%~%{$reset_color%} $(git_super_status)\
# %(?:%{%{$white%}%}:%{$fg_bold[red]%})❯❯❯%{$reset_color%} '
PROMPT=$'%{$BG[$BKG1]%}%{$fg[$FG1]%}%D{[%H:%M:%S]}%{$reset_color%}%{$BG[$BKG2]%}%{$FG[$BKG1]%}$SEGMENT_SEPARATOR%{$fg[$FG2]%} at %{$fg_bold[$FG2]%}%{$FG[011]%}%~ %{$reset_color%}$(git_super_status)\
%(?:%{%{$white%}%}:%{$fg_bold[red]%})❯❯❯%{$reset_color%} '

RPROMPT=''