Corewar
======

About
-----

>Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer.
These battle programs are written in an abstract assembly language called Redcode.

Let's run it !
-----

- Clone the repo \[NOTE: You'll need `ncurses` for this program to work\]
- `make` creates two binaries :
   - `asm` compiles 'warriors' from `.s` assembly source to `.cor` machine code
   - `corewar` is the VM which runs the game by loading `.cor` machine code inside a memory arena
- Compile champions contained in `./warriors/` using the `./asm warriors/*.s` command.
- Launch a game with `./corewar -visu champs/warrior1.cor champs/warrior2.cor [...]` (1 to 4 warriors can compete at the same time inside the VM)
