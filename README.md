# Monitoring File Changes With Inotify

*© Israel Pereira Tavares da Silva*

> The inotify API provides a mechanism for monitoring filesystem events. Inotify can be used to monitor individual files, or to monitor directories. When a directory is monitored, inotify will return events for the directory itself, and for files inside the directory.



* [Man](https://man7.org/linux/man-pages/man7/inotify.7.html#EXAMPLES)



## About

With the inotify API actions can be made upon a file or directory being changed. As an example, the program written in `watch.c` watches for changes made to `file.txt` and executes a system command.



## Usage 

Clone the project.

```bash
$ git clone git@github.com:ismalakazel/C-Inotify-FileWatch.git
```

Created an executable from `watch.c`.

```bash
$ gcc -o watch.out watch.c
```

Run the program.

```bash
./watch.out file.txt firefox &
```

* `file.txt` is the file that's being monitored for changes.
* `firefox` is the system command that will be ran upon changes in `file.txt`

On another terminal tab run the following:

```bash
$ echo hello >> file.txt
```

After the above the echo command, `watch.out` observes `file.txt` has changed and starts Firefox browser. If `file.txt` was updated with a text editor such as [VisualStudio](www.visualstudio.microsoft.com) the `watch.out` program would do the same thing. For [Vim](www.vim.org) users `watch.c` would have to be changed because [Vim](www.vim.org) creates a new file and moves it in place of the original one.



> Talk does not cook rice. (Chinese proverb) 

