#!/bin/bash

# Configuration
FIFO_PATH="/tmp/myfifo"

[[ -p "$FIFO_PATH" ]] || mkfifo "$FIFO_PATH"

echo "Type messages (Ctrl-D to quit):"

while IFS= read -r line; do
    printf '%s\n' "$line"
done > "$FIFO_PATH"
