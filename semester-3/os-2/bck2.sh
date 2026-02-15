#!/usr/bin/env bash

STAMP_FILE="$HOME/.weekly_backup_start"

if [[ "$1" == "cron" ]]; then
    [[ -f "$STAMP_FILE" ]] || date +%s > "$STAMP_FILE"

    START_TS=$(cat "$STAMP_FILE")
    NOW_TS=$(date +%s)
    THRESHOLD=$((182*24*3600)) 

    if (( NOW_TS >= START_TS + THRESHOLD )); then
        crontab -l 2>/dev/null | grep -v "$0 cron" | crontab -
        exit 0
    fi

    archive="/tmp/$(basename "$PWD")-$(date +%F).tar"
    tar -cvf "$archive" -C "$PWD" .
    echo "Backed up $PWD to $archive"
    exit 0
fi

date +%s > "$STAMP_FILE"

CRON_LINE="0 23 * * 0 $(realpath $0) cron"

tmpfile=$(mktemp)

crontab -l 2>/dev/null > "$tmpfile"

grep -Fq "$CRON_LINE" "$tmpfile" || echo "$CRON_LINE" >> "$tmpfile"

crontab "$tmpfile"
rm -f "$tmpfile"

echo "Cron added"
