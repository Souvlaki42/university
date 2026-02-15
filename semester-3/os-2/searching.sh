#!/usr/bin/bash

num_a=$1
num_b=$2

count_a=0
count_b=0
count_c=0
count_d=0
count_e=0

while read -p "Give the name of a directory: " directory; do
  if [ -z "$directory" ]; then
    echo "$count_a total files that have $num_a permissions"
    echo "$count_b total files that have been modified in the last $num_b days"
    echo "$count_c total subdirectories that have been accessed in the last $num_b days"
    echo "$count_d total files that all users in the system have read access to"
    echo "$count_e total subdirectories that can be modified by users except their owner"
    break
  fi

  output="$(find "$directory" -type f -perm $num_a)"
  count="$(echo "$output" | wc -l)"
  echo "$count files in $directory that have $num_a permissions:"
  count_a="$((count_a+count))"
  echo "$output"

  output="$(find "$directory" -type f -mtime -$num_b)"
  count="$(echo "$output" | wc -l)"
  echo "$count files in $directory that have been modified in the last $num_b days:"
  count_b="$((count_b+count))"
  echo "$output"

  output="$(find "$directory" -type d -atime -$num_b)"
  count="$(echo "$output" | wc -l)"
  echo "$count subdirectories in $directory that have been accessed in the last $num_b days:"
  count_c="$((count_c+count))"
  echo "$output"

  output="$(ls -lR $directory | grep "^-" | grep "r..r..r")"
  count="$(echo "$output" | wc -l)"
  echo "$count files in $directory that all users in the system have read access to:"
  count_d="$((count_d+count))"
  echo "$output"

  output="$(ls -lR $directory | grep "^d" | grep "[^ ]*w..")"
  count="$(echo "$output" | wc -l)"
  echo "$count subdirectories in $directory that can be modified by users except their owner:"
  count_e="$((count_e+count))"
  echo "$output"
done
