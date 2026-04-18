# System Error Alert

🚧 Work in progress

A lightweight Linux system monitoring tool written in C.
It provides real-time insights into CPU usage, memory status, and running processes using data from `/proc`.

---

## ✨ Features

* 📊 Real-time CPU usage (per core)
* 🧠 Memory usage tracking
* 🧾 Basic process information
* ⚡ Non-blocking input (interactive UI)
* 🔄 Continuous screen refresh

---

## 🛠 Tech Stack

* Language: C
* Platform: Linux
* Data source: `/proc` filesystem

---

## 🚀 Build & Run

```bash
gcc test.c system.c ui.c -o sys_alert
./sys_alert
```

---

## ⌨️ Controls

| Key | Action       |
| --- | ------------ |
| 1   | CPU view     |
| 2   | Memory view  |
| 3   | Process view |
| q   | Quit         |

---

## 🧠 How it works

* Reads system data from `/proc`
* Calculates CPU usage using time delta
* Uses non-blocking input with `termios` and `fcntl`
* Updates UI in a loop without blocking

---

## 📌 Status

This project is under active development.
Future improvements may include:

* Sorting and filtering processes
* Better UI (ncurses)
* Alerts for high resource usage
