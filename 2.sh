#!/bin/bash

# Create directory (1) with 50 files of 1GB each
mkdir -p dir1
for ((i=1; i<=50; i++)); do
    dd if=/dev/zero of=dir1/file${i}.txt bs=1G count=1
done

# Create directory (2) with 5000 files of 10MB each
mkdir -p dir2
for ((i=1; i<=5000; i++)); do
    dd if=/dev/zero of=dir2/file${i}.txt bs=10M count=1
done
# Function to create files of a specific size
create_files() {
  local size_mb=$1
  local num_files=$2
  local directory=$3

  for ((i = 1; i <= num_files; i++)); do
    dd if=/dev/zero of="$directory/file${i}.txt" bs=1048576 count=$size_mb
  done
}

# Function to create directories and files recursively(3)
create_directory_structure() {
  local base_directory=$1
  local num_files=$2
  local levels=$3
  local size_mb=10

  mkdir -p "$base_directory"
  cd "$base_directory"

  create_files $size_mb $num_files .

  if [ "$levels" -gt 0 ]; then
    for ((i = 1; i <= num_files; i++)); do
      local sub_directory="subdir${i}"
      mkdir "$sub_directory"
      cd "$sub_directory"
      create_directory_structure "$PWD" $num_files $((levels - 1))
      cd ..
    done
  fi
}

# Set the base directory and call the function to create the structure
base_directory="main_directory"
num_files_per_directory=50
levels=99  # Adjust the number of levels as needed

create_directory_structure "$base_directory" $num_files_per_directory $levels

echo "Directory structure created successfully."


