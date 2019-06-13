#!/bin/bash
repo=$(git remote -v | head -n 1 | awk '{print $2}')
if [ -z "$repo" ]; then
    echo "Try using cd to move into your ROB599 directory"
    exit 1
fi
# echo "repo: $repo"

repo_dir=$(git rev-parse --show-toplevel)
pset=$(pwd | sed "s:$repo_dir::g" | tr -d '/')
if [ -z "$pset" ]; then
    echo "Error: not in a problem/assignment subdirectory"
    echo "Try using cd to move into the directory you want to submit"
    exit 1
fi
# echo "pset: $pset"

problem=$1
# echo "problem: $problem"
# echo ""

curl -X GET "localhost:8599/check?repo=$repo&pset=$pset&problem=$problem"
