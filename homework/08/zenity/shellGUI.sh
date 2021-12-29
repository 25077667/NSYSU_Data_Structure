#!/bin/bash
FILE="$(zenity --file-selection --title='Select your File')"

zenity --question --text="operation?" --ok-label="compress" --cancel-label="decompress"
ANS=$?
if [ "$ANS" -eq 0 ]; then
    ../huffman.elf ${FILE} -c | zenity --progress --pulsate --time-remaining
else
    ../huffman.elf ${FILE} -d | zenity --progress --pulsate --time-remaining
fi
