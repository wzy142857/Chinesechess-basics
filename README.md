# Chinesechess-basics
A CLI-based Chinese Chess engine implemented in C, featuring complex move validation logic and binary state persistence.
# Chinese Chess Logic Engine (C-based)

A command-line interface (CLI) implementation of Chinese Chess (Xiangqi), focused on rigorous game logic and state management.

## 🛠 Features
- **Rigid Move Validation**: Implemented custom algorithms for all piece types, including complex constraints like "Horse's leg" (马腿) and "Elephant's eye" (象眼).
- **Specialized Mechanics**: Full support for "Cannon" (炮) jumping logic and "General" (将) line-of-sight restrictions.
- **State Persistence**: Developed a binary file I/O system (`fread`/`fwrite`) to save and resume game sessions.
- **Dynamic CLI Rendering**: Real-time board visualization using ANSI escape sequences for color-coded feedback.

## 💻 Tech Stack
- **Language**: C (Standard I/O, String Manipulation)
- **Concepts**: Matrix-based board mapping, binary file handling, complex conditional logic.

## 🚀 How to Run
1. Compile the source: `gcc main.c -o chess`
2. Run the executable: `./chess`
