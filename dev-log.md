## Day 2 (2026-05-21)
- ✅ Implemented command router (help, clear, history, exit)
- ✅ Added whitespace trimming & input validation
- ✅ Cross-platform clear via preprocessor macro
- 📝 Notes: `std::getline` avoids `cin >>` buffer traps. `system("cls")` requires MSVC warning 4996 suppression.
- 🚧 Day 3: Matrix struct, row-major memory layout, `operator+`, `print()`, first unit tests.