#!/bin/bash
if ! grep gcc-7.1.0 ~/.profile > /dev/null; then
    echo 'export PATH=/usr/um/gcc-7.1.0/bin/:/usr/um/git-2.14.1/bin/:/usr/um/vscode-1.32.3/bin/:$PATH' >> ~/.profile
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
    echo "export PATH=$DIR:\$PATH" >> ~/.bashrc
    source ~/.profile
    source ~/.bashrc
else
    echo "no changes made"
fi
