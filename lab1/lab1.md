# CS-265: Advanced Programming Tools & Techniques
## Lab 1 — Moving In: tux, vim, and permissions

By the end of this lab you will have a private course directory on tux, a shell configured the way we'll use it all term, a working knowledge of vim, and proof that you can get files off tux and into Canvas.

### What you will hand in

Upload two plain-text files to the **Lab 1** assignment on Canvas:

| File | What it is |
|------|------------|
| `lab1.txt` | Your answer sheet. Answer every question marked **Q#**. |
| `vi_lab.txt` | Your saved copy of the vim tutorial, with its edits done. |

### Conventions

- Code blocks show exactly what to type. You can copy and paste them.
- `abc123` stands for your Drexel user ID. Use your own.
- Commands run on tux unless the step says **on your laptop**.
- Vim keys are written like **Esc :wq Enter**. Press them in order.

---

## Part 1 — Move in

1. **On your laptop**, log in to tux:

   ```
   ssh abc123@tux.cs.drexel.edu
   ```

   If ssh isn't working, see **[Connecting to tux — Canvas page]**.

2. Make your course directory and make it private:

   ```
   mkdir ~/CS265
   chmod 700 ~/CS265
   ```

3. Get the course materials. This makes your own copy of the instructor's files:

   ```
   git clone https://github.com/Drexel-CoEC-Parkinson/CS-265 ~/CS265/materials
   ```

   You don't need to understand `git` yet. Two rules:

   - Never work inside `~/CS265/materials`. Copy files *out* of it.
   - Before each lab or activity, run `cd ~/CS265/materials && git pull` to get new files.

4. Make a directory for this lab and copy the Lab 1 files into it:

   ```
   mkdir ~/CS265/lab1
   cd ~/CS265/lab1
   cp ~/CS265/materials/lab1/* .
   mv lab1_template.txt lab1.txt
   ls
   ```

   You should see `README.md`, `funny`, `hello.bash`, `lab1.md`, and `lab1.txt`.

