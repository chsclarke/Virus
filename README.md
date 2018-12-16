# File Infecting Virus
File infecting virus implemented in C. Built for Linux x86 systems.


To test rubustness of program feel free to test with these test cases (created by ).

1.) Make sure invoking your virus stand-alone as ./virus works -- it should not
crash:

terrier080@master:~/test$ ./virus 2>&1
Hello! I am a simple virus!

2.) Copy /bin/echo to the directory where your virus is and test it:

terrier080@master:~/test$ cp /bin/echo .
terrier080@master:~/test$ ls
echo  sometext.txt  virus
terrier080@master:~/test$ ./virus 2>&1
Hello! I am a simple virus!
terrier080@master:~/test$ ./echo Master
Hello! I am a simple virus!
Master

3.) Copy /bin/ls to the directory where your virus is and test it:

terrier080@master:~/test$ cp /bin/ls .
terrier080@master:~/test$ ./echo 2>&1
Hello! I am a simple virus!

terrier080@master:~/test$ ./ls 2>&1
Hello! I am a simple virus!
echo  ls  sometext.txt  virus

4.) Copy /bin/cat and /bin/grep where your virus is and test that your virus is
robust:

terrier080@master:~/test$ cp /bin/cat .
terrier080@master:~/test$ cp /bin/grep .
terrier080@master:~/test$ chmod u-w-r grep
terrier080@master:~/test$ ./ls 2>&1
Hello! I am a simple virus!
cat  echo  grep  ls  sometext.txt  virus
terrier080@master:~/test$ ./cat sometext.txt -n 2>&1
Hello! I am a simple virus!
     1  Hello world!

5.) Invoke ./echo again to make sure that the output is the same:

terrier080@master:~/test$ ./echo Master
Hello! I am a simple virus!
Master

Please go back and debug your stuff. Hope to see you again!
