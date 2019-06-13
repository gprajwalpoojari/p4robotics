#!/bin/bash
repo=$(git remote -v | head -n 1 | awk '{print $2}')
if [ -z "$repo" ]; then
    echo "Try using cd to move into your ROB599 directory"
    echo "We need the git repo to mark your clicker choice"
    exit 1
fi

choice=$1

curl -X PUT "localhost:8599/clicker?repo=$repo&choice=$choice"