**Q1** Run `ls -ld ~/CS265` and paste the output. (You'll decode it in Part 6.)

---

## Part 2 — The round trip

Every lab is submitted the same way: copy your files from tux to your laptop with `scp`, then upload them to Canvas. Make sure that works now.

1. On tux, make a test file:

   ```
   echo "round trip test from abc123" > roundtrip.txt
   ```

2. **On your laptop**, open a **second** terminal window (not the one logged in to tux) and run:

   ```
   scp abc123@tux.cs.drexel.edu:CS265/lab1/roundtrip.txt .
   ```

   This means: from *user*@*machine*:*path*, copy to `.` (the current folder here).

3. Check that the file arrived on your laptop, then upload it to **[Lab 1 – round trip check — Canvas assignment]**.

> **Most common mistake:** running `scp` on tux. If your prompt says `tux`, you're in the wrong window.

**Q2** Paste the exact `scp` command you ran.

---

## Part 3 — Startup files

When bash starts, it reads settings from a file in your home directory called `.bashrc`. We provide three settings files. Install them, saving a backup of any file you already have:

```
cd ~
mv .bashrc .bashrc.ORIG
cp ~/CS265/materials/dotfiles/bashrc .bashrc
cp ~/CS265/materials/dotfiles/inputrc .inputrc
cp ~/CS265/materials/dotfiles/vimrc .vimrc
. ~/.bashrc
```

The last line (a dot, a space, then the path) loads the new settings into your current shell. Check it worked:

```
set -o | grep vi
```

You should see `vi  on`. If not, ask for help.

The new `.bashrc` changes a few things you'll notice all term:

| Setting | Effect |
|---------|--------|
| `set -o vi` | Edit the command line with vim keys (Part 5). |
| `set -o noclobber` | `>` won't overwrite an existing file. |
| `set -o ignoreeof` | Ctrl-D won't log you out. Type `exit`. |
| `rm -i`, `cp -i`, `mv -i` | Ask before deleting or overwriting. |

Go back to your lab directory:

```
cd ~/CS265/lab1
```

**Q3** Run `echo again > roundtrip.txt`. What message do you get, and which setting causes it?

---

## Part 4 — Vim

This course uses **vim** for all editing. Learn these first:

| Keys | Effect |
|------|--------|
| **Esc :q! Enter** | Quit **without** saving. |
| **Esc :wq Enter** | Save and quit. |
| **Esc u** | Undo. |

If you're lost, press **Esc** twice and quit.

If you ever see **E325: ATTENTION … Found a swap file**, an earlier vim session didn't close cleanly. Press **D** to delete the old swap file and continue.

### The tutorial

1. Start the tutorial:

   ```
   vimtutor
   ```

2. **Save it under your own name right away**, or your work will be lost:

   **Esc :saveas vi_lab.txt Enter**

   Use `:saveas`, not `:w vi_lab.txt`. `:saveas` switches vim over to the new file, so every later save goes into `vi_lab.txt`. (`:w vi_lab.txt` would only save a copy, and your later saves would go to a temporary file that is deleted when you quit.)

3. Work through the whole tutorial (about 30 minutes), doing each edit it asks for. Save often with **Esc :w Enter**. To come back later: `vi ~/CS265/lab1/vi_lab.txt`.

**Q4** Write "done" when `vi_lab.txt` is complete and saved in `~/CS265/lab1`.

### Fix a file

The file `funny` has three typos, each on a line marked `FIXME`.

1. `vi funny`
2. Type `/FIXME` and press Enter to jump to the first one. `n` jumps to the next.
3. Fix the typo (`x` deletes a letter, `r` replaces one, `i` inserts).
4. Put the cursor on the space before `FIXME` and press `D` to delete to the end of the line.
5. Do the other two, then **Esc :wq Enter**.

**Q5** Paste the three corrected lines.

---

## Part 5 — Editing the command line

With `set -o vi`, you can use vim keys on the command line. Run these three commands:

```
echo one fish
echo two fish
echo red fish
```

Now press these keys one at a time, then Enter:

**Esc  k  k  0  w  c  w  blue  Enter**

**Q6** What printed? In a few words each, what did `k`, `0`, `w`, and `cw` do?

---

## Part 6 — Permissions

### Reading `ls -l`

```
ls -l
```

You'll see something like this:

```
-rw-------  1 abc123 domain users  1462 Oct  1 09:25 funny
-rw-------  1 abc123 domain users   231 Oct  1 09:25 hello.bash
```

The first column has 10 characters. The first one is the type (`d` = directory, `-` = file). The other nine are three groups of `rwx`:

| Characters | Who |
|------------|-----|
| 2–4 | **user**: you, the owner |
| 5–7 | **group** |
| 8–10 | **other**: everyone else |

A letter means allowed; `-` means not allowed.

| Letter | On a file | On a directory |
|--------|-----------|----------------|
| `r` | read it | list the names inside |
| `w` | change it | add or delete files inside |
| `x` | run it as a program | go into it |

**Q7** Look back at your Q1 output. What can you, your group, and others do with `~/CS265`?

### Changing permissions with `chmod`

Each group gets one digit: add **4** for read, **2** for write, **1** for execute. The three digits are user, group, other.

```
chmod 700 dir     # you: rwx.  everyone else: nothing
chmod 644 file    # you: rw.   everyone else: read only
chmod 600 file    # you: rw.   everyone else: nothing
```

You can also add or remove one permission: `chmod u+x file` adds execute for yourself (**u**ser).

Try running the script:

```
./hello.bash
```

**Q8** What happened, and why? (Look at `ls -l hello.bash`.) Now run `chmod u+x hello.bash`, run the script again, and paste its output.

### Directories: the locked box

Run these commands one at a time and note which ones fail:

```
mkdir box
echo "the note inside" > box/note.txt

chmod 600 box
ls box
cat box/note.txt

chmod 100 box
ls box
cat box/note.txt

chmod 700 box
```

**Q9** For `600` and for `100`, which of `ls box` and `cat box/note.txt` worked? Which letter lets you *list* a directory, and which lets you *get to the files* inside?

**Q10** Which `chmod` command would let everyone read a file, but only you change it?

---

## Part 7 — Submit

1. Delete the test file (answer `y` when asked):

   ```
   rm roundtrip.txt
   ```

2. Check `lab1.txt` in vim: every question answered, blank line between answers.

3. **On your laptop**, copy both files down:

   ```
   scp abc123@tux.cs.drexel.edu:CS265/lab1/lab1.txt .
   scp abc123@tux.cs.drexel.edu:CS265/lab1/vi_lab.txt .
   ```

4. Upload `lab1.txt` and `vi_lab.txt` to the **Lab 1** assignment on Canvas.

### Before you leave

- [ ] You can ssh to tux from your own laptop.
- [ ] `roundtrip.txt` is uploaded to Canvas.
- [ ] Log out, log back in, and `set -o | grep vi` still says `on`.
- [ ] You can open a file in vim, change it, save, and quit without looking at this handout.
