#!/usr/bin/env bash

CURDIR=$PWD

# helper function
function install_brew_list() {
    
    while read line
    do
        name=`echo $line | cut -d " " -f 1`
        if [ `grep -c -e "^$name$" lists/brew-installed-list.txt` -ne 1 ]
        then
            echo "install $name"
            if [[ ${1} =~ cask ]]
            then
                brew install cask $name
            else
                brew install $name
            fi
        fi
    done < ${1}
}

if [ `uname` == "Darwin" ] # mac OS
then
    # check os version:
    # sw_vers -productVersion
    
    
    if [ ! -e `xcrun --show-sdk-path`/usr/include ]
    then
        read -p "Install command line tools? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            xcode-select --install
            # also remember to add this line to shell config ($CBUTILS/dotFiles/environment.sh):
            # export CPATH=`xcrun --show-sdk-path`/usr/include
            # this was an alternative in mojave:
            # sudo open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg
        fi
    fi
    
    # set up brew
    if [ ! -e "/usr/local/bin/brew" ]
    then
        read -p "Install homebrew? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            export DOBREW=1
            /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
        else
            unset DOBREW
        fi
        brew list > lists/brew-installed-list.txt
    else
        export DOBREW=1
    fi
    
    if [ $DOBREW ]
    then
        read -p "Install homebrew packages from lists/brew-packages.txt? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            install_brew_list lists/brew-packages.txt
        fi
        read -p "Install homebrew packages from lists/brew-packages_full.txt? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            install_brew_list lists/brew-packages_full.txt
        fi
        
        read -p "Install python2 from homebrew? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            brew install https://raw.githubusercontent.com/Homebrew/homebrew-core/86a44a0a552c673a05f11018459c9f5faae3becc/Formula/python@2.rb
        fi
        
        # install missing casks
        read -p "Install brew casks from lists/brew-casks? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            install_brew_list lists/brew-casks.txt
        fi
        read -p "Install brew casks from lists/brew-casks_full? [yY/?]" -n 1 -r
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            install_brew_list lists/brew-casks_full.txt
        fi
    fi
fi

# check if zsh shell available
if [ ! `command -v zsh` ]
then
    if [ `uname` == "Darwin" ]
    then
        echo "Installing zsh"
        brew install zsh
        DIDZSH=1
    else
        unset DIDZSH
    fi
    # TODO: what if zsh is not available on system without admin rights?
else
    DIDZSH=1
fi

# set shell to zsh
if [ `command -v zsh` ]
then
    if [ `basename $SHELL` != "zsh" ]
    then
        echo "Setting shell to zsh"
        chsh -s /bin/zsh || echo "... not successful"
    fi
else
    echo "zsh not available, using fallback bash"
fi

read -p "Install Oh-My-Zsh? [yY/?]" -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    if [ ! -e $HOME/.oh-my-zsh ]
    then
        sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    fi
    if [ ! -L $ZSH/custom ]
    then
        rm -rf $ZSH/custom
        ln -s $PWD/OhMyZshCustom $ZSH/custom
    fi
    
    if [ ! -e OhMyZshCustom/plugins/zsh-autosuggestions ]
    then
        git clone https://github.com/zsh-users/zsh-autosuggestions OhMyZshCustom/plugins/zsh-autosuggestions
    fi
fi

if [ `uname` == "Darwin" ]; then
    # check sublime settings
    if [ ! -L $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User ]; then
        echo "Linking Sublime Settings"
        rm -rf $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User
        ln -s $PWD/SublimeSettings $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User
    fi
    
    # set vscode settings
    if [ -d ~/Library/Application\ Support/Code/User ]
    then
        if [ ! -L ~/Library/Application\ Support/Code/User/settings.json ]
        then
            rm ~/Library/Application\ Support/Code/User/settings.json
            ln -s $CBUTILS/OtherSettings/vscode_settings.json ~/Library/Application\ Support/Code/User/settings.json
        fi
    fi
    
    # LaTeX
    if [ ! -L /usr/local/texlive/texmf-local/tex/latex/local ]; then
        echo "Linking latex folder"
        sudo rm -rf /usr/local/texlive/texmf-local/tex/latex/local
        sudo ln -s $PWD/latex /usr/local/texlive/texmf-local/tex/latex/local
        texhash /usr/local/texlive/texmf-local/tex/latex/local
    fi
fi

# environment
ENVFILE=~/.environment.sh
if [ ! -e $ENVFILE ]
then
    echo "Writing new environment file (please adjust if needed):"
    echo $ENVFILE
    echo '#!/usr/bin/env bash' > $ENVFILE
    echo '' >> $ENVFILE
    echo "export CBUTILS=$CURDIR" >> $ENVFILE
    echo "export ENVFILE=$ENVFILE" >> $ENVFILE
    echo '' >> $ENVFILE
    echo '## modules' >> $ENVFILE
    echo '#MODULEPATH=$MODULEPATH'>> $ENVFILE
    echo '' >> $ENVFILE
    echo '## path' >> $ENVFILE
    echo -n 'PATH=' >> $ENVFILE
    echo "$PATH">> $ENVFILE
    echo '' >> $ENVFILE
    echo 'export CPATH=`xcrun --show-sdk-path`/usr/include' >> $ENVFILE
fi

# create link for each missing font from $CBUTILS/fonts
# install power line fonts:
read -p "Install power line fonts? [yY/?]" -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    git clone https://github.com/powerline/fonts.git --depth=1 temp_fonts_install
    # install
    cd temp_fonts_install
    ./install.sh
    # clean-up a bit
    cd ..
    rm -rf temp_fonts_install
fi

# link dotfiles
cd dotFiles
for df in `ls`
do
    if [ ! -e $HOME/.$df ]
    then
        echo "linking dotfile .$df"
        ln -s $PWD/$df $HOME/.$df
    fi
done
cd $CURDIR

# TODO:
# adjust git name and user to $GITUSER and $GITMAIL


echo "======================="
echo "Have set up everything."
echo "======================="

# going back to initial directory
cd $CURDIR
