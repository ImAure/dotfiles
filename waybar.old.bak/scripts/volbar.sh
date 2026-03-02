#!/bin/bash

vol=$(pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}' | tr -d '%')
mute=$(pactl get-sink-mute @DEFAULT_SINK@ | awk '{print $2}')

bars=10

if [ "$mute" = "yes" ]; then
    echo "  &lt;=============&gt;"
    exit
fi

filled=$((vol * bars / 100))
empty=$((bars - filled))

printf "  &lt;"
printf "%0.s=" $(seq 1 $filled)
printf "||"
printf "%0.s=" $(seq 1 $empty)
printf "&gt;"
