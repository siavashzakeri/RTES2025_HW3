#!/bin/bash
set -euo pipefail

PORT=8080

echo "Simple HTTP Web Server – running on port $PORT"

while true; do

    RESP="Hello $(date '+%Y-%m-%d %H:%M:%S')"

    {
        printf 'HTTP/1.1 200 OK\r\n'
        printf 'Content-Type: text/plain; charset=utf-8\r\n'
        printf 'Content-Length: %s\r\n' "${#RESP}"
        printf 'Connection: close\r\n'
        printf '\r\n'
        printf '%s\n' "$RESP"
    } | nc -l -p "$PORT" >/dev/null 2>&1

    echo "$RESP"
done


