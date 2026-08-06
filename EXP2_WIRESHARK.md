# Experiment 2 - HTTP Packet Analysis using Wireshark

## Objective

To capture HTTP packets using Wireshark and analyze HTTP request and response headers.

---

## Software Required

- Wireshark
- Web Browser
- Internet Connection

---

## Procedure

1. Open Wireshark.
2. Select the active network interface.
3. Start packet capture.
4. Clear browser cache.
5. Visit any HTTP website.
6. Stop packet capture.
7. Apply the filter:

```text
http
```

8. Select the first HTTP GET packet.
9. Analyze the HTTP request and response.

---

## Parameters to Observe

### (a) Source and Destination IP Address

Found under:

```
Internet Protocol (IPv4)
```

Example

```
Source IP      : 192.168.1.5
Destination IP : 93.184.216.34
```

---

### (b) Client Accept Information

From the HTTP GET request, observe:

- Accept
- Accept-Language
- Accept-Encoding
- Accept-Charset (if present)

Example

```
Accept: text/html
Accept-Language: en-US
Accept-Encoding: gzip, deflate
```

---

### (c) URL and User-Agent

Observe:

```
Host:
```

and

```
User-Agent:
```

Example

```
Host: example.com

User-Agent:
Mozilla/5.0 ...
```

---

### (d) Source and Destination IP of Response

Check the corresponding HTTP Response packet.

Example

```
Source IP      : Server IP
Destination IP : Client IP
```

---

### (e) HTTP Status Code

Look for

```
HTTP/1.1 200 OK
```

Common Status Codes

| Code | Meaning |
|------|---------|
|200|OK|
|301|Moved Permanently|
|302|Redirect|
|404|Not Found|
|500|Internal Server Error|

---

### (f) Last Modified Date

Look for

```
Last-Modified:
```

Example

```
Last-Modified:
Mon, 15 Jun 2026 08:30:00 GMT
```

---

### (g) Content-Length

Look for

```
Content-Length:
```

Example

```
Content-Length: 6480
```

---

### (h) Response Time

Calculate

```
Response Time =
Response Timestamp − GET Timestamp
```

Example

```
GET Sent:
12.541 s

Response Received:
12.582 s

Time Taken:
0.041 seconds
```

---

### (i) HTTP Version

Observe

```
HTTP/1.1

or

HTTP/2
```

---

## Observation

The captured packets contain HTTP request and response headers including source/destination IP addresses, accepted media types, browser information, status codes, response size, and response time.

---

## Result

Successfully captured and analyzed HTTP packets using Wireshark and examined the important fields in HTTP request and response messages.

---