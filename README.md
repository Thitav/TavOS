# TavOS

TavOS is a minimal 32bit toy OS made completely for fun and learning purposes.

## Building

### Setup cross compiler

Setup the [cross compiling toolchain](https://wiki.osdev.org/GCC_Cross-Compiler) or use the [Dockerfile](.devcontainer/Dockerfile) for building inside of a container.

### Compiling

```bash
make all
```

## Emulating

### Installing QEMU

Install [QEMU](https://www.qemu.org/) for emulating the OS (other emulators can work as well).

### Running

```bash
qemu-system-i386 -fda ./bin/os.bin
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
