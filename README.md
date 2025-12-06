# 🔢 Infix Expression Calculator in C (Infix to Postfix Converter & Evaluator)

This project is a simple console application written in the C language that first converts a mathematical **Infix expression** into a **Postfix expression**, and then **evaluates** the final result. The program is designed to handle operator precedence, parenthesis usage, and multi-digit numbers.

## ✨ Key Features

* **Infix to Postfix Conversion:** Implements a simplified version of the shunting-yard algorithm for conversion.
* **Postfix Evaluation:** Reads the postfix expression and calculates the final arithmetic result using a stack.
* **Multi-Digit Number Support:** Correctly processes numbers like `10`, `123`, etc., using a space separator in the postfix notation.
* **Operator Precedence:** Correctly applies mathematical precedence rules (`*`, `/` before `+`, `-`).
* **Robust Error Handling:** The code includes checks for:
    * Unbalanced or mismatched parentheses (`(` or `)`).
    * Division by zero.
    * Invalid characters within the expression.
    * Stack overflow and underflow conditions.

## 🚀 Usage

### Pre-compiled Executable (Windows Users)

A pre-compiled `.exe` file is available for Windows users who prefer not to compile the source code themselves.

1.  Download the `calculator.exe` file from the [link to your release/folder].
2.  Open your Command Prompt or PowerShell, navigate to the download location, and run the file:
    ```bash
    ./calculator.exe
    ```

> **Note:** Due to security concerns, always refer to the source code (`calculator.c`) to ensure the compiled executable is safe. This file is intended for quick testing only.

### Compilation and Running (All Platforms)
Use the following commands in your terminal to compile and run the code:

```bash
# Compile the code
gcc calculator.c -o calculator

# Run the program
./calculator
