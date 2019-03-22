# Lab 1 - basic os information 
<p> 
    Name: Ben Straub
    Student Id: 830-27-6423
    Date: 02/18/2019
</p>

## Purpose
<p>
    The basic purpose of this excersize was to familiarize ourselves with the available utilities related to os/hardware information 
    We were to use the exposed functionality in uname as well as scrape various system statistics from the proc psuedo directory system
</p>

## Implementation
<p>
    I chose to implement all of the functionality in a single file using c.
    Parts A and B are relegated to seperate functions and part B is split into function by file. 
    Since we were looking for specific values in specific positions, parsing was confined to a single function, rewinding the file position pointer after finding the initial value. 
    In some cases rewinding was unecessary, but to avoid problems if the file format was different, we rewind whenever we find a key, but will need to search the file again after parsing that keys value.
</p>

## To Run
<p> 
In directory:
  *  make clean
  *  make 
  *  ./Lab1
</p>
    
