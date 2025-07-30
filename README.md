# 🧭 Minimalist HTTP Server in C

This is a minimalist HTTP server written in C, compatible with both **Windows** and **Linux** platforms. It uses system-level socket programming to accept connections and return a simple HTTP response to clients.

## ⚙️ Features

- Basic HTTP 1.1 response handler  
- Handles one request at a time (sequential model)  
- Compatible with:
  - 🐧 **Linux (POSIX)** via BSD sockets  
  - 🪟 **Windows** via WinSock 2

## 🚀 Getting Started

### 📦 Requirements

- GCC or Clang on Linux  
- MinGW or MSYS2 on Windows (with `ws2_32` library)  
- Basic C knowledge

### 🛠 Build Instructions

#### Linux

```bash
gcc main.c server.c -o myServer
./myServer
```

#### Windows

```bash
gcc main.c server.c -o myServer.exe -lws2_32
./myServer.exe
```

> ⚠️ Make sure to **run the executable from PowerShell or CMD**, and use a **non-privileged port (e.g. 8080)** unless running as administrator.

---

## 🌐 Test the Server

Once the server is running, open your browser or use `curl`:

```bash
curl http://localhost:8080
```

You should see the following response:

```html
<!DOCTYPE html>
<html>
<head><title>Testing Basic HTTP-SERVER</title></head>
<body>Hello, Visitor!</body>
</html>
```

---

## 🔄 Cross-Platform Architecture

This project uses conditional compilation via `#ifdef _WIN32` to separate Windows and Linux-specific socket behavior. Types and function calls such as `recv/send` vs. `read/write`, and `closesocket()` vs. `close()`, are all abstracted to support both systems cleanly.

---

## 📌 Future Improvements

- [ ] Modularize platform-specific code (`socket_utils.c/h`)  
- [ ] Add multi-threading or `select()`/`poll()` support  
- [ ] Handle HTTP methods and status codes properly  
- [ ] Support persistent connections or HTTP 1.1 pipelining  
- [ ] Improve logging and error handling  
- [ ] Package as a library or learning toolkit  

---

## 🧑‍💻 Author

Made with ❤️ as a learning project. Feel free to fork and expand.

---

## 📄 License

This project is open source and available under the MIT License.
