

# Shell Implementation Program

## Introduction
This project involves the design and implementation of a basic Linux shell that supports five internal commands: cd, mv, rm, ls, and cp. The shell also incorporates additional options for these commands, including custom options such as recursive behavior and help options. The implementation utilizes classes and objects, supporting wildcard characters for enhanced flexibility.

## Shell Commands and Options
### Internal Commands:

cd: Change directory

mv: Move files or directories

rm: Remove files or directories

ls: List directory contents

cp: Copy files or directories

## Options:

Each command supports a set of custom options (at least four), including recursive behavior and a help option.

## Profiling Script
A Bash script is provided for profiling the shell's performance using the time command. The script creates three different directory structures with varying numbers and sizes of files. It then measures the time taken by each of the five internal commands for each case, providing valuable insights into the shell's efficiency.

## Multi-threaded Implementation
For external commands involving recursion, a multi-threaded implementation has been integrated. The number of threads is dynamically determined based on the available CPU cores and workload. This implementation leverages multi-threading libraries to enhance performance.

## Profiling of Multi-threaded Version
To assess the performance of the multi-threaded version, a re-profiling step is included. This involves comparing the execution times of the multi-threaded implementation with the original single-threaded version. Insights gained from this comparison can help evaluate the effectiveness of multi-threading in improving the shell's efficiency.

## Usage
### Shell:

Run the shell script.
Enter commands with options and observe the behavior.

### Profiling:

Execute the profiling script to create directories and measure command execution times.
Analyze the output for performance insights.
### Multi-threaded Implementation:

Observe the enhanced performance of recursive commands.
Adjust the number of threads based on available resources.
### Profiling Multi-threaded Version:

Re-run the profiling script on the multi-threaded shell.
Compare results with the single-threaded version.
### Contributors
[Ankur Bhoi]

[Ayush Giri Goswami]



