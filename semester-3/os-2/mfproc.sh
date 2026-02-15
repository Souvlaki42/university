#!/usr/bin/bash

username_arg=""
state_arg=""
uid_arg=""
res_num=0

while getopts "u:s:" opt; do
  case $opt in
    u) username_arg="$OPTARG" ;;
    s) state_arg="$OPTARG" ;;
  esac
done

if [[ -n "$username_arg" ]]; then
  if id "$username_arg" >/dev/null 2>&1; then
    uid_arg=$(id -u "$username_arg")
  else
    exit 1
  fi
fi

for entry in /proc/*
do
  pid=$(basename "$entry")

  if ! [[ "$pid" =~ ^[0-9]+$ && -d "$entry" ]]; then
    continue
  fi

  name=$(awk -F ':[[:space:]]*' 'NR==1 {print $2}' "/proc/$pid/status")
  state=$(awk -F ':[[:space:]]*' 'NR==3 {print $2}' "/proc/$pid/status")
  ppid=$(awk -F ':[[:space:]]*' 'NR==7 {print $2}' "/proc/$pid/status")
  uid=$(awk -F ':[[:space:]]*' 'NR==9 {print $2}' "/proc/$pid/status" | awk '{print $1}')
  gid=$(awk -F ':[[:space:]]*' 'NR==10 {print $2}' "/proc/$pid/status")

  if [[ -n "$uid_arg" && "$uid" != "$uid_arg" ]]; then
    continue
  fi

  if [[ -n "$state_arg" && "$state:0:1" != *"$state_arg" ]]; then
    continue
  fi
  
  read_lock_count=$(awk -v pid="$pid" '$4=="READ" && $5==pid {count++} END {print count+0}' /proc/locks)
  write_lock_count=$(awk -v pid="$pid" '$4=="WRITE" && $5==pid {count++} END {print count+0}' /proc/locks)

  res_num=$((res_num+1))

  echo "$name $pid $ppid $uid $gid $state $write_lock_count $read_lock_count"
done

if (( res_num == 0 )); then
  exit 2
fi
