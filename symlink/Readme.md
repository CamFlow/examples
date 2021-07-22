# Procfs Symlink Example
### Purpose
This is a mockup example to demonstrate what happens in the CVE-5736-2019. To see whether camflow registers write edges when the writes are made using symlinks

### Method
- First the `my_file.o` is executed and is kept in the running state and the PID is extracted.
- Then `overwrite.o` is executed which works in four steps:
    - First the executable file is opened for reading through the procfs using the followng path: `/proc/<pid>/exe`. The corresponding file descriptor(fd) is saved.
    - Contents of evil_file binary are read and placed in a buffer.
    - The `overwrite.o` then waits for the `my_file.o` to exit. As soon as `my_file.o` exits, the executable file is opened in write mode using the procfs symlink (`/proc/self/fd/<fd_val>`) and the fd saved in step 1.
    - Finally, the contents of `my_file.o` are overwritten with the contents of `evil_file.o`.


### How to execute the example
- In the first shell, run `./my_file.o`
- In the second shell, run `./overwrite.o`
- Go back to the first shell and then press "e" and then hit the enter key.
- To check if `my_file.o` was overwritten, run `./my_file.o` again.
