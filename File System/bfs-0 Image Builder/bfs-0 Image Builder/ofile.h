#pragma once
#pragma once

// File access modes
#define O_RDONLY    0x0000  // Open for reading only
#define O_WRONLY    0x0001  // Open for writing only
#define O_RDWR      0x0002  // Open for reading and writing

// File creation flags
#define O_CREAT     0x0200  // Create the file if it does not exist
#define O_EXCL      0x0400  // Ensure that this call creates a new file
//#define O_NOCTTY    0x0800  // Don't assign a controlling terminal
#define O_TRUNC     0x2000  // Truncate the file to zero length if it already exists
#define O_APPEND    0x04000 // Append data to the end of the file

// File status flags
//#define O_NONBLOCK  0x0004  // Non-blocking I/O
//#define O_SYNC      0x101000  // Synchronous I/O
//#define O_DSYNC     0x100000  // Data synchronization I/O
//#define O_RSYNC     0x400000  // Read synchronization

// File locking and memory mapping
//#define O_FSYNC     0x101000  // Synchronous file updates
//#define O_ASYNC     0x0040  // Enable signal-driven I/O

// Directory flags (specific to directories, and not typical files)
#define O_DIRECTORY 0x10000 // Fail if not a directory

// Additional flags
//#define O_CLOEXEC   0x02000000  // Close the file descriptor on exec()

struct ofile 
{
	unsigned int fnode_id;
	unsigned int position;
	unsigned int flags;
};