## First-Time Git Setup
```shell
sudo apt-get install git-all
```

   1./etc/gitconfig file: Contains values for every user on the system and all their repositories. If you pass the option --system to git config , it reads and writes from this file specifically.

2. ~/.gitconfig or ~/.config/git/config file: Specific to your user.
You can make Git read and write to this file specifically by passing the --global option.

3. config file in the Git directory (that is, .git/config ) of whatever repository you’re currently using: Specific to that single repository.

Each level overrides values in the previous level, so values in .git/config trump those in /etc/gitconfig .

```shell
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@example.com
```

If you want to override this with a different name or email address for spe-cific projects, you can run the command without the --global option when you’re in that project.



Now that your identity is set up, you can configure the default text editor that will be used when Git needs you to type in a message. If not configured, Git uses your system’s default editor.
If you want to use a different text editor, such as Emacs, you can do the following:

```shell
$ git config --global core.editor emacs
```

If you want to check your settings, you can use the git config --list com-
mand to list all the settings Git can find at that point:

```shell
$ git config --list
user.name=John Doe
user.email=johndoe@example.com
color.status=auto
color.branch=auto
color.interactive=auto
color.diff=auto
...
```

You can also check what Git thinks a specific key’s value is by typing git
config <key> :

```shell
$ git config user.name
John Doe
```



```
$ git help <verb>
$ git <verb> --help
$ man git-<verb>
```

## Git Basics

Initializing a Repository in an Existing Directory

```
$ git init
```

You can accomplish that with a few git add commands that specify the
files you want to track, followed by a git commit :

```
$ git add *.c
$ git add LICENSE
$ git commit -m 'initial project version'
```

If you want to clone the repository into a directory named something other than “libgit2”, you can specify that as the next command-line option:

```
$ git clone https://github.com/libgit2/libgit2 mylibgit
```

working directory can be in one of two states: tracked or untracked. Tracked files are files that were in the last snap- shot; they can be unmodified, modified, or staged. Untracked files are every- thing else – any files in your working directory that were not in your last snap- shot and are not in your staging area.

As you edit files, Git sees them as modified, because you’ve changed them
since your last commit. You stage these modified files and then commit all your
staged changes, and the cycle repeats.

![image-20220130170157426](ProGit.assets/image-20220130170157426.png)



```
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
nothing to commit, working directory clean
```

In order to begin tracking a new file, you use the command git add . To begin
tracking the README file, you can run this:

```
$ git add README
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
(use "git reset HEAD <file>..." to unstage)
new file:
README
```

You can tell that it’s staged because it’s under the “Changes to be commit-
ted” heading. If you commit at this point, the version of the file at the time you
ran git add is what will be in the historical snapshot. You may recall that when
you ran git init earlier, you then ran git add (files) – that was to begin
tracking files in your directory. The git add command takes a path name for
either a file or a directory; if it’s a directory, the command adds all the files in
that directory recursively

### Staging Modified Files

Let’s change a file that was already tracked. If you change a previously tracked file called CONTRIBUTING.md and then run your git status command again, you get something that looks like this:

```
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
	(use "git reset HEAD <file>..." to unstage)
		new file:
README
Changes not staged for commit:
	(use "git add <file>..." to update what will be committed)
(use "git checkout -- <file>..." to discard changes in working directory)
	modified:	CONTRIBUTING.md
```

The CONTRIBUTING.md file appears under a section named “Changes not staged for commit” – which means that a file that is tracked has been modified in the working directory but not yet staged. To stage it, you run the git add command. git add is a multipurpose command – you use it to begin tracking new files, to stage files, and to do other things like marking merge-conflicted files as resolved. It may be helpful to think of it more as “add this content to the next commit” rather than “add this file to the project”. Let’s run git add now to stage the CONTRIBUTING.md file, and then run git status again:

```
$ git add CONTRIBUTING.md
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
(use "git reset HEAD <file>..." to unstage)
new file:
modified:
README
CONTRIBUTING.md
```

Both files are staged and will go into your next commit. At this point, sup-
pose you remember one little change that you want to make in CONTRIBU-
TING.md before you commit it. You open it again and make that change, and
you’re ready to commit. However, let’s run git status one more time:

```
$ vim CONTRIBUTING.md
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
	(use "git reset HEAD <file>..." to unstage)
		new file:	README
		modified:	CONTRIBUTING.md

Changes not staged for commit:
	(use "git add <file>..." to update what will be committed)
	(use "git checkout -- <file>..." to discard changes in working directory)
		modified:  CONTRIBUTING.md
```

What the heck? Now CONTRIBUTING.md is listed as both staged and unstag-
ed. How is that possible? It turns out that Git stages a file exactly as it is when
you run the git add command. If you commit now, the version of CONTRIBU-
TING.md as it was when you last ran the git add command is how it will go
into the commit, not the version of the file as it looks in your working directory
when you run git commit . If you modify a file after you run git add , you have
to run git add again to stage the latest version of the file:

```
$ git add CONTRIBUTING.md
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
(use "git reset HEAD <file>..." to unstage)
new file:
modified:
README
CONTRIBUTING.md
```

### Short Status

If you run git status -s or git status --short you get a far more simpli-
fied output from the command:

```
$ git status -s
 M README # modified in the working directory but not yet staged
MM Rakefile # modified, staged and then modified again, so there are changes to it that are both staged and unstaged.
A lib/git.rb
M lib/simplegit.rb # modified and staged
?? LICENSE.txt
```

New files that aren’t tracked have a ?? next to them, new files that have been added to the staging area have an A , modified files have an M and so on.

