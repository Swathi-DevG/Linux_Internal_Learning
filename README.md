# Linux_Internal_Learning
Welcome to **Linux_Internals_Learning** — a personal repository where I document and practice key concepts of Linux systems programming through hands-on C programs.
This collection includes short, focused programs that demonstrate my understanding of linux internals.

---

## 1. Simple File Logger
This is a basic C program that demonstrates how to perform file operations using Linux system calls. It periodically logs timestamped messages to a file (`log.txt`) and showcases key Linux internals like `open()`, `write()`, `close()`, `time()`, and `ctime()`.

### 🛠️ Concepts Covered
- File handling using `open()`, `write()`, and `close()`
- Time handling using `time()` and `ctime()`
- Working with file descriptors
- Using system-level sleep delays with `sleep()`

---

## 2. File Copier with Offset
This program copies data from a source file to a destination file, starting from a user-defined byte offset.  
It is designed to showcase file reading and writing using system calls, along with offset manipulation using `lseek()`.

### 🛠️ Concepts Covered
- Reading and writing files using `read()` and `write()`
- File descriptor manipulation with `open()` and `close()`
- Seeking file position using `lseek()`
- Handling command-line arguments
- Error checking and system call robustness
- Usage: ./file_copier_with_offset <source file> <dest file> <offset>

---

## 3. DUP-based I/O Echo (Without printf / scanf)
This program demonstrates how to perform standard input and output operations without using printf and scanf, instead using low-level system calls and file descriptor duplication via dup().

### 🛠️ Concepts Covered
- System-level input/output with read() and write()
- File descriptor duplication with dup()
- Clean, low-level resource handling using close()

---