#!/usr/bin/bash

source="$2"
dest="$3"

if [ -z "$source" ] || [ -z "$dest" ]; then
  echo "Usage: $0 <username> <source> <destination>"
  exit 1
fi

if [ -d "$dest" ]; then
  archive="$dest/$(basename "$source")-$(date +%F).tar"
  tar -cvf "$archive" -C "$source" .
  echo "Backed up $source to $archive"
elif [ -f "$dest" ]; then
  tar -rvf "$dest" -C "$source" .
  echo "Appended $source to $dest"
else
  echo "$dest doesn't exist yet"
fi

