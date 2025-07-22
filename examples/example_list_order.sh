#!/bin/bash

#List current orders on market and update

#set correct script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXEC_LIST="$SCRIPT_DIR/../build/examples/example_list_order"
EXEC_UPDATE="$SCRIPT_DIR/../build/examples/example_update_order"

"$EXEC_LIST" \
  --USERNAME $USERNAME \
  --PASSWORD $PASSWORD \
  --TOKEN $APIKEYDELAY \