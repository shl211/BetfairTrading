#!/bin/bash

#This will cancel unmatched orders
#can cancel specific markets or bets if specified

#set correct script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXEC="$SCRIPT_DIR/../build/examples/example_cancel_order"

#run example_cancel_order script
"$EXEC" \
  --USERNAME $USERNAME \
  --PASSWORD $PASSWORD \
  --TOKEN $APIKEYDELAY \