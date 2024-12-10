#!/bin/bash

BASE_URL="http://cs01.richmond.edu:18080/api"

echo "---------------------------"
echo "Testing Pomodoro Timer API"
echo "---------------------------"

# Test POST /api/timers
echo "Test: POST /api/timers"
echoapi post "$BASE_URL/timers" \
    -d '{"workDuration": 25, "breakDuration": 5}' \
    -H "Content-Type: application/json" \
    --verbose
echo -e "\n"

# Test GET /api/timers
echo "Test: GET /api/timers"
echoapi get "$BASE_URL/timers" --verbose
echo -e "\n"

# Test DELETE /api/timers
echo "Test: DELETE /api/timers"
echoapi delete "$BASE_URL/timers" --verbose
echo -e "\n"

# Test GET /api/sessions
echo "Test: GET /api/sessions"
echoapi get "$BASE_URL/sessions" --verbose
echo -e "\n"

echo "---------------------------"
echo "All tests completed."
echo "---------------------------"
