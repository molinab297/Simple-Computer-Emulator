# Simple-Computer-Emulator
Repository for a simple computer emulator! Simulates the simple computer as seen at http://www.cs.xu.edu/csci170/07f/simpleComputer/sc.html

![Alt text](/MainScreen.png?raw=true "Optional Title")

# Editing Commands
 
# Keyboard Input
 
Keyboard input is allowed to cells within the Memory, Input Cards, and Program Counter (PC). Simply select the desired cell and type the contents. When finished and the keyboard focus is taken from the cell, the cell contents are checked. Non-numeric characters are discarded and the cell contents are formatted.
 
Any input to the Accumulator (AC), Instruction Register (IR), Output Cards, or Memory Cell '00' is discarded and the previous value is restored when keyboard focus is taken from the cell. It is not possible to print the emulator with erroneous or 'fabricated' values within these cells.
 
# Moving Cell Contents
 
Cell contents can be moved from one cell to another by highlighting the cell, typing "ctrl-x" to cut or "ctrl-c" to copy, then selecting the target cell and typing "ctrl-v" to paste.
 
# Clearing
 
Buttons are provided at the top of each component of the Simple Computer Emulator to allow clearing of the cells. Clearing of the CPU will reset the Program Counter to '00'. Clearing of the Input Cards resets the Input Card counter to '01'. Memory location '00' is always '001' by default.
 
A 'Reset' button is provided for the Input Cards to allow resetting the Input Card counter without clearing the cell contents.
 
A 'Clear All' button is provided to clear all components of the Simple Computer simultaneously.
 
# Input/Ouput
 
#Printing
 
Printing of the Simple Computer and all it's contents is accomplished by selecting "File" from the browser's menu, then "Print" to print the page. Alternatively, it is possible to do a screen capture of the browser and paste this to another application program.
 
# Loading Program Files
 
Loading program files is accomplished in three steps:
Select the "Load" button from the Simple Computer menu. A window will open with a list of program files available on the server. Click to choose one of the program files, or alternatively type in the path to a program file on disk. Pathnames to files on disk are similar to the form: file:///A|/programs/DIVISION.html
Click on "Select" to download the program file. A window will open that contains this file.
Click on "Load" to load the program.
Saving Program Files
 
Saving is accomplished in two steps:
Select the "Save button from the Simple Computer menu. A window will open that contains the program file.
Select "File" "Save As" from the menu on this smaller window to save the program file to disk.
Execution
 
The Simple Computer Emulator is a three decimal digit virtual machine. It contains 100 cells of Memory (cell '00' through '99'), 15 Input Cards, and 15 Ouput Cards. The Central Processing Unit (CPU) contains a three decimal digit accumulator (with an associated one decimal digit Carry 'Bit'), a three decimal digit Instruction Register, and a two decimal digit Program Counter. It can handle Signed-Magnitude execution with an additional sign bit, or alternatively, Ten's complement execution without the sign bit.
 
# Instruction Set
 
Each instruction word is composed of a one decimal digit operation code and a two decimal digit address. The left most digit is taken to be the operation code, the right two digits are the address.
 
The full instruction set can be seen inside the appilcation by clicking the OpCodes button on the top right corner of the screen.
 
# Execution Mode
 
Signed-Magnitude or Ten's Complement execution is choosen by selecting from the switch in the CPU.
 
# Step
 
Make sure the Program Counter is set to the correct value. Execution can proceed one instruction at a time by clicking the "Step" button in the CPU. This feature is useful when debugging. The "Run" button can be selected at any time during this process to allow execution to proceed normally from that point on. A message is posted at the end of execution.
 
# Run
 
Make sure the Program counter is set to the correct value. Normal execution is initiated by clicking the "Run" button in the CPU. A message is posted at the end of execution.
