#!/bin/bash

#This will place a bet at the specified terms, and after 5 second delay will print current orders on the market
#Note that event is a query used to find the event names via text search query
#Obviously not super robust
#This just exposes some basic functionality, lots more detail under the hood with api calls

#set correct script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXEC="$SCRIPT_DIR/../build/examples/example_place_order"

#run example_place_order script
"$EXEC" \
  --USERNAME $USERNAME \
  --PASSWORD $PASSWORD \
  --TOKEN $APIKEYDELAY \
  --EVENT "England (W) v Italy (W)" \
  --RUNNER "England (W)" \
  --MARKET "Match Odds" \
  --ORDER_PRICE 10.0 \
  --ORDER_SIZE 1 \
  --SIDE BACK