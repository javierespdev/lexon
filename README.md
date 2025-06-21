<table>
  <tr>
    <td>

<h1>Lexon</h1>

<p><strong>Lexon</strong> is a lightweight pseudocode interpreter implemented in C++ using Flex and Bison. It supports intuitive syntax, typed variables, screen commands, conditionals, loops, and more.</p>

</td>
<td align="right" valign="top">
  <div style="margin-top:90px;">
    <img src="docs/images/lexon.png" alt="Lexon Logo" width="300"/>
  </div>
</td>
  </tr>
</table>

## Grammar Specification

Lexon is designed to be readable, expressive, and extendable. Below is a complete reference to its grammar, including keywords, syntax rules, and supported operations.

## Reserved Keywords and Constants

| Control Statements | Screen Commands | Constants  |
|--------------------|-----------------|------------|
| read               | clear_screen    | true       |
| read_string        | place           | false      |
| print              |                 | pi         |
| if                 |                 | e          |
| then               |                 | gamma      |
| else               |                 | deg        |
| end_if             |                 | phi        |
| while              |                 |            |
| do                 |                 |            |
| end_while          |                 |            |
| repeat             |                 |            |
| until              |                 |            |
| for                |                 |            |
| from               |                 |            |
| to                 |                 |            |
| step               |                 |            |
| end_for            |                 |            |
| switch             |                 |            |
| case               |                 |            |
| default            |                 |            |
| end_switch         |                 |            |

- **Case-insensitive:** `Print`, `PRINT`, and `print` are equivalent.
- Reserved words cannot be used as identifiers.

## Identifiers

- Must begin with a **letter**.
- Can include **letters**, **digits**, and **underscores** (`_`).
- Cannot end in `_` or contain consecutive underscores (`__`).
- Examples:
  - ✅ `total`, `x_1`, `user_name`
  - ❌ `_var`, `data_`, `value__x`

## Numbers

- Supported formats:
  - Integer: `123`
  - Real: `12.34`
  - Scientific: `3.14e+2`
- All are treated as numeric values with floating-point support.

## Strings

- Defined with single quotes: `'text'`
- Escape sequences:
  - `\n`: newline
  - `\t`: tab
  - `\'`: single quote
- Example: `'Line:\n\tIndented'`

## Operators

### Arithmetic
| Operation     | Symbol  | Description         |
|---------------|---------|---------------------|
| Addition      | `+`     | Unary/Binary        |
| Subtraction   | `-`     | Unary/Binary        |
| Multiplication| `*`     |                     |
| Division      | `/`     | Floating-point      |
| Integer Div   | `//`    | Truncated result    |
| Modulo        | `mod`   | Remainder           |
| Power         | `^`     | Exponentiation      |

### String
- Concatenation: `||`

### Relational
| Operator       | Symbol |
|----------------|--------|
| Equal          | `=`    |
| Not Equal      | `<>`   |
| Less Than      | `<`    |
| Greater Than   | `>`    |
| Less or Equal  | `<=`   |
| Greater or Equal | `>=` |

### Logical
- `or`, `and`, `not`

## Requirements

To build and run Lexon, make sure the following are installed:

- `g++` (C++ compiler)
- `flex` (lexer generator)
- `bison` (parser generator)
- `make` (build tool)

On Ubuntu/Debian systems:

```bash
sudo apt update
sudo apt install g++ flex bison make
```

## Running the Interpreter

To compile and execute a Lexon program:

```bash
git clone https://github.com/yourusername/lexon.git
cd lexon
make
./interpreter.exe program.p
```

For interactive mode:

```bash
./interpreter.exe
```