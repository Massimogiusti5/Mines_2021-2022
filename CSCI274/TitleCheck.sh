#!/usr/bin/env bash
LC_COLLATE=C

echo "Enter a title: "
read title

for token in _${title}; do

  case ${token} in
    _[a-z]*)
      echo "'${token:1}' should be capitalized."
      ;;
    A|An|In|Out|To|From|For|The|Of)
      echo "'${token}' should NOT be capitalized."
      ;;
    a|an|in|out|to|from|for|the|of)
      echo -n ""
      ;;
    [a-z]*)
      echo "'${token}' should be capitalized."
      ;;
  esac
done