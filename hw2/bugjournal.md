# Bug 1

## A) How is your program acting differently than you expect it to?
- on the line 75 of searchshell.c, it shows that passing argument of 
- tolower makes integer from pointer without a cast.
## B) Brainstorm a few possible causes of the bug
- the parameter type might be wrong
- since the method has many char/char*/char**, it is easy to make mistakes

## C) How you fixed the bug and why the fix was necessary
- I compare the parameter type (char) with my input parameter type (char*)
- So I change query[j] = tolower(query[j]) to 
- *(token+j) = tolower(*(token+j))


# Bug 2

## A) How is your program acting differently than you expect it to?
- FileParser.c AddWordPosition add an empty string at position 47.

## B) Brainstorm a few possible causes of the bug
- Maybe the if statement to execute AddWordPosition is wrong?
- unsuccessful set the word_start?
- Any cases that will execute AddWordPosition when it shouldn't be execute?

## C) How you fixed the bug and why the fix was necessary
- Run through GDB and find the case two continous boundary char will lead to
- treate empty string as a word. We change the statement to execute
- AddWordPosition to first check whether current ptr is inside a word.





# Bug 3

## A) How is your program acting differently than you expect it to?
- qsort receive a seg fault.

## B) Brainstorm a few possible causes of the bug
- qsort is dealing with mystery data or data that it can't access?
- Maybe we didn't update i correctly? should we always increase it?
- why is i keep increasing without stop? maybe we have an infinite loop?
## C) How you fixed the bug and why the fix was necessary
- When checking "." file, we didn't update dirent but directly break
- the while loop. We finally update dirent and i while encounter
- "." and ".." file.
