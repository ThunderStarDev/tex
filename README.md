# Tex

`Tex` is a high‑performance hex conversion tool written in C++17. It can convert a text string to its hexadecimal representation and back, either via command‑line arguments or an interactive prompt.

### Features
- Convert text to hex (`-tx`) and hex to text (`-xt`).  
- Interactive mode for on‑the‑fly conversions.  
- Simple, single‑source‑file implementation with no external libraries.  

### Prerequisites
- **g++** (or any C++17 ‑ compatible compiler).  
- **Make** (optional, for the provided Makefile).  

### Build & Install

```sh
# Compile and install to /usr/local/bin
make install
```

The above command builds the `tex` binary and copies it to `/usr/local/bin`.  

If you prefer a local binary without installing:

```sh
make        # produces ./tex in the project root
```

### Usage

```sh
tex                 # start interactive mode
tex -tx <text>      # text → hex
tex -xt <hex>       # hex → text
tex -h | --help     # display help
```

### Options

| Option | Description |
|--------|-------------|
| `-tx`  | Convert a **text** string to space‑separated hex bytes. |
| `-xt`  | Convert a space‑separated **hex** string to plain text. |
| `-h`, `--help` | Show the help message. |

### Examples

```sh
$ tex -tx hello
68 65 6C 6C 6F

$ tex -xt 68 65 6C 6C 6F
hello
```

### License

`Tex` is released under the **BSD 3‑Clause License**. See the [LICENSE](LICENSE) file for details.

### Contributing

Feel free to open issues or submit pull requests. Please follow the existing coding style and run `make` to ensure the build succeeds.
