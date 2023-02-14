# pipex

| Project Name | pipex |
| :-: | :-: |
| Description | Using multiprocessing to implement Pipe command |
| Technologies | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries | open(), close(), read(), write(), malloc(), free(), perror(), strerror(), access(), dup(), dup2(), execve(), exit(), fork(), pipe(), unlink(), wait(), waitpid()|
| Final grade | 100/100 |

## Usage
```
git clone https://github.com/robinbnc/pipex.git
cd pipex
make
./pipex file1 command1 command2 file2
```
Equivalent on bash to:
$ command1 < file1 | command2 > file2;
