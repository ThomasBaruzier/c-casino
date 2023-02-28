#!/bin/bash

make && tilp bin/*.8xp -n -s >/dev/null && echo "Pushed"
