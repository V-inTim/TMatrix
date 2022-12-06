#!/usr/bin/env bash

# Files to check:
file_patterns='
*.c
*.cpp
*.h
*.hpp
*.md
*.sh
*.yml
'

# TODO: Look also for trailing empty lines, and missing '\n' after the last line
if git --no-pager grep --color -n --full-name -e ' $' -- $file_patterns; then
    echo "Error: trailing whitespace found in source file(s)"
    echo ""
    echo "This can often be fixed with:"
    echo "    git rebase --whitespace=fix HEAD~1"
    echo "or"
    echo "    git rebase --whitespace=fix master"
    echo "and then a forced push of the correct branch"
    exit 1
fi
