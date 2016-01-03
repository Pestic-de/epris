#!/bin/sh

CURRENT=$(epr list | grep "^*" | cut -c 3-)
DIRNAME=$(dirname "$CURRENT")
BASENAME=$(basename "$CURRENT")

echo "$DIRNAME"
echo "$BASENAME"

SHOW=$(epr show)
TITLE=$(echo "$SHOW" | grep title | cut -c 17-)
ARTIST=$(echo "$SHOW" | grep artist | cut -c 17-)
ALBUM=$(echo "$SHOW" | grep album | cut -c 17-)

echo $TITLE "("$ALBUM "-" $ARTIST")"
