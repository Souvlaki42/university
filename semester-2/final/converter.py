#!/usr/bin/env python3
import struct
import sys

def convert_map_to_binary(input_path, output_path):
    """
    Reads a text-based map file and converts it to a binary format.

    The binary format is:
    - 4-byte unsigned integer: width
    - 4-byte unsigned integer: height
    - N-bytes: raw tile data (char by char)
    """
    print(f"Reading text map from: '{input_path}'")
    
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: Input file not found at '{input_path}'")
        sys.exit(1)

    # Clean the lines by removing trailing newline characters
    lines = [line.rstrip('\n') for line in lines]

    # Filter out any empty lines that might be at the end of the file
    lines = [line for line in lines if line]

    if not lines:
        print("Error: Map file is empty.")
        sys.exit(1)

    # --- Calculate dimensions and validate ---
    height = len(lines)
    width = len(lines[0])

    for i, line in enumerate(lines):
        if len(line) != width:
            print(f"Error: Map is not rectangular!")
            print(f"Line {i+1} has length {len(line)}, but expected {width}.")
            sys.exit(1)

    print(f"Map dimensions detected: {width}x{height}")

    # --- Prepare data for writing ---
    
    # 1. Prepare the header.
    # The format string 'II' means two consecutive 4-byte unsigned integers.
    header = struct.pack('II', width, height)

    # 2. Prepare the map data by joining all lines and encoding to bytes.
    map_data_string = "".join(lines)
    map_data_bytes = map_data_string.encode('utf-8') # ASCII would also work here

    # --- Write the binary file ---
    print(f"Writing binary map to: '{output_path}'")
    try:
        with open(output_path, 'wb') as f:
            # Write the header first
            f.write(header)
            # Write the raw tile data
            f.write(map_data_bytes)
    except IOError as e:
        print(f"Error: Could not write to output file '{output_path}': {e}")
        sys.exit(1)

    print("Conversion successful.")

if __name__ == "__main__":
    # You can hardcode the filenames here...
    # convert_map_to_binary("map2.txt", "map2.dat")

    # ...or use command-line arguments for more flexibility.
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_map.txt> <output_map.dat>")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    convert_map_to_binary(input_file, output_file)