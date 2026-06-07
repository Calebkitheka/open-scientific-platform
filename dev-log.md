## Day 2 (2026-05-21)
- ✅ Implemented command router (help, clear, history, exit)
- ✅ Added whitespace trimming & input validation
- ✅ Cross-platform clear via preprocessor macro
- 📝 Notes: `std::getline` avoids `cin >>` buffer traps. `system("cls")` requires MSVC warning 4996 suppression.
- 🚧 Day 3: Matrix struct, row-major memory layout, `operator+`, `print()`, first unit tests.

## Day 3 (2026-05-22)
- ✅ Built Matrix struct with row-major 1D vector layout
- ✅ Implemented safe indexing, dimension validation, formatted printing
- ✅ Added REPL `test` command with automated verification
- 📝 Notes: `data[r * cols + c]` avoids pointer indirection overhead. `vector<vector>` is cache-unfriendly for scientific workloads.
- 🚧 Day 4: Basic expression parsing (`A = [1,2;3,4]`), REPL variable storage, tokenization.

## Day 4 (2026-05-23)
- ✅ Implemented matrix literal parser: `[1, 2; 3, 4]`
- ✅ Added workspace symbol table (`unordered_map`) for variable storage
- ✅ Safe REPL with `try/catch` recovery & identifier validation
- 📝 Notes: `std::stringstream` + `getline` with delimiters is cleaner than manual char iteration for CSV-like parsing. Never let parser crashes kill the shell.
- 🚧 Day 5: Binary expression evaluation (`A + B`, `A * B`), operator precedence basics, runtime error handling.

## Day 5 (2026-05-24)
- ✅ Built lexer/tokenizer for identifiers, numbers, + - *
- ✅ Implemented left-to-right expression evaluator with scalar/matrix dispatch
- ✅ Added MATLAB-style `ans` auto-capture for direct expressions
- 📝 Notes: Treating scalars as 1x1 matrices simplifies type system. Full matrix-matrix multiplication (dot product) requires nested loops & will be Day 6. Left-associative evaluation avoids complex AST for now.
- 🚧 Day 6: True matrix multiplication (dot product), operator precedence (`*` before `+`), basic error recovery improvements.

## Day 6 (2026-05-25)
- ✅ Implemented O(N^3) matrix-matrix dot product with inner-dimension validation
- ✅ Built recursive descent parser (factor → term → expression) for correct precedence
- ✅ Added matrix subtraction & cleaned parser architecture
- 📝 Notes: Recursive descent is the foundation of all modern language parsers. `*` binds tighter than `+/-` naturally via call hierarchy. Dimension checks prevent silent numerical corruption.
- 🚧 Day 7: Matrix transposition, determinant (2x2/3x3), basic error recovery, workspace save/load (JSON).