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