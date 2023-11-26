#!/bin/bash

# Directory containing the files to process
tracefolder="/home/priyansh/Downloads/CS683/Tracefiles/Project"

# Get the list of files in the directory and store it in an array
file_list=("$tracefolder"/*)

# Loop through each file in the list
for file_path in "${file_list[@]}"; do
    # Extract the file name from the file path
    file_name=$(basename "$file_path")
    
    # Check if the item is a regular file
    if [ -f "$file_path" ]; then
        # Remove the extension and store in a new variable
        file_name_no_ext="${file_name%.champsimtrace.xz}"

        # Run the command with the current file, output to a .txt file
        bin/lru --warmup_instructions 25000000 --simulation_instructions 25000000 "$tracefolder/$file_name" > "logs/lru_$file_name_no_ext.txt"
    fi
done