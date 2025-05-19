# Chat Application

A command-line peer-to-peer chat application implemented in C using POSIX sockets and threads.

## Features
- Command-line interface with commands: `help`, `myip`, `myport`, `connect`, `list`, `terminate`, `send`, `exit`.
- Supports multiple concurrent TCP connections.
- Handles errors for invalid inputs, disconnections, and message length limits.
- Thread-safe connection management with mutexes.
- No memory leaks (verified with Valgrind).

## Requirements
- POSIX-compliant system (Linux/macOS).
- GCC compiler.
- POSIX threads library (`pthread`).

## Build Instructions
```bash
cd chat_app
make
```

## Usage
```bash
./build/bin/chat_app <port>
```
Example: `./build/bin/chat_app 4322`

## Commands
- `help`: Display available commands.
- `myip`: Show the machine's IP address.
- `myport`: Show the listening port.
- `connect <ip> <port>`: Connect to a peer.
- `list`: List all active connections.
- `terminate <id>`: Terminate a connection by ID.
- `send <id> <message>`: Send a message to a connection.
- `exit`: Close all connections and exit.

## Testing
- Run multiple instances on different ports or machines.
- Test all commands and error cases (e.g., invalid IP, long messages).
- Use Valgrind to check for memory leaks:
  ```bash
  valgrind --leak-check=full ./build/bin/chat_app 4322
  ```

## Directory Structure
- `src/`: Source files.
- `include/`: Header files.
- `build/`: Build artifacts (obj/, bin/).
- `tests/`: Placeholder for tests.
- `docs/`: Documentation.
