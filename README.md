# tcpp: a c++ wrapper for formatted messages over tcp sockets

In my work, I find myself writing the long boilerplate of BSD sockets repeatedly. This is a c++ wrapper to encapsulate that.
It offers the convenience of using stream formatting to read and write to sockets. The interface is very simple. On the server side:

```C++
/* listening socket on port, implements accept */
ServerSocket server(8000);
RWSocket client_socket = server.accept();

// now read and write
client_socket >> n;
client_socket << n * n;
```

For the client side:

```C++
// connect to (ip, port)
RWSocket server_connection("127.0.0.1", 8000);

// now read and write
server_connection << n;
server_connection >> n_square;
```
