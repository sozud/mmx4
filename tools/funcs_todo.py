import os

def get_file_path(filename):
    script_dir = os.path.dirname(os.path.realpath(__file__))  # Directory of the script
    return os.path.join(script_dir, filename)

# Function to read hex numbers from the file
def read_hex_numbers(filename):
    file_path = get_file_path(filename)  # Get full path to the file
    with open(file_path, 'r') as file:
        return {line.strip() for line in file}

# Function to find matching files and sort them by size
def find_matching_files_sorted_by_size(directory, hex_numbers):
    matching_files = []
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.startswith("func_") and filename.endswith(".s"):
                hex_part = filename[5:13]  # Extract XXXXXXXX part from func_XXXXXXXX.s
                if hex_part in hex_numbers:
                    file_path = os.path.join(root, filename)
                    file_size = os.path.getsize(file_path)
                    matching_files.append((file_path, file_size))
    
    # Sort files by size (smallest to largest)
    matching_files.sort(key=lambda x: x[1])
    
    return matching_files

# Main function
def main():
    # Read hex numbers from output.txt
    hex_numbers = read_hex_numbers('mednafen_trace.txt')
    
    # Define the directory to search
    search_directory = 'asm/us/main/nonmatchings/323C'
    
    # Find matching files and sort them by size
    matching_files = find_matching_files_sorted_by_size(search_directory, hex_numbers)
    
    # Print matching files with their sizes
    if matching_files:
        print(f"Matching files found ({len(matching_files)}), sorted by size:")
        for file, size in matching_files:
            print(f"{file} - {size} bytes")
    else:
        print("No matching files found.")

if __name__ == "__main__":
    main()
