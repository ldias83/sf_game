## Rock-Paper-Scissors ##  

A compact yet **heavily-modular C++17** implementation of the classic game.  
Ideal for portfolio use: it highlights **clean OOP design, dependency injection, Factory pattern**, and thorough unit-testing while staying small enough for a quick read.

---

### Features ###  

* **Single-player console game** (user vs computer)  
* **Pluggable interfaces** for players, messaging back-ends, and game sessions  
* **Factory registration** of new modes – add sessions without editing existing code  
* **Deterministic, unit-testable core logic** (`SinglePlayerRpsGame`) with mocks  
* **Extensive Google Test suite** – 20 + unit tests, all passing  
* **Cross-platform**: standard C++17 + CMake ≥ 3.10, builds on Linux / macOS / Windows  

---

### Project Layout ###  

inc/ # Public headers
src/ # Production .cpp files
tst/ # Google Test / Mock units
.vscode/ # Optional editor tasks / launch configs
CMakeLists.txt # Top-level build script


| Header | Purpose |
| ------ | ------- |
| `IPlayer.hpp`, `UserPlayer.hpp`, `ComputerPlayer.hpp` | Participant abstraction & concrete players |
| `IGameMessenger.hpp`, `ConsoleMessenger.hpp` | I/O layer (console today, GUI tomorrow) |
| `IGameSession.hpp`, `SinglePlayerRpsGame.hpp` | Game-loop abstraction & concrete implementation |
| `GameSessionFactory.hpp`, `GameMode.hpp`, `GameMove.hpp` | Factory pattern & enumerations |

---

### Build & Run ###  

#### Requirements ####  
* C++17 compiler (GCC 9+, Clang 9+, MSVC 2019+)  
* CMake 3.10 +  
* (Optional) Google Test – fetched automatically if absent  

#### Build ####  

```bash
# Configure
cmake -S . -B bld -DCMAKE_BUILD_TYPE=Release \
      -DROCK_PAPER_SCISSORS_BUILD_TESTS=ON   # toggle tests

# Build
cmake --build bld --parallel


# Linux / macOS
./bld/game

# Windows (MSVC)
bld\Release\game.exe


### Unit tests ###  

cd bld
./rps_tests                 # run directly
# or
ctest --output-on-failure   # via CTest
```

### Design Overview ###  

#### Architecture & Responsibilities ####  

- **Players** – `UserPlayer`, `ComputerPlayer`  
- **Core logic** – `SinglePlayerRpsGame`  
- **Sessions** – `IGameSession` abstraction  
- **Messaging / I/O** – `IGameMessenger`, `ConsoleMessenger`  
- **Object creation** – `GameSessionFactory` (registers lambdas keyed by `GameMode`)  
- **Enumerations** – `GameMove`, `GameMode`  

Interfaces decouple components; swapping console I/O for a GUI requires no changes to game logic.

#### Patterns & SOLID ####  

| Pattern / Principle | Where | Benefit |
| ------------------- | ----- | ------- |
| **Factory Pattern** | `GameSessionFactory` | Open-closed – new modes plug in via registration |
| **Dependency Injection** | `SinglePlayerRpsGame` constructor | Decoupling, easy mocking |
| **Single Responsibility** | One focus per class | Maintainability |
| **Open-Closed** | Add modes / messengers with no edits | Extensibility |
| **Liskov Substitution** | Any `IPlayer` / `IGameMessenger` | Robust polymorphism |
| **Interface Segregation** | Small, focused interfaces | No “fat” APIs |
| **Dependency Inversion** | High-level modules depend on abstractions | Flexible architecture |

#### Game-Loop Algorithm ####  

1. **Setup** – messenger gathers names & round count.  
2. **Round loop**  
   - **User move** via messenger (`RequestMoveChoice`).  
   - **Computer move** via injected RNG (`std::rand()` seeded once).  
   - `constexpr` helpers classify outcome (`IsRoundDraw`, `DoesUserWinRound`).  
   - Scores updated; messenger announces result.  
3. **Finalisation** – messenger prints the final scoreboard.
