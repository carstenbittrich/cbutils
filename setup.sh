#!/usr/bin/env bash

CURDIR=$PWD

if [ `uname` == "Darwin" ] # mac OS
then
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
ENVFILE=$CURDIR/dotFiles/environment.sh
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
	echo "## physics" >> $ENVFILE
	echo "" >> $ENVFILE
	echo "### Samples" >> $ENVFILE
	echo "export SAMPLEBASE=$HOME" >> $ENVFILE
	echo "" >> $ENVFILE
	echo "### CAF" >> $ENVFILE
	echo "export CAFPATH=$HOME" >> $ENVFILE
	echo "export GTEST_REPO=$HOME" >> $ENVFILE
	echo "" >> $ENVFILE
	echo "### ELCore" >> $ENVFILE
	echo "export ELCOREPATH=" >> $ENVFILE
	echo "" >> $ENVFILE
	echo "### OtherTools" >> $ENVFILE
	echo "export OTHERTOOLS=" >> $ENVFILE
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

echo "======================="
echo "Have set up everything."
echo "======================="

# going back to initial directory
cd $CURDIR
