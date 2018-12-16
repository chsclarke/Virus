# File Infecting Virus
File infecting virus implemented in C. Built for Linux x86 systems.




================================================================================

To test rubustness of program feel free to test with these test cases 
(created by Manuel Egele megele@bu.edu).



1.) Make sure invoking your virus stand-alone as ./virus works -- it should not
crash:

$ ./virus 2>&1
Hello! I am a simple virus!

2.) Copy /bin/echo to the directory where your virus is and test it:

$ cp /bin/echo .
$ ls
echo  sometext.txt  virus
$ ./virus 2>&1
Hello! I am a simple virus!
$ ./echo Master
Hello! I am a simple virus!
Master

3.) Copy /bin/ls to the directory where your virus is and test it:

$ cp /bin/ls .
$ ./echo 2>&1
Hello! I am a simple virus!

$ ./ls 2>&1
Hello! I am a simple virus!
echo  ls  sometext.txt  virus

4.) Copy /bin/cat and /bin/grep where your virus is and test that your virus is
robust:

$ cp /bin/cat .
$ cp /bin/grep .
$ chmod u-w-r grep
$ ./ls 2>&1
Hello! I am a simple virus!
cat  echo  grep  ls  sometext.txt  virus
$ ./cat sometext.txt -n 2>&1
Hello! I am a simple virus!
     1  Hello world!

5.) Invoke ./echo again to make sure that the output is the same:

$ ./echo Master
Hello! I am a simple virus!
Master