the left-hand column indicates the status of the staging area and the right-hand column indicates the status of the working tree.

### Ignoring Files

```
$ cat .gitignore
*.[oa]
*~
```

The first line tells Git to ignore any files ending in “.o” or “.a” – object and archive files that may be the product of building your code.

he second line tells Git to ignore all files whose names end with a tilde ( ~ ), which is used by many text editors such as Emacs to mark temporary files.

The rules for the patterns you can put in the .gitignore file are as follows:

• Blank lines or lines starting with # are ignored.
• Standard glob patterns work.
• You can start patterns with a forward slash ( / ) to avoid recursivity.
• You can end patterns with a forward slash ( / ) to specify a directory.
• You can negate a pattern by starting it with an exclamation point ( ! ).

Glob patterns are like simplified regular expressions that shells use. An aster-isk ( * ) matches zero or more characters; [abc] matches any character inside the brackets (in this case a, b, or c); a question mark ( ? ) matches a single character; and brackets enclosing characters separated by a hyphen ( [0-9] ) match-es any character between them (in this case 0 through 9). You can also use two asterisks to match nested directories; a/**/z would match a/z , a/b/z , a/b/c/z , and so on.

```
# no .a files
*.a
# but do track lib.a, even though you're ignoring .a files above
!lib.a
# only ignore the TODO file in the current directory, not subdir/TODO
/TODO
# ignore all files in the build/ directory
build/
# ignore doc/notes.txt, but not doc/server/arch.txt
doc/*.txt
# ignore all .pdf files in the doc/ directory
doc/**/*.pd
```

https://github.com/github/gitignore

### Viewing Your Staged and Unstaged Changes



ou want to know exactly what you changed, not just which files were changed – you can use the git
diff command. We’ll cover git diff in more detail later, but you’ll probably use it most often to answer these two questions: What have you changed but not yet staged? And what have you staged that you are about to commit? Al- though git status answers those questions very generally by listing the file names, git diff shows you the exact lines added and removed – the patch, as it were.

Let’s say you edit and stage the README file again and then edit the CONTRIBUTING.md file without staging it. If you run your git status command, you once again see something like this:

```
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
	(use "git reset HEAD <file>..." to unstage)
		modified:	README
Changes not staged for commit:
	(use "git add <file>..." to update what will be committed)
	(use "git checkout -- <file>..." to discard changes in working directory)
		modified:	CONTRIBUTING.md
```

To see what you’ve changed but not yet staged, type git diff with no other arguments:

```
$ git diff
diff --git a/CONTRIBUTING.md b/CONTRIBUTING.md
index 8ebb991..643e24f 100644
--- a/CONTRIBUTING.md
+++ b/CONTRIBUTING.md
@@ -65,7 +65,8 @@ branch directly, things can get messy.
 Please include a nice description of your changes when you submit your PR;
 if we have to read the whole diff to figure out why you're contributing
 in the first place, you're less likely to get feedback and have your change
-merged in.
+merged in. Also, split your changes into comprehensive chunks if your patch is
+longer than a dozen lines.

If you are starting to work on a particular area, feel free to submit a PR
that highlights your work in progress (and note in the PR title that it's
```

That command compares what is in your working directory with what is in your staging area. The result tells you the changes you’ve made that you haven’t yet staged

If you want to see what you’ve staged that will go into your next commit, you can use git diff --staged . This command compares your staged changes to your last commit:

```
$ git diff --staged
diff --git a/README b/README
new file mode 100644
index 0000000..03902a1
--- /dev/null
+++ b/README
@@ -0,0 +1 @@
+My Project
```

It’s important to note that git diff by itself doesn’t show all changes
made since your last commit – only changes that are still unstaged. This can be
confusing, because if you’ve staged all of your changes, git diff will give you
no output.

For another example, if you stage the CONTRIBUTING.md file and then edit
it, you can use git diff to see the changes in the file that are staged and the
changes that are unstaged. If our environment looks like this:

```
$ git add CONTRIBUTING.md
$ echo '# test line' >> CONTRIBUTING.md
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
Changes to be committed:
	(use "git reset HEAD <file>..." to unstage)
	
		modified:	CONTRIBUTING.md
		
Changes not staged for commit:
	(use "git add <file>..." to update what will be committed)
	(use "git checkout -- <file>..." to discard changes in working directory)
	
		modified:	CONTRIBUTING.md
```

Now you can use git diff to see what is still unstaged:

```
$ git diff
diff --git a/CONTRIBUTING.md b/CONTRIBUTING.md
index 643e24f..87f08c8 100644
--- a/CONTRIBUTING.md
+++ b/CONTRIBUTING.md
@@ -119,3 +119,4 @@ at the
 ## Starter Projects

 See our [projects list](https://github.com/libgit2/libgit2/blob/development/PROJECTS.md).
+# test line
```

and git diff --cached to see what you’ve staged so far ( --staged and
--cached are synonyms):

```
$ git diff --cached
diff --git a/CONTRIBUTING.md b/CONTRIBUTING.md
index 8ebb991..643e24f 100644
--- a/CONTRIBUTING.md
+++ b/CONTRIBUTING.md
@@ -65,7 +65,8 @@ branch directly, things can get messy.
 Please include a nice description of your changes when you submit your PR;
 if we have to read the whole diff to figure out why you're contributing
in the first place, you're less likely to get feedback and have your change
-merged in.
+merged in. Also, split your changes into comprehensive chunks if your patch is
+longer than a dozen lines.

 If you are starting to work on a particular area, feel free to submit a PR
 that highlights your work in progress (and note in the PR title that it's
```









