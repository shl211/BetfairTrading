#!/bin/bash

#List current orders on market and update

#set correct script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXEC_UPDATE="$SCRIPT_DIR/../build/examples/example_update_order"

#adjust accordingly
"$EXEC_UPDATE" \
  --USERNAME $USERNAME \
  --PASSWORD $PASSWORD \
  --TOKEN $APIKEYDELAY \
  --BETID 395577515031\
  --MARKETID "1.245754549"\
  --NEWPERSISTENCE LAPSE \
