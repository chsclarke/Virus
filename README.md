# File Infecting Virus
File infecting virus implemented in C. 

linux_virus.c Built for Linux x86 systems (infects only ELF executables).  
mac_virus.c Built for Mac OSX (infects only Mach-O executables).  

Author: Chase Clarke cfclarke@bu.edu

This code is written solely for academic purposes and is not to be used for for illegal or damaging applications.

## What is a file Infecting virus?

"A file-infecting virus is a type of malware that infects executable files with the intent to cause permanent damage or make them unusable. A file-infecting virus overwrites code or inserts infected code into an executable file. This type of virus can infect a number of operating systems, including Macintosh, Windows, and Unix."

## How does it work?

The operation of this virus is simple but effective. Every executable is viewed by the program as infected or uninfected. If the file is infected, it is left alone. If it is not infected, the following operation is executed:

First, the given payload is executed. Next, an existing (uninfected) executable is found and the virus is appended at the beginning of the new file. This is great; the virus will spread, but if the computer attempts to run an infected file, the virus will execute and the original file will not. 

To remedy the problem stated above, the virus will split a copy of the infected program by creating two temporary executables in the /tmp directory* upon execution. The virus will call these executables in succession. The first file will be the malware and the second will be the original program. For demonstration purposes, my virus payload consists of a print statement that says “Hello! I am a simple virus!” every time it is run.

To summarize: an infected file will print “Hello! I am a simple virus!” (this is my mock payload), attempt to infect another file, and then execute the original functionality of the file.

*Usage of the /tmp directory is intended to prevent an ls call from accidentally uncovering the temporary files during the virus’s execution.

# Getting Started

Fork the code into a local, isolated, directory.
Run through the following steps to get a feel of how the virus runs andspreads.

* Make sure invoking your virus stand-alone as ./virus works -- it should not
crash:
```
$ ./virus 2>&1
Hello! I am a simple virus!
```
* Copy /bin/echo to the directory where your virus is and test it:
```
$ cp /bin/echo .
$ ls
echo  sometext.txt  virus
$ ./virus 2>&1
Hello! I am a simple virus!
$ ./echo Master
Hello! I am a simple virus!
Master
```
* Copy /bin/ls to the directory where your virus is and test it:
```
$ cp /bin/ls .
$ ./echo 2>&1
Hello! I am a simple virus!

$ ./ls 2>&1
Hello! I am a simple virus!
echo  ls  sometext.txt  virus
```
* Copy /bin/cat and /bin/grep where your virus is and test that your virus is
robust:
```
$ cp /bin/cat .
$ cp /bin/grep .
$ chmod u-w-r grep
$ ./ls 2>&1
Hello! I am a simple virus!
cat  echo  grep  ls  sometext.txt  virus
$ ./cat sometext.txt -n 2>&1
Hello! I am a simple virus!
     1  Hello world!
```
* Invoke ./echo again to make sure that the output is the same:
```
$ ./echo Master
Hello! I am a simple virus!
Master
```
(test cases created by Manuel Egele megele@bu.edu).

