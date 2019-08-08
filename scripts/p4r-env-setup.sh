#!/bin/bash
if [[ $0 == $BASH_SOURCE ]]; then
    echo "Please run: source $0"
    exit 1
fi

if ! grep "/usr/bin/modulecmd" ~/.profile > /dev/null; then
    profileAddition="
if [ -f /usr/bin/modulecmd ] ; then
    module load gcc/7.1.0
    module load git/2.14.1
    module load vscode/1.32.3
fi"
    echo "$profileAddition" >> ~/.profile
    DIR="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
    rcAdd="export PATH=$DIR:\$PATH"
    echo "$rcAdd" >> ~/.bashrc
    if [ -f ~/.zshrc ]; then
        echo "$rcAdd" >> ~/.zshrc
    fi
    eval "$profileAddition"
    eval "$rcAdd"
else
    echo "no changes made"
fi
