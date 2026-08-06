# Computer Networks Lab - SMTP Experiment Report & Analysis

## 1. Environment & Wireshark Setup (Loopback Interface)
To capture the local SMTP traffic, Wireshark was configured to capture on the **Loopback interface (`lo`)** using TCP filtering, since both the client (`telnet`/script) and the server (`aiosmtpd`) run locally on `localhost`. 

The local SMTP server was started using:
```bash
python3 -m aiosmtpd -n -l localhost:8025
```
## 2. Interactive SMTP Session via Telnet
The client-server SMTP dialogue was performed manually using telnet:

```bash
root@dell-Vostro-3470:/home/mec# telnet localhost 8025
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
220 dell-Vostro-3470 Python SMTP 1.1
HELO localhost
250 dell-Vostro-3470
MAIL FROM <sender@test.com>
501 Syntax: MAIL FROM: <address>
MAIL FROM: <sender@test.com>
250 OK
RCPT TO: <receiver@test.com>
250 OK
DATA
354 End data with <CR><LF>.<CR><LF>
From:sender@test.com
To:receiver@test.com
Subject:SMTP Test Mail
This is a test mail to study SMTP Mail Packet Sending
.
250 OK
QUIT
```
### 3. Lab Questions & Answers

### (a) *All SMTP packets have the same two IP addresses. Which one is the IP address of your computer? Which host does the other IP address represent?*
* **IP address of your computer:** `127.0.0.1` (IPv4 loopback address).
* **Other host represented:** Since this is a local loopback test (`localhost`), both source and destination are `127.0.0.1`, representing the same local machine acting as both client and server.

### (b) *All SMTP packets have the same two port numbers. Which one is the port number of the SMTP client process? In which range is the client port number?*
* **Client port number:** A dynamically assigned temporary ephemeral port (e.g., high-numbered port like `5XXXX`).
* **Range:** Dynamic/ephemeral port range (`49152` to `65535`).

### (c) *What is the port number of the SMTP server process?*
* **Server port number:** `8025` (specified during the server launch).

### (d) *Examine the SMTP commands or SMTP response codes in each SMTP packet and write down their meanings.*
| Command / Response | Description |
| :--- | :--- |
| `220 dell-Vostro-3470 Python SMTP 1.1` | Server greeting banner indicating readiness. |
| `HELO localhost` | Client greeting handshake. |
| `MAIL FROM: <sender@test.com>` | Specifies the sender address (note: initial syntax error 501 resolved with proper angle brackets format). |
| `RCPT TO: <receiver@test.com>` | Specifies the recipient address. |
| `DATA` | Initiates the transmission of the email body. |
| Message Body Content | Contains the From, To, Subject headers and the message payload, terminated by a period (.) on a line by itself. |
| `250 OK` | Server confirmation that the email was accepted. |
| `QUIT` | Terminates the SMTP session. |

### (e) *There is an IMF packet that is encapsulated inside an SMTP packet. What is the content of this packet?*
The IMF packet encapsulated inside the `DATA` stream contains:
```bash
From:sender@test.com
To:receiver@test.com
Subject:SMTP Test Mail
This is a test mail to study SMTP Mail Packet Sending
```
