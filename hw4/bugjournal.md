# Bug 1

## A) How is your program acting differently than you expect it to?
- when I run ./test_suite, it passes httpconnection basic test, but
it was stuck at partial read test. It stops moving.

## B) Brainstorm a few possible causes of the bug
- Because I have while loop in the code, it might caused by infinite loop
- It passes basic test, but failed at partial read test. It might be because 
besic test tests on small length of content, but partial test include large files.
- This file include many functions that I seldomly used, for example converting 
char* to string. I looked up functions over the internet, but they might be unreliable.

## C) How you fixed the bug and why the fix was necessary
- I run the valgrind and it shows me uninitialized parameter of rfind function. I print 
the string content both before the the function and after the function and find out
the result includes some werid character. So I change rfind to find and the problems
are fixed.


# Bug 2

## A) How is your program acting differently than you expect it to?
- The website I opened shows me "Cancelled load from ‘http://attu3.cs.Washington.edu:5567/‘ because it is using HTTP/0.9"

## B) Brainstorm a few possible causes of the bug
- it said HTTP/0.9, so I should set HTTP to 0.9 rather than 1.1?
- because it happened when I try to open 333gle but it worked fine in the other website,
so it might be caused by some error in ProcessQueryRequest.

## C) How you fixed the bug and why the fix was necessary
- I open the telnet and found out that the result returned is fine except the binary solution
said that HTTP/1.1 200 OK and mine said some random number. When I looked into ProcessQueryRequest method, I found out I did not set protocol, response_code and message, so I set it up.


# Bug 3

## A) How is your program acting differently than you expect it to?
- Our server cannot open the wikipedia page from the search result

## B) Brainstorm a few possible causes of the bug
- Maybe miss to update the wikipedia url?
- The search result wikipedia url might be wrong?

## C) How you fixed the bug and why the fix was necessary
- We compared the html response from solution binary and our implementation, and found the html shouldn't add '/static/'
before the uri. So we add an if statement to specifically deal
with the uri if it begin with "http://".
