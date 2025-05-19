# Chat Application Design

## Overview
A peer-to-peer chat system using TCP sockets and POSIX threads, supporting multiple concurrent connections and a command-line interface.

## Architecture
- **chat_app.c**: Main entry point and CLI logic.
- **connection.c**: Manages the connection list.
- **network.c**: Handles socket setup and communication.
- **utils.c**: Utility functions (IP validation, string trimming).
- **chat_app.h**: Defines structs and prototypes.

## Key Components
- **ChatApp struct**: Global state (server socket, host, port, connections, mutex).
- **Connection struct**: Represents a connection (ID, socket, address, active status).
- **Threading**: Uses pthreads for concurrency, with a mutex for thread safety.
- **Error Handling**: Checks for invalid inputs, socket errors, and disconnections.

## Non-Functional Requirements
- **Performance**: Multi-threaded for concurrent connections.
- **Reliability**: Robust error handling.
- **Memory Management**: Proper resource cleanup.
- **Clean Code**: Modular design, clear naming, no duplication.