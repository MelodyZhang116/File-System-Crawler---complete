# Bug 1

## A) How is your program acting differently than you expect it to?
- When I run ./test_suite, it was stuck at some point in FileIndexReader 
and not showing results.

## B) Brainstorm a few possible causes of the bug
- I think it might be caused by an infinite loop
- I think it might be caused by inproper fread, for example, not updating variables


## C) How you fixed the bug and why the fix was necessary
- I communicate with my partner and he points out that in step 4 we should do byte-by-byte,
because in that case we do not need to worry about endian issue. So I changed from fread(buf, kbufsize, 1, file_); to fread(buf, 1, kbufsize, file_);


# Bug 2

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 


# Bug 3

## A) How is your program acting differently than you expect it to?
- 

## B) Brainstorm a few possible causes of the bug
- 
- 
- 

## C) How you fixed the bug and why the fix was necessary
- 
