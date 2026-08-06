# Experiment 1 - Familiarization with Linux Networking Commands

## Objective

To familiarize with commonly used Linux networking commands for network configuration, troubleshooting, monitoring, and packet analysis.

---

## Overview

Linux provides numerous utilities for viewing network information, testing connectivity, monitoring traffic, and troubleshooting network issues. While some commands in the lab manual are considered legacy, they are still included for academic purposes along with their recommended modern alternatives.

> **Note:** This experiment follows the KTU lab manual. Where applicable, modern replacements for deprecated or legacy commands are also provided.

---

# Commands

## 1. ifconfig *(Legacy)*

Displays or configures network interfaces.

```bash
ifconfig
```

### Modern Alternative

```bash
ip addr
```

**Purpose:** View IP addresses, subnet masks, and interface status.

---

## 2. ifplugstatus *(Legacy / Less Common)*

Checks whether an Ethernet cable is connected.

```bash
ifplugstatus
```

### Modern Alternatives

```bash
ip link
```

or

```bash
ethtool eth0
```

**Purpose:** Check the operational state of a network interface.

---

## 3. iftop

Displays real-time network bandwidth usage.

```bash
sudo iftop
```

**Purpose:** Monitor active network connections and bandwidth consumption.

---

## 4. ping

Tests connectivity with another host.

```bash
ping google.com
```

**Purpose:** Measure packet loss and network latency.

---

## 5. ip

Modern utility for network configuration.

Display interfaces:

```bash
ip addr
```

Display routing table:

```bash
ip route
```

Display link status:

```bash
ip link
```

**Purpose:** Configure and inspect network interfaces, routes, and links.

---

## 6. traceroute

Displays the route taken by packets to reach a destination.

```bash
traceroute google.com
```

### Alternative

```bash
tracepath google.com
```

**Purpose:** Identify intermediate routers and diagnose routing issues.

---

## 7. mtr

Combines the functionality of ping and traceroute.

```bash
mtr google.com
```

**Purpose:** Continuously monitor packet loss and latency across network hops.

---

## 8. netstat *(Legacy)*

Displays network connections and listening ports.

```bash
netstat -tuln
```

### Modern Alternative

```bash
ss -tuln
```

**Purpose:** View active TCP/UDP connections and listening services.

---

## 9. whois

Retrieves registration details of a domain.

```bash
whois google.com
```

**Purpose:** Obtain domain ownership and registration information.

---

## 10. nmap

Network scanning and security auditing tool.

```bash
nmap localhost
```

**Purpose:** Discover hosts, open ports, and running services.

---

## 11. nmcli

Command-line interface for NetworkManager.

Display devices:

```bash
nmcli device
```

Show saved connections:

```bash
nmcli connection show
```

**Purpose:** Manage network connections from the terminal.

---

## 12. speedtest-cli *(Legacy)*

Measures Internet download and upload speeds.

```bash
speedtest-cli
```

### Modern Alternative

```bash
speedtest
```

*(Requires Ookla Speedtest CLI)*

**Purpose:** Measure Internet connection performance.

---

## 13. bmon

Bandwidth monitoring utility.

```bash
bmon
```

**Purpose:** Monitor network bandwidth usage graphically in the terminal.

---

## 14. nslookup *(Legacy)*

Queries DNS servers.

```bash
nslookup google.com
```

### Modern Alternatives

```bash
dig google.com
```

or

```bash
host google.com
```

**Purpose:** Resolve domain names to IP addresses and troubleshoot DNS.

---

## 15. tcpdump

Captures and analyzes network packets.

Capture packets:

```bash
sudo tcpdump
```

Capture packets on a specific interface:

```bash
sudo tcpdump -i eth0
```

**Purpose:** Perform packet-level network analysis.

---

# Summary

| Command | Purpose | Modern Alternative |
|----------|---------|-------------------|
| ifconfig | Interface configuration | ip addr |
| ifplugstatus | Link status | ip link, ethtool |
| iftop | Bandwidth monitoring | iftop |
| ping | Connectivity testing | ping |
| ip | Network configuration | ip |
| traceroute | Route tracing | tracepath |
| mtr | Network diagnostics | mtr |
| netstat | Network connections | ss |
| whois | Domain information | whois |
| nmap | Port scanning | nmap |
| nmcli | NetworkManager CLI | nmcli |
| speedtest-cli | Internet speed test | speedtest |
| bmon | Bandwidth monitoring | bmon |
| nslookup | DNS lookup | dig, host |
| tcpdump | Packet capture | tcpdump |

---

# Result

Successfully familiarized with Linux networking commands used for network configuration, troubleshooting, monitoring, and packet analysis.
