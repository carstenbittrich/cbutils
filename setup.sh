#!/usr/bin/env bash

CURDIR=$PWD

if [ `uname` == "Darwin" ] # mac OS
then
	# check os version:
	# sw_vers -productVersion

	# xcode
	if [ ! -e `xcrun --show-sdk-path`/usr/include ]
	then
		xcode-select --install
		# also remember to add this line to shell config ($CBUTILS/dotFiles/environment.sh):
		# export CPATH=`xcrun --show-sdk-path`/usr/include
		# this was an alternative in mojave:
		# sudo open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg
	fi

	# set up brew
	if [ ! -e "/usr/local/bin/brew" ]
	then
		/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
	brew list > lists/brew-installed-list.txt

	# install brew packages
	while read line
	do
	    name=`echo $line | cut -d " " -f 1`
	    if [ `grep -c -e "^$name$" lists/brew-installed-list.txt` -ne 1 ]
	    then
	        echo "install $name"
	        brew install $name
	    fi
	done < lists/brew-packages.txt
	# reinstall python2
	# brew install https://raw.githubusercontent.com/Homebrew/homebrew-core/86a44a0a552c673a05f11018459c9f5faae3becc/Formula/python@2.rb

	# install missing casks
	while read line
	do
		name=`echo $line | cut -d " " -f 1`
		if ! brew cask info $name &> /dev/null; then
			brew cask install $name
		fi
	done < lists/brew-casks.txt
fi

# check if zsh shell available
if [ ! `command -v zsh` ]
then
	if [ `uname` == "Darwin" ]
	then
		echo "Installing zsh"
		brew install zsh
	fi
	# what if zsh is not available on system without admin rights?
fi

# TODO: install oh-my-zsh

# TODO: install zsh autosuggestions
if [ -e OhMyZshCustom/plugins/zsh-autosuggestions ]
then
	git clone https://github.com/zsh-users/zsh-autosuggestions OhMyZshCustom/plugins/zsh-autosuggestions
fi
ln -s $PWD/OhMyZshCustom ~/.zsh/custom

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

if [ `uname` == "Darwin" ]; then
	# check sublime settings
	if [ ! -L $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User ]; then
		echo "Linking Sublime Settings"
		rm -rf $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User
		ln -s $PWD/SublimeSettings $HOME/Library/Application\ Support/Sublime\ Text\ 3/Packages/User
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
ENVFILE=~/.zsh/custom/environment.sh
if [ ! -e $ENVFILE ]
then
	echo "Writing new environment file (please adjust if needed):"
	echo $ENVFILE
	echo "#!/usr/bin/env bash" > $ENVFILE
	echo "" >> $ENVFILE
	echo "export CBUTILS=$CURDIR" >> $ENVFILE
	echo "export ENVFILE=$ENVFILE" >> $ENVFILE
	echo "" >> $ENVFILE
	echo "## modules" >> $ENVFILE
	echo 'MODULEPATH=$MODULEPATH'>> $ENVFILE
	echo "" >> $ENVFILE
	echo "## path" >> $ENVFILE
	echo 'PATH=$PATH'>> $ENVFILE
	echo "" >> $ENVFILE
	echo "export CPATH=`xcrun --show-sdk-path`/usr/include" >> $ENVFILE
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
