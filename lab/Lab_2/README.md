# LAB 2 - MyShell
### Benjamin Straub
## Implement a Shell
The goal of Lab 2 was to implement a shell that can:
* execute arbitrary executibles in the file system
* change directories
* redirect the stdin/stdout from/to a file
## Implementation Details
I chose to implement everything in a single file to simplify linking
if this were to be a product, or were to be productized, it would need
to be broken up in to several files

There are also several functions that have duplicative functionality,
they should have functionality commonized and specific functionality
or behavior be determined by a passed in parameter or function

I ran into quite a few issues with string.h's strtok function and implemented
my own that was not destructive. While I could have just copied the string
to a local variable, I wanted to make a function that was not destructive. That
being said, it is fairly inefficient in comparison

Much of the complexity in this file is around strings and whitespace. I ran into 
several problems with tokenization and opening files due to whitespace. 
I ended up having to strip whitespace in multiple places and it should
probably be commonized.
