#!/bin/bash
if [[ $0 == $BASH_SOURCE ]]; then
    echo "Please run: source $0"
    exit 1
fi

if ! grep gcc-7.1.0 ~/.profile > /dev/null; then
    profileAddition='export PATH=/usr/um/gcc-7.1.0/bin/:/usr/um/git-2.14.1/bin/:/usr/um/vscode-1.32.3/bin/:$PATH'
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
