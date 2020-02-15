# Homework 03: linked lists

*Due 2/21 by 3pm*

---
 
This is *A WORKING DRAFT* of the initial repository for the third homework
assignment for the Spring 2020 offering of Reed's CSCI 221.

This folder contains an implementation of a linked list *library*, as
implemented in the two source files `llist.hh` and `llist.cc`. Neither
of these files have a `main` in them. Instead, they can be compiled
with other program source code that needs to use a linked list to
structure its data. (Such code is called *client code* of the
`llist` library we've invented.) This folder also contains a sample
client program, the source file `test_llist.cc` that is simply a
"driver" program that can be used to test the linked list code.

This assignment has three parts. Part 1 asks you to complete the 
implementation of the `llist` library, adding the two methods
`length` and `delete`. You can test these by compiling and running
the driver program. Parts 2 and 3 each ask you to mimic this code
by inventing a linked list implementation of an *ordered dictionary*
data structure and also a linked list implementation of a *queue*
data structure.

Once you've completed the assignment, then, you will have edited
or created 7 files that you'll need to submit, namely

    llist.cc (Part 1)
    order.cc order.hh test_order.cc (Part 2)
    queue.cc queue.hh test_queue.cc (Part 3)

Please work to mimic the 
[coding style guidelines](https://jimfix.github.io/csci221/assigns/C_style_guide_hw02.html) 
and formatting I've
suggested so far. Include comments that describe the code, when
appropriate. Include some comments at the top of your source code,
including your name and other brief info describing the program. There
should also be a brief comment that precedes each struct, function, 
and procedure definition you write. Mimic the work I've produced for
the `llist*` files here.

You should work to complete each of these exercises so that they
compile and run correctly. Should you face problems in solving an
exercise, you can still submit broken code. In your top comment in
that file **PLEASE** *let us know in what way the code is broken* (why
it doesn't compile, or what tests failed, etc.). In many cases, we are
willing to give partial credit if you identify problems in the code.

### Running the starter code

You might find it useful to start by just compiling and running the
provided program. It can be compiled with the unix command line

    g++ --std=c++11 -g -o test_llist test_llist.c llist.cc

and then run with the unix command line

    ./test_llist <values>

where `<values>` is either nothing, or a space-separated list of
integers that get used as the contents of a linked list, first
built by the program.

Once running, the program asks for a series of commands, ones that
perform a suite of operations on that linked list. For example,
here is an interaction made possible by the program:

    $ ./test_llist 5 7 3
    Your list is [5, 7, 3].
    Enter a list command: insert end 42
    Done.
    Your list is [5, 7, 3, 42].
    Enter a list command: delete front
    Done.
    Your list is [7, 3, 42].
    Enter a list command: search 5
    Not found.
    Your list is [7, 3, 42].
    Enter a list command: quit
    Bye!
    $

The set of commands it accepts is reported by the `help` command and
is the following:
 
    insert front <number>
    insert end <number>
    delete front
    delete end
    remove <number>  
    search <number>
    length
    help
    quit
 
Two of these commands won't do anything. The `remove` and `length`
commands will be implemented in the Part 1 exercises.

### Debugging linked list code

There are several tricky things about writing C++ code that works
with pointers. The most frequent bug in your code that you'll encounter
is a `Segmentation fault.` This arises when you attempt to access the
`data` or `next` field of a `node*`, say for example, with expressions
like `list->first->data` or `current->next`.  In each (see the `llist`
code) the expressions `list->first` and `current` are each of type
`node*`, so they could each be pointing to a valid struct of type `node`.
Or it's possible that each could be a `nullptr`.

I've trained myself, when writing linked list code, to worry quite a
bit any time my code accesses one of these fields. When I type
`->data` or `->next` an alarm goes off in my coding mind, asking the
question "*Could this pointer be null??*" I then work hard to either
(a) convince myself that the line of code cannot face that situation,
that I've eliminated the `nullptr` scenario by handling such cases
with conditional statements (or, because the condition on my loop
prevents that scenario within its body). Or (b) I realize that a
`nullptr` is actually possible at that moment, and develop more
complex code that handles that case.

Nevertheless, I still make mistakes, and so there are a few strategies
I use for figuring out the cause of a segmentation fault. One useful
strategy is to add output lines before and after lines of code that
are suspect. You can, for example, output the value of a pointer using
`std::cout <<` just before a line that relies on a pointer being valid.
If the output is the `nullptr`, with hexadecimal address `0x0`, then
I've found my bug.

Alternatively, most of you will have installed C++ and command-line
console tools that provide a debugger. On most people's systems, the
debugger tool is called `gdb`. This is the debugger provided with the
Gnu compiler suite (which includes `g++`). On many Mac OSX systems,
the debugger is instead provided as part of the LLVM compiler tools,
and the command is named `lldb`.

I'll work to show these commands' use in lecture and in lab, and your
tutors are also familiar with them. But, at a minimum, you can use a
debugger in a limited way to at least identify the line of code where
your segmentation fault is occurring. Below shows an interaction that
results from me testing my `llist` library when it had a bug in my
`deleteEnd` procedure. (I had forgotten to check if the list only
had one item in it.)

Here is that interaction:

    $ lldb test_llist
    (lldb) target create "test_llist"
    Current executable set to 'test_llist' (x86_64).
    (lldb) run 5 7 3
    Process 4586 launched: '/Users/jimfix/git/ReedCS2-S20/Lec03-3-examples/test_llist' (x86_64)
    Your list is [5, 7, 3].
    Enter a list command: delete end
    Done.
    Your list is [5, 7].
    Enter a list command: delete end
    Done.
    Your list is [5].
    Enter a list command: delete end
    Process 4586 stopped
    * thread #1: tid = 0x23d84, 
    0x0000000100007ac8 test_llist`llist::deleteEnd(list=0x00000001003000b0) + 56 at llist.cc:76,
    queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x8)
    frame #0: 0x0000000100007ac8
    test_llist`llist::deleteEnd(list=0x00000001003000b0) + 56 at llist.cc:76
       73
       74      node* follower = list->first;
       75      node* leader = list->first->next;
    -> 76      while (leader->next != nullptr) {
       77        follower = leader;
       78        leader = leader->next;
       79      }
    (lldb) print leader
    (llist::node *) $0 = 0x0000000000000000
    (lldb) quit
    Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] Y
    $
     
In the above, I loaded the program into the debugger and ran it with
`run 5 7 3`. This is equivalent to just running the program in the
console with this command line

    $ ./test_llist 5 7 3

except it gets watched over by the debugger. After a few `delete end`
commands, making the list have only one element, my code then crashed
in the middle of `deleteEnd` at line 76 in `llist.cc`. I next printed
the value of the pointer `leader` and discovered that it was a null
pointer.

You can do similar work while developing your solutions. The key thing
that we did to enable this debugging was to compile the code with the
debug flag `-g`. This produces a different executable, one that's
filled with extra code information that both `gdb` and `lldb` can use
to give better feedback on your running program.

---

### Part 1: complete `llist`

---

### Part 2: write `order`

---

### Part 3: write `queue`

---
