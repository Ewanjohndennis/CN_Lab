# Computer Networks (CN) Lab

**Semester:** S5 (Common to CS/CD/CM/CB/CU/CI)  
**Course Code:** PCCSL507  

A repository dedicated to the Computer Networks Laboratory coursework, featuring implementations of network programming, client-server architectures, and low-level packet analysis written in C.

---

## Lab Status & Progress

* **Socket Programming (Experiments 5 – 10):** -> **Completed**
* **Warm-up & Wireshark Analysis (Experiments 1 – 4):** -> **Completed (Not Added)**
* **Cisco Packet Tracer / Routing & Security (Experiments 11 – 17):** -> *Coming Soon*

---

## Repository Structure

The completed socket programming experiments are organized inside the `Sockets/` directory:

```text
CN_Lab/
└── Sockets/
    ├── chatserver.c / chatclient.c               # Exp 7: Multi-user TCP chat application
    ├── packetcap.c                               # Exp 10: Raw socket packet-capturing sniffer
    ├── file_server.c / file_client.c             # Exp 9: Concurrent file server with PID
    ├── matrix_server.c / matrix_client.c         # Exp 5: TCP matrix type identifier
    ├── time_server.c / time_client.c             # Exp 8: UDP concurrent time server
    └── translator_server.c / translator_client.c # Exp 6: UDP slang/English translator
