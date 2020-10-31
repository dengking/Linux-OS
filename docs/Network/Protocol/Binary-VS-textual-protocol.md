# Classification of protocol

## Type of protocol

1) Binary protocol 

wikipedia [Binary protocol](https://en.wikipedia.org/wiki/Binary_protocol)

2) Textual protocol



下面是对它们的区分，从它们的区分中，能够充分理解它们各自的含义，优势。

## stackoverflow [binary protocols v. text protocols](https://stackoverflow.com/questions/2645009/binary-protocols-v-text-protocols)



Binary protocol versus text protocol isn't really about how binary blobs are encoded. The difference is really whether the **protocol** is oriented around **data structures** or around **text strings**. Let me give an example: HTTP. HTTP is a **text protocol**, even though when it sends a jpeg image, it just sends the **raw bytes**, not a text encoding of them.

But what makes HTTP a **text protocol** is that the exchange to *get* the jpg looks like this:

> NOTE: 上面这段话的意思是: 使HTTP是一个text protocol的是它请求*get* jpg的方式如下: 

Request:

```JSON
GET /files/image.jpg HTTP/1.0
Connection: Keep-Alive
User-Agent: Mozilla/4.01 [en] (Win95; I)
Host: hal.etc.com.au
Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, */*
Accept-Language: en
Accept-Charset: iso-8859-1,*,utf-8
```

Response:

```JSON
HTTP/1.1 200 OK
Date: Mon, 19 Jan 1998 03:52:51 GMT
Server: Apache/1.2.4
Last-Modified: Wed, 08 Oct 1997 04:15:24 GMT
ETag: "61a85-17c3-343b08dc"
Content-Length: 60830
Accept-Ranges: bytes
Keep-Alive: timeout=15, max=100
Connection: Keep-Alive
Content-Type: image/jpeg

<binary data goes here>
```

> NOTE: 显然在text protocol中，field name是需要被encode的，但是在binary protocol中，不需要encode fieldname，这是两者之间的主要差别之一。这导致了textual protocol耗费更多的空间。

Note that this could very easily have been packed much more tightly into a structure that would look (in C) something like

Request:

```C++
struct request {
  int requestType;
  int protocolVersion;
  char path[1024];
  char user_agent[1024];
  char host[1024];
  long int accept_bitmask;
  long int language_bitmask;
  long int charset_bitmask;
};
```

Response:

```c++
struct response {
  int responseType;
  int protocolVersion;
  time_t date;
  char host[1024];
  time_t modification_date;
  char etag[1024];
  size_t content_length;
  int keepalive_timeout;
  int keepalive_max;
  int connection_type;
  char content_type[1024];
  char data[];
};
```

Where the **field names** would not have to be transmitted at all, and where, for example, the `responseType` in the response structure is an int with the value 200 instead of three characters '2' '0' '0'. That's what a text based protocol is: one that is designed to be communicated as a flat stream of (usually human-readable) lines of text, rather than as structured data of many different types.



## medium [Use **Binary** Encoding Instead of JSON](https://medium.com/better-programming/use-binary-encoding-instead-of-json-dec745ec09b6)

In memory, the data is kept as data structures like objects, lists, arrays, etc. But when you want to send the data over a network or store it in a file, you need to encode the data as a **self-contained sequence of bytes**. The translation from the in-memory representation to a byte sequence is called **encoding** and the inverse is called **decoding**. With time, the **schema** for data that an application handles or stores may evolve, a new field can get added, or an old one can be removed. Therefore, the **encoding** used needs to support both **backward** (new code should be able to read the data written by the old code) and **forward** (old code should be able to read the data written by the new code) compatibility.

> NOTE: 关于encode、decode，参见工程programming-language的`Theory\Serialization`章节。

In this article, we will discuss different encoding formats, how **binary** encoding formats are better than JSON, XML, and how these support **schema evolution**.

### Types of Encoding Formats

There are two types of encoding formats:

1. Textual formats
2. **Binary** formats

### Textual Formats

Textual formats are somewhat human-readable. Some of the common formats are JSON, CSV, and XML. Textual formats are easy to use and understand but can result in different problems:

1) **Textual formats** can contain a lot of **ambiguity**. 

For example, in XML and CSV, you cannot distinguish between strings and numbers. 

JSON can distinguish between string and numbers but cannot distinguish between integers and floating numbers and doesn’t specify a precision. 

> NOTE: json中的字符串使用`""`指定，所以能够区分

This becomes a problem when dealing with large numbers. An example of numbers larger than 253 occurs on Twitter, which uses a 64-bit number to identify each tweet. The JSON returned by Twitter’s API includes tweet IDs twice — once as a JSON number and once as a decimal string — to work around the fact that the numbers are not correctly parsed by JavaScript applications.

