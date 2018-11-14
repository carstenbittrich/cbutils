
if [[ `uname` == "Darwin" ]]; then
    # functions that rely on mac OS
    function qlook
    {
        qlmanage -p "$@" > /dev/null 2>&1
    }

    function notify
    {
        eval $@;
        if [ $? != 0 ]; then
            terminal-notifier -message $@ -title Failure -activate com.apple.Terminal
        else
            terminal-notifier -message $@ -title Done -activate com.apple.Terminal
        fi
    }

    function ropen
    {
        scp $@ /private/tmp/ropen_temp
        open /private/tmp/ropen_temp
    }

    function sag
    {
        say -v "Yannick" "$@"
    }
else
    # functions that won't run on mac OS

    function pidwatch() {
        pidstat -hurd -p ${1} 5
    }
fi

function after() {
    while [ $(ps ux | grep -c "$1") != 1 ]
        do sleep 30
    done
    echo "$1 done at $(date)"
}

function sshagentadd {
  eval "$(ssh-agent -s)"
  ssh-add ~/.ssh/id_rsa
}

function newest {
    ls -1tr $@ | tail -n 1
}

function rroot
{
    scp $@ /private/tmp/rroot_temp.root
    root /private/tmp/rroot_temp.root
}

function putbox() {
    tar -cvf ~/.box.tar ${1}
    gzip -f -9 ~/.box.tar
}

function getbox {
    if [ ! -e ~/Temp/_box ]; then
        mkdir -p ~/Temp/_box
    fi
    if [ -d $2 ] ; then
        if [ -z $2 ] ; then
            cd ~/Temp/_box
        else
            cd $2
        fi
    else
        cd ~/Temp/_box
    fi
    scp $1:.box.tar.gz box.tar.gz
    tar -xzvf box.tar.gz
}

# handy extract
function extract
{
    if [ -f $1 ] ; then
        case $1 in
            *.tar.bz2)   tar xvjf $1     ;;
            *.tar.gz)    tar xvzf $1     ;;
            *.bz2)       bunzip2 $1      ;;
            *.rar)       unrar x $1      ;;
            *.gz)        gunzip $1       ;;
            *.tar)       tar xvf $1      ;;
            *.tbz2)      tar xvjf $1     ;;
            *.tgz)       tar xvzf $1     ;;
            *.zip)       unzip $1        ;;
            *.Z)         uncompress $1   ;;
            *.7z)        7z x $1         ;;
            *)           echo "'$1' cannot be extracted via >extract<" ;;
        esac
    else
        echo "'$1' is not a valid file"
    fi
}

### Physics

function afsinidesy {
    kinit -Rf cbittric@DESY.DE || kinit -f -l 25h -r 7d -k ~/.ssh/krb.keytab cbittric@DESY.DE
        aklog -cell desy.de -k DESY.DE
}
function afsinicern {
    kinit -Rf cbittric@CERN.CH || kinit -f -l 25h -r 7d cbittric@CERN.CH
        aklog -cell cern.ch -k CERN.CH
}

function setupATLAS
{
    export RIVET_ANALYSIS_PATH=/raid1/users/bittrich/WZ/Rivet/_Analysen20
    export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
    export RUCIO_ACCOUNT=cbittric
    source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh
}

function goto_samples
{
    module load PyYAML 2>/dev/null || echo "Module PyYAML not available"
    module load python 2>/dev/null || echo "Module python not available"
    cd $SAMPLEBASE
    athena_setup
    lsetup rucio
    lsetup pyami

    function download_files {
        rucio download --ndownloader 4 `egrep -v "#" -i ${1} | tr '/\n' ' '`
    }
}

function goto_CAF
{
    export CAFINPUT=$CAFPATH/Input/ELCore2CAF
    cd $CAFPATH
    module load boost
    module load root
}

function goto_ELCore
{
    if [ $ELCOREPATH != ""]; then
        cd $ELCOREPATH
        for mod in $ELCOREMODULES; do
            module load $mod
        done
        export OUTPUTDIR=$ELCOREOUTPUTDIR
        # export PATH=$HOME/Tool/GridTools/:$PATH
        athena_setup
        export GROUPDATA=/cvmfs/atlas.cern.ch/repo/sw/database/GroupData
        export GROUPWEB=http://atlas.web.cern.ch/Atlas/GROUPS/DATABASE/GroupData
        source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalPandaClientSetup.sh --pandaClientVersion ${pandaClientVersionVal}
        source rcSetup.sh
        if [ -e $HOME/software/PyYAML/pyyaml-env.sh ]; then
            source $HOME/software/PyYAML/pyyaml-env.sh
        fi
    else
        echo "ELCOREPATH not set, don't know where to go"
    fi
}
