# AUR Package Manager

This is a simple command-line tool for managing packages from the Arch User Repository (AUR) on Arch Linux.

## Installation

1. Make sure you have Git installed. If not, run the following command to install it:

```shell
sudo pacman -S git
```

2. Clone this repository:

```shell
git clone https://github.com/coronux/aur-package-manager.git
```

3. Change to the cloned directory:

```shell
cd aur-package-manager
```

4. Compile the program:

```shell
gcc -o aur main.c
```

## Usage

```shell
./aur [-i|-r] package_name
```

### Options

- `-i`: Install a package from the AUR.
- `-r`: Remove a package installed from the AUR.

### Example

To install a package from the AUR:

```shell
./aur -i package_name
```

To remove a package installed from the AUR:

```shell
./aur -r package_name
```

## Requirements

- Arch Linux
- Git
- GCC (GNU Compiler Collection)

## License

This project is licensed under the MIT License. See the LICENSE file for more information.

---

Made with ❤️ by Coronux
