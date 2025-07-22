#!/bin/bash

#List current orders on market and replace

#set correct script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXEC_REPLACE="$SCRIPT_DIR/../build/examples/example_replace_order"

#adjust accordingly
"$EXEC_REPLACE" \
  --USERNAME $USERNAME \
  --PASSWORD $PASSWORD \
  --TOKEN $APIKEYDELAY \
  --BETID 395580802338\
  --MARKETID "1.245754549"\
  --NEW_BET_PRICE 11 \