> NOTE: 没有理解

2) CSV doesn’t contain any **schema**, leaving it to the application to define the meaning of each row and column.

> NOTE: 需要由application来定义每一行的含义

3) Textual formats take more space than **binary** encoding. For example, as JSON and XML are schema-less, they need to contain field names as well.

```json
{
    "userName": "Martin",
    "favoriteNumber": 1337,
    "interests": ["daydreaming", "hacking"]
}
```

Its JSON encoding after removing all the white spaces consumes 82 bytes.

### **Binary** Encoding

For data that is used only internally within your organization, you could choose a format that is more compact or faster to parse. Although JSON is less verbose than XML, they both still use a lot of space compared to **binary** formats. We will be discussing three different **binary** encoding formats in this article:

1) Thrift

2) **Protocol** Buffers

3) Avro

All three provide efficient, cross-language serialization of data using a **schema** and have **code generation tools**. All three support **schema evolution** by ensuring both backward and forward compatibility.

### Thrift and **Protocol** Buffers

Thrift is developed by Facebook and **Protocol** Buffers by Google. Both of them require schema for data to be encoded. In Thrift, the schema is defined using Thrift’s interface definition language (IDL).

```C++
struct Person {
  1: string       userName,
  2: optional i64 favouriteNumber,
  3: list<string> interests
}
```

The equivalent schema for **Protocol** Buffers is:

```c++
message Person {
    required string user_name        = 1;
    optional int64  favourite_number = 2;
    repeated string interests        = 3;
}
```

As you can see, both define a **data type** and **tag number** (as `1`, `2`, and `3`) for each field. Thrift has two different **binary** encoding formats: `BinaryProtocol` and `CompactProtocol`*.* The **binary** format is straightforward, as shown below, and takes 59 bytes to encode the data above.

The compact **protocol** is semantically equivalent to the **binary** **protocol** but packs the same information in just 34 bytes. It does this by packing the field type and tag number in a single byte.

**Protocol** Buffers also encode the data similarly to Thrift’s compact **protocol** and take 33 bytes to encode the same data.

**Tag numbers** ensure schema evolution in Thrift and **Protocol** Buffers. If an old code tries to read the data written with a **new schema**, it will simply ignore the fields with new tag numbers. Similarly, new code can read the data written by an old schema by putting the values as `null` for missing tag numbers.

### Avro

Avro is different from **Protocol** Buffers and Thrift. Avro also uses a schema to define the data. Schema can be defined using Avro’s IDL (intended for human readability):

```c++
record Person {
    string               userName;
    union { null, long } favouriteNumber;
    array<string>        interests;
}
```

Or JSON (more machine-readable):

```json
"type": "record",
    "name": "Person",
    "fields": [
        {"name": "userName",        "type": "string"},
        {"name": "favouriteNumber", "type": ["null", "long"]},
        {"name": "interests",       "type": {"type": "array",      "items": "string"}}
    ]
}
```

Notice that there are no **tag numbers** with each field. Avro encoding takes just 32 bytes to encode the same data.

As you can see in the byte sequence above, there is no way to identify a field (like using a tag number in Thrift and **Protocol** Buffers) or its data type. The values are simply concatenated together. Does this mean any change in the schema while decoding would generate incorrect data? The key idea with Avro is that the writer and reader’s schema do not need to be the same, but they do need to be compatible. When the data is decoded, Avro’s library resolves the difference by looking at both schemas and translating the data from the writer’s schema to reader’s schema.

You must be thinking about how the reader will know about the writer’s schema. This depends on the use case where such encoding is used.

1. For transferring large files or data, the writer can include their schema once at the beginning of the file.
2. For a database with individually written records, each row can be written with a different schema. The simplest solution is to include a version number at the beginning of each record and to keep the list of schemas.
3. For sending a record over a network, the reader and writer can negotiate the schema on connection setup.

One of the main advantages of using the Avro format is it supports dynamically generated schemas. Since it doesn’t use tag numbers, you can use versioning to keep different records encoded with different schemas.

### Conclusion

In this article, we looked into textual and **binary** encoding formats, how the same data takes 82 bytes with JSON encoding, 33 bytes using Thrift and **Protocol** Buffers, and just 32 bytes using Avro encoding. **Binary** formats offer several compelling advantages over JSON for sending data over the wire between internal services.

### Resources

To know more about encoding and designing data-intensive applications, I highly recommend reading Martin Kleppmann’s book *Designing Data-Intensive Applications*.