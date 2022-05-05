# F28HS Coursework 1

This is the starter code for F28HS coursework 1: C programming.

## Getting the code

You must first **FORK** the project from:

https://gitlab-student.macs.hw.ac.uk/f28hs-2020-21/f28hs-2020-21-staff/f28hs-2020-21-cwk1-c

then clone your fork to your computer.

We recommend that you use the command line for using the `git` command
to version control `steg.c` as you progress.

For this, use a terminal window (__changing `<username>` to your
Heriot-Watt username__):

```bash
git clone git@gitlab-student.macs.hw.ac.uk:<username>/f28hs-2020-21-cwk1-c.git

```

Alternatively, you can clone your fork using the same URL, using any
modern IDE development environment. e.g. how we used GitLab in F28SG
and other Java-based courses to clone your GitLab projects. 

## Compiling

You can compile the `steg.c` file with the `gcc` compiler:

```bash
gcc -o steg steg.c

```

You're now ready! Now complete the coursework 1 lab sheet, which is
available on Vision.

You can use which ever development environment you are comfortable
with. There are many C development environments available for Linux
including Emacs, Vim, Netbeans, Eclipse, `gedit` and `kwrite`. We
recommend that you keep it simple: a text editor, a terminal window
and `gcc` is enough.

## Version control your work

To understand the life cycle of a file in a git repository, watch from
15m 21s of [this
video](https://web.microsoftstream.com/video/407df13c-18b7-4163-a1e3-90e5ceb54585?st=921).

The most useful git operation are `add`, `commit` and `push`.

`git add` allows you to add a file to the staging area to be included
in the next commit you create. E.g.

    git add steg.c

Once you have one or multiple files in the staging area, you can then
create a commit, e.g.

    git commit -m "Implements the encode function"

Finally, push that commit to the MACS GitLab Student server:

    git push

## Submission

Your submission should comprise two files:

1. `steg.c` which is your C implementation of steganography.
2. `Report.md` which is your write up of your `steg.c` solution.

Create and push commits as you work through the questions. Create
small commits frequently during and after each question, and push them
to GitLab. This is a good software engineering practise.

__Importantly__, you must create a commit for your final solution and
push it to GitLab within the submission deadline. Your `Report.md` and
`steg.c` file will be marked based on their version at the coursework
1 deadline.
