# Computer Networks (CN) Lab

**Semester:** S5 (Common to CS/CD/CM/CB/CU/CI)  
**Course Code:** PCCSL507

A repository containing the experiments performed as part of the **Computer Networks Laboratory**. It includes Linux networking fundamentals, protocol analysis using Wireshark, network programming using sockets in C, and routing/network simulation experiments.

---

## Lab Status

| Experiments | Topic | Status |
|-------------|-------|--------|
| 1 | Linux Networking Commands | ✅ Added |
| 2 | HTTP Analysis using Wireshark | ✅ Added |
| 3 | SMTP Analysis using Wireshark | ✅ Added |
| 4 | DNS Analysis using Wireshark | 🚧 Coming Soon |
| 5–10 | Socket Programming | ✅ Completed |
| 11–17 | Cisco Packet Tracer / Routing & Security | 🚧 Coming Soon |

---

## Repository Structure

```text
CN_Lab/
│
├── EXP1_COMMANDS.md          # Linux networking commands and modern alternatives
├── EXP2_WIRESHARK.md         # HTTP packet analysis using Wireshark
├── EXP3_SMTP.md              # SMTP protocol analysis using Wireshark
├── README.md
│
└── Sockets/
    ├── matrix_server.c
    ├── matrix_client.c
    ├── translator_server.c
    ├── translator_client.c
    ├── chatserver.c
    ├── chatclient.c
    ├── time_server.c
    ├── time_client.c
    ├── file_server.c
    ├── file_client.c
    └── packetcap.c
```

---

## Repository Contents

### Documentation-Based Experiments

- **Experiment 1:** Linux networking commands with explanations and modern alternatives.
- **Experiment 2:** HTTP packet analysis using Wireshark.
- **Experiment 3:** SMTP protocol analysis using Wireshark.
- **Experiment 4:** DNS packet analysis using Wireshark *(Coming Soon).*

### Socket Programming

Implementation of client-server applications using the Berkeley Socket API in C, covering:

- TCP and UDP communication
- Concurrent client handling
- File transfer
- Chat application
- Matrix type identification
- Slang translator
- Raw socket packet capturing

### Network Simulation

Cisco Packet Tracer experiments covering:

- Routing
- Switching
- VLANs
- Access Control Lists (ACLs)
- Network security

*(Will be added soon.)*

---

## Technologies Used

- C Programming
- Linux
- Berkeley Socket API
- Wireshark
- Cisco Packet Tracer

---

## Notes

- The repository follows the **KTU Computer Networks Lab (PCCSL507)** syllabus.
- Documentation-based experiments include explanations, procedures, observations, and viva questions.
- Legacy Linux networking commands are documented alongside their modern replacements wherever applicable.

---