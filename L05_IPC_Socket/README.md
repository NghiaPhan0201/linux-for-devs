# TCP Socket Project

This project demonstrates a simple client-server communication using IPv4 Stream Sockets (TCP) in C. The server listens for incoming connections, receives a message from the client, and sends a response back. The client connects to the server, sends a message, and displays the server's response.

## Project Structure

```bash
project/
├── include/
│   ├── tcp_server.h    # Header file for server functions and constants
│   └── tcp_client.h    # Header file for client functions and constants
├── src/
│   ├── tcp_server.c    # Server function implementations
│   ├── server_main.c   # Main server program
│   ├── tcp_client.c    # Client function implementations
│   └── client_main.c   # Main client program
├── bin/                # Directory for compiled executables (created by Makefile)
├── obj/                # Directory for object files (created by Makefile)
└── Makefile            # Build script for compiling the project
```

## Prerequisites

- A C compiler (e.g., `gcc`)
- A Unix-like operating system (Linux, macOS, etc.)
- `make` utility for building the project

## Building the Project

1. **Navigate to the project directory**:

   ```bash
   cd project
   ```

2. **Compile the project**:
   Run the following command to build both the server and client executables:

   ```bash
   make
   ```

   This will:
   - Create `obj/` and `bin/` directories if they don't exist.
   - Compile source files into object files (in `obj/`).
   - Link object files to create `bin/server` and `bin/client` executables.

## Running the Project

1. **Start the server**:
   Open a terminal and run the server:

   ```bash
   ./bin/server
   ```

   The server will listen on `127.0.0.1` at port `12345` and wait for a client connection.

2. **Run the client**:
   Open another terminal and run the client:

   ```bash
   ./bin/client
   ```

   The client will:
   - Connect to the server at `127.0.0.1:12345`.
   - Send a message ("Hello, Server!").
   - Receive and display the server's response.

3. **Expected Output**:

    Server:

    ```bash
    Waiting for server...
    Connected to client
    Data: Hello, Server!
    ```

   Client:

    ```bash
    Response from server: Recieved data!
    ```

## Cleaning Up

To remove compiled object files and executables, run:

```bash
make clean
```

This will delete the `obj/` and `bin/` directories' contents.

## Notes

- **Port**: The default port is `12345`. Ensure this port is not in use by other applications.
- **Address**: The server listens on `127.0.0.1` (localhost). Modify the code in `src/tcp_client.c` if you need to connect to a different IP address.
- **Error Handling**: The programs include basic error checking for socket creation, binding, and connection. Check terminal output for error messages if issues occur.

## Extending the Project

To add support for other socket types (e.g., IPv4 Datagram, Unix Stream, Unix Datagram):

1. Add corresponding header files to `include/`.
2. Add implementation and main files to `src/`.
3. Update the `Makefile` to include new object files and targets.

## License

This project is for educational purposes and has no specific license.
