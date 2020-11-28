#!/bin/bash

problems_base_folder_name="problems"
input_folder_name="inputs"
output_folder_name="output"
generators_folder_name="generators"
solution_folder_name="solution"
bin_folder_name="bin"

# Inputs form the user
contest_id=$1
problem_id=$2
language=$3

contest_folder="$problems_base_folder_name/$contest_id"
problem_folder="$contest_folder/$problem_id"
input_folder="$problem_folder/$input_folder_name"
output_folder="$problem_folder/$output_folder_name"
solution_folder="$problem_folder/$solution_folder_name"
bin_folder="$problem_folder/$bin_folder_name"

# Create the input, output, generator folders
mkdir -p "$input_folder"
mkdir -p "$output_folder"
mkdir -p "$solution_folder"

# Create the solution file
touch "$solution_folder/solution.$language"

# Create atleast one input and output file
touch "$input_folder/input-0.txt"
touch "$output_folder/output-0.txt"
