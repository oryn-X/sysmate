# Sysmate

Simple CLI utility scaffold in C, organized into modules.

## Project Layout

```
sysmate/
├── src/
│   ├── main.c
│   ├── commands.c
│   ├── ui.c
│   └── system_ops.c
├── include/
│   ├── commands.h
│   ├── ui.h
│   └── system_ops.h
├── build/
├── Makefile
└── README.md
```

## Build

```bash
make
```

## Run

```bash
./build/sysmate update
./build/sysmate clean
./build/sysmate ls
./build/sysmate -dr-dev
```

## Clean

```bash
make clean
```
