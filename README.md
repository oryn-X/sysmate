# Sysmate

**Sysmate** is a simple CLI utility written in C. It combines useful system and developer tasks into one tool.

## Social Media

Stay connected:

- GitHub M0SAIF-ANTNET: https://[github.com/USERNAME/sysmate](https://github.com/M0SAIF-ANTNET)
- GitHub oryn-X: https://[github.com/USERNAME/sysmate](https://github.com/oryn-X)
- Discord https://discord.gg/v38BhC8f

## Features

- Update system packages
- Clean unused files and cache
- List files in the current directory
- Build `.sysmate_index`
- Delete files by index
- Check development tools with `doctor-dev`

## Project Layout

```text
sysmate/
├── src/
│   ├── main.c
│   ├── commands.c
│   ├── help.c
│   ├── ui.c
│   └── system_ops.c
├── include/
│   ├── commands.h
│   ├── help.h
│   ├── ui.h
│   └── system_ops.h
├── build/
├── Makefile
└── README.md
```

## Installation

Install Sysmate for your current user.

### From GitHub

````bash
git clone https://github.com/oryn-X/sysmate.git
cd sysmate
make install-user
## Build

```blocks
make
````

## Run from project folder

```text
./build/sysmate help
./build/sysmate version
./build/sysmate update
./build/sysmate clean
./build/sysmate ls
./build/sysmate delete 3
./build/sysmate doctor-dev
```

## Install for current user

```blocks
make install-user
```

## If sysmate is not found after installation, add this once:

```blocks
export PATH="$HOME/.local/bin:$PATH"
```

## Then reload your shell:

```blocks
source ~/.bashrc
```

## Now you can run:

```blocks
sysmate help
sysmate ls
sysmate doctor-dev
```

## Uninstall

```blocks
make uninstall-user
```

## Notes

```text
ls creates a file named .sysmate_index
delete uses the index stored in .sysmate_index
Run sysmate ls before using delete
doctor-dev checks core development tools
```

## Clean build files

```blocks
make clean
```
