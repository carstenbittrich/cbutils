autoload -Uz git-prompt
autoload colors

# Default values for the appearance of the prompt.
ZSH_THEME_GIT_PROMPT_PREFIX="on "
ZSH_THEME_GIT_PROMPT_SUFFIX=""
ZSH_THEME_GIT_PROMPT_SEPARATOR=" "
ZSH_THEME_GIT_PROMPT_BRANCH="%{$fg_bold[white]%}"
ZSH_THEME_GIT_PROMPT_STAGED="%{$fg[green]%}%{✚%G%}"
ZSH_THEME_GIT_PROMPT_CONFLICTS="%{$fg[red]%}%{≠%G%}"
ZSH_THEME_GIT_PROMPT_CHANGED="%{$fg[yellow]%}%{✖%G%}"
ZSH_THEME_GIT_PROMPT_BEHIND="%{↓%G%}"
ZSH_THEME_GIT_PROMPT_AHEAD="%{↑%G%}"
ZSH_THEME_GIT_PROMPT_UNTRACKED=""
ZSH_THEME_GIT_PROMPT_CLEAN=""

# zsh knows black, red, green, yellow, blue, magenta, cyan and white
PROMPT=$'%{$fg_bold[green]%}%D{[%H:%M:%S]} %{$reset_color%}at %{$fg_bold[white]%}%~%{$reset_color%} $(git_super_status)\
%(?:%{%{$white%}%}:%{$fg_bold[red]%})❯❯❯%{$reset_color%} '
# PROMPT=$'%{$BG[010]%}%{$FG[000]%}%D{[%H:%M:%S]}%{$reset_color%} at %{$fg_bold[white]%}%~ %{$reset_color%}$(git_super_status)\
# %(?:%{%{$white%}%}:%{$fg_bold[red]%})❯❯❯%{$reset_color%} '

RPROMPT=''