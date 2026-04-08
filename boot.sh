#Krimit Patel A00481150
#!/bin/bash

echo "1. Cleaning Old Build and Logs..."
rm -rf bin logs

echo "2. Creating Required Folders..."
mkdir -p bin logs

echo "3. Compiling Logger Module..."
gcc src/logger.c -o bin/logger
if [ $? -ne 0 ]; then
    echo "Failed to compile Logger. Aborting."
    exit 1
fi

echo "4. Compiling Other Modules..."

gcc src/file_management.c -o bin/file_management
if [ $? -eq 0 ]; then echo " - File Management compiled successfully."; else echo " - Failed to compile File Management."; fi

gcc src/peterson.c -o bin/peterson -pthread
if [ $? -eq 0 ]; then echo " - Peterson's Solution compiled successfully."; else echo " - Failed to compile Peterson's Solution."; fi

gcc src/memory.c -o bin/memory
if [ $? -eq 0 ]; then echo " - Memory Allocation compiled successfully."; else echo " - Failed to compile Memory Allocation."; fi

gcc src/amdahl.c -o bin/amdahl
if [ $? -eq 0 ]; then echo " - Amdahl's Law compiled successfully."; else echo " - Failed to compile Amdahl's Law."; fi

gcc src/main_menu.c -o bin/main_menu
if [ $? -eq 0 ]; then echo " - Main Menu compiled successfully."; else echo " - Failed to compile Main Menu."; fi

echo "5. Report Compilation Status completed."

echo "6. Running Main Menu..."
if [ -f "bin/main_menu" ] || [ -f "bin/main_menu.exe" ]; then
    cd bin
    ./main_menu
else
    echo "main_menu executable not found."
fi
