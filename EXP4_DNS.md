# Experiment 4: Analyzing DNS Protocol Traffic

## Objective
This experiment demonstrates how to capture and analyze **Domain Name System (DNS)** traffic using **Wireshark** by performing a host lookup for Model Engineering College (`mec.ac.in`).

---

## 1. Experimental Procedure & Steps Undertaken

### Step 1: Clearing Host DNS Cache
To ensure the operating system sends an actual DNS query over the network rather than retrieving an IP address from local memory, the local DNS resolver cache was flushed.

- **On Windows:**
  ```cmd
  ipconfig /flushdns
  ```
- **On Linux (systemd-resolved):**
  ```bash
  sudo systemd-resolve --flush-caches
  # Or on newer distributions:
  sudo resolvectl flush-caches
  ```

### Step 2: Clearing Browser Cache
Browser cache and socket pools were cleared to prevent the browser from serving cached host mappings or reusing existing HTTP/HTTPS connections.

### Step 3: Packet Capture Initiation
1. Opened **Wireshark** and selected the active network interface (e.g., `eth0` or `Wi-Fi`).
2. Clicked the **Start Capturing Packets** (blue shark fin) button.

### Step 4: Web Request Execution
1. Opened the web browser and navigated to:
   ```
   http://mec.ac.in
   ```
2. Waited for the homepage of Model Engineering College to fully load.

### Step 5: Filtering & Saving Capture
1. In the Wireshark display filter bar, typed:
   ```
   dns
   ```
   and pressed **Enter** / clicked **Apply**.
2. Stopped the packet capture.
3. Saved the capture file as `dns_analysis_mec.pcapng` (`File -> Save As...`).

---

### **Questions & Answers**

**(a) Locate the first DNS query message resolving your college website. What is the packet number in the trace for the DNS query message?**
* **Answer:** **Packet #9**  
* *Detail:* Frame 9 in the trace shows the outgoing DNS query packet (`Protocols in frame: eth:ethertype:ipv6:udp:dns`).

---

**(b) Is this query message sent over UDP or TCP?**
* **Answer:** **UDP**  
* *Detail:* The Next Header field in the IPv6 header is set to `UDP (17)`, and the transport layer protocol is explicitly listed as `User Datagram Protocol`.

---

**(c) Now locate the corresponding DNS response to the initial DNS query. What is the packet number in the trace for the DNS response message? Is this response message received via UDP or TCP?**
* **Answer:** **Packet #20** received via **UDP**.  
* *Detail:* Frame 20 is marked as `[Request In: 9]` and carries the `Standard query response 0xc870` over UDP.

---

**(d) What are the source and destination port numbers for the DNS query message?**
* **Answer:**
  * **Source Port:** `55664`
  * **Destination Port:** `53`

---

**(e) What are the source and destination port numbers for the DNS response message?**
* **Answer:**
  * **Source Port:** `53`
  * **Destination Port:** `55664`

---

**(f) To what IP address is the DNS query message sent?**
* **Answer:** `2405:201:f020:70c9::c0a8:1d01` (IPv6 recursive DNS resolver address).

---

**(g) What is the query message ID number? What is the response message ID number? What is the purpose of this field?**
* **Answer:**
  * **Query Transaction ID:** `0xc870`
  * **Response Transaction ID:** `0xc870`
  * **Purpose:** The Transaction ID matches a connectionless DNS response to its original request so the client host can map incoming answers to outstanding queries when multiple lookups are active concurrently.

---

**(h) What is the length of the flag field in a DNS message?**
* **Answer:** **16 bits** (2 bytes).  
* *Detail:* Seen as hexadecimal `0x0100` in the query and `0x8180` in the response.

---

**(i) Which bit in the flag field determines whether the message is a query or a response?**
* **Answer:** The **QR (Query/Response) bit**, which is the **most significant bit (Bit 0)** of the Flags field.
  * `0` = Query (`0x0100` has leading binary bit `0`)
  * `1` = Response (`0x8180` has leading binary bit `1`)

---

**(j) Which bits are used only in the response message? What is the function of these bits in the response message?**
* **Answer:**
  * **Authoritative Answer (AA) [Bit 5]:** Specifies if the responding server is an authoritative server for the queried domain.
  * **Truncated (TC) [Bit 6]:** Specifies if the DNS message was truncated due to exceeding the maximum permitted length over UDP.
  * **Answer Authenticated (AD) [Bit 10]:** Indicates whether the returned data was validated by DNSSEC.
  * **Reply Code / Response Code (RCODE) [Bits 12–15]:** Indicates the status of the query (e.g., `0` for `No error`, `3` for `NXDomain`).

---

**(k) How many question records, answer records, authority records, and additional records are present in the query message?**
* **Answer:**
  * **Questions:** `1`
  * **Answer RRs:** `0`
  * **Authority RRs:** `0`
  * **Additional RRs:** `0`

---

**(l) How many question records, answer records, authority records, and additional records are present in the response message?**
* **Answer:**
  * **Questions:** `1`
  * **Answer RRs:** `1`
  * **Authority RRs:** `0`
  * **Additional RRs:** `0`
