# Report CPU usage for commands running longer than 10 seconds
REPORTTIME=10

# switch off suggested corrections
unsetopt correct_all

# [Alt+UpArrow] - Insert last word of previous command
bindkey '^[[A' insert-last-word
bindkey '^[[1;3A' insert-last-word
# [Alt+'] - quote full line
bindkey 'æ' quote-line
# [Alt+/] - commment/uncomment full line
bindkey '÷' pound-insert

# get those string combinations by running cat and entering desired key combination