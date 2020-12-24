# task-manager-cli

Implementation of a command-line (CLI) program that lets you manage your tasks.

## To run the program

1. Install CPP: You should have build support for cpp on your system.

2. Build the app by running `make app`.

3. Once you are done with the changes you should be able to execute by running the following command from the terminal.

   **On Windows:**

   ```
   .\todo.bat
   ```

   **On \*nix:**

   ```
   ./todo.sh
   ```
## Run Automated Tests

### 1. Install Node.js

You need to have npm installed in your computer for this problem. It comes with Node.js and you can get it by installing Node from https://nodejs.org/en/

### 2. Install dependencies

Run `npm install` to install all dependencies.

### 3. Create symbolic link to the executable file

#### On Windows

To create a symbolic link on Windows, you'll need to run either the Windows Command Prompt, or Windows Powershell **with administrator privileges**. To do so, right-click on the icon for Command Prompt, or Powershell, and choose the _"Run as Administrator"_ option.

**Command Prompt:**

```
> mklink todo todo.bat
```

**Powershell:**

```
> cmd /c mklink todo todo.bat
```

#### On \*nix:

Run the following command in your shell:

```
$ ln -s todo.sh todo
```

### 4. Run the tests.

Now run `npm test` to run the tests.

## A Note about `/` for Windows Users

In the following sections, you'll see many commands prefixed with `./`, or paths containing the `/` (forward-slash) character.

If you're using the Windows _Command Prompt_, then you'll need to replace `/` with `\` (back-slash) for these commands and paths to work as expected.

On Windows _Powershell_, these substitutions are not required.

## Usage

1. The app can be run in the console with `./todo`.

2. The app reads from and writes to a `todo.txt` text file. Each task occupies a single line in this file. Here is an example file that has 2 todo items.

```txt
water the plants
change light bulb
```

3.  When a task is completed, it is removed from `todo.txt` and instead added to the `done.txt` text file. This file has a different format:

    ```txt
    x 2020-06-12 the text contents of the todo item
    ```

    1. the letter x
    2. the current date in `yyyy-mm-dd` format
    3. the original text

    The date when the task is marked as completed is recorded in the `yyyy-mm-dd` format (ISO 8601). For example, a date like `24th December, 2020` is represented as `2020-12-24`.

4. Help: 

Executing the command without any arguments, or with a single argument `help` prints the CLI usage.

```
$ ./todo help
Usage :-
$ ./todo add " task"  # Add a new task
$ ./todo ls               # Show remaining tasks
$ ./todo del NUMBER       # Delete a task
$ ./todo done NUMBER      # Complete a task
$ ./todo help             # Show usage
$ ./todo report           # Statistics
```

5. List all pending tasks: 

Use the `ls` command to see all the tasks that are not yet complete. The most recently added task should be displayed first.

```
$ ./todo ls
[2] change light bulb
[1] water the plants
```

6. Add a new task

Use the `add` command. The text of the task should be enclosed within double quotes (otherwise only the first word will be considered as the task, and the remaining words will be treated as different arguments).

```
$ ./todo add "the thing i need to do"
Added todo: "the thing i need to do"
```

7. Delete a task

Use the `del` command to remove a task by its number.

```
$ ./todo del 3
Deleted todo #3
```

Attempting to delete a non-existent task should display an error message.

```
$ ./todo del 5
Error: todo #5 does not exist. Nothing deleted.
```

8. Mark a task as completed

Use the `done` command to mark a task as completed by its number.

```
$ ./todo done 1
Marked todo #1 as done.
```

Attempting to mark a non-existed task as completed will display an error message.

```
$ ./todo done 5
Error: todo #5 does not exist.
```

9. Generate a report

Use the `report` command to see the latest tally of pending and completed tasks.

```
$ ./todo report
yyyy-mm-dd Pending : 1 Completed : 4
```

