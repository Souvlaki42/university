#!/usr/bin/bash

source="$2"
dest="$3"
time="$4"

if [ -z "$source" ] || [ -z "$dest" ] || [ -z "$time" ]; then
  echo "Usage: $0 <username> <source> <destination> <time>"
  exit 1
fi

if [ -d "$dest" ]; then
  archive="$dest/$(basename "$source")-$(date +%F).tar"
  echo "/usr/bin/bash -c 'tar -cvf \"$archive\" -C \"$source\" .'" | at "$time"
  echo "Backing up $source to $archive at $time"
elif [ -f "$dest" ]; then
  echo "/usr/bin/bash -c 'tar -rvf \"$dest\" -C \"$source\" .'" | at "$time"
  echo "Appending $source to $dest at $time"
else
  echo "$dest doesn't exist yet"
fi

