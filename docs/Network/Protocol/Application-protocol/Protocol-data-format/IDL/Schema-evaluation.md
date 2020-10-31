# Schema evaluation

支持Schema evaluation是本章所描述的几种库的优势，本文对这个主题进行展开。

## williamqliu [Data Exchange Formats (Avro, Thrift, Protocol Buffers)](https://williamqliu.github.io/2020/01/02/data-exchange-avro-thrift-protocolbuffers.html)

There are a lot of Data Exchange formats, each with its own use-case. Some include:

- JSON
- Protocol Buffers (Protobuf)
- Thrift
- AVRO

Things to consider:

- Efficency - Time and Space
- Ease/Speed of development

E.g. JSON vs Binary; Binary is very fast time and space, but hard to develop with because it is error prone

If you’re looking for a cross-language serialization of data using a **schema** (and requires **schema evolution**), but not sure which one to use, then here’s a comparison.

### schema evolution

If/When you change a **schema**, you’ll have producers and consumers with different versions at the same time. **Schema evolution** allows your producers and consumers to continue to work across schemas. Some concepts for **schema evolution** involve **forward** and **backward** compatibility.

#### schema evolution scenarios

Scenarios for forward and backward compatibility are:

- No change in fields
- Added field, old client (producer), new server (consumer)
- Removed field, old client (producer), new server (consumer)
- Added field, new client (producer), old server (consumer)
- Removed field, new client (producer), old server (consumer)

Scenario: No change in fields - producer (client) sends a message to a consumer (server) - all good e.g. MyMsg MyMsg user_id: 123 user_id: 123 amount: 1000 amount: 1000

Scenario: Added field - producer (old client) sends an old message to a consumer (new server); new server recognizes that the field is not set, and implements default behavior for out-of-date requests - all good e.g. MyMsg MyMsg user_id: 123 user_id: 123 amount: 1000 amount: 1000 time: 15

Scenario: Added field - producer (new client) sends a new message to a consumer (old server); old server simply ignores it and processes as normal - all good e.g. MyMsg MyMsg user_id: 123 user_id: 123 amount: 1000 amount: 1000 time: 15