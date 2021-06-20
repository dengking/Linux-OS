# HTTP persistent connection



## wanweibaike [HTTP persistent connection](https://en.wanweibaike.com/wiki-HTTP_persistent_connection)

**[HTTP](https://en.wanweibaike.com/wiki-HTTP) persistent connection**, also called **HTTP keep-alive**, or **HTTP connection reuse**, is the idea of using a single [TCP](https://en.wanweibaike.com/wiki-Transmission_Control_Protocol) connection to send and receive multiple [HTTP requests](https://en.wanweibaike.com/wiki-Hypertext_Transfer_Protocol)/responses, as opposed to opening a new connection for every single request/response pair. The newer [HTTP/2](https://en.wanweibaike.com/wiki-HTTP/2) protocol uses the same idea and takes it further to allow multiple concurrent requests/responses to be multiplexed over a single connection.

### Operation

#### Keepalive with [chunked transfer encoding](https://en.wanweibaike.com/wiki-Chunked_transfer_encoding)

> NOTE: 
>
> message boundary、粘包

Keepalive makes it difficult for the client to determine where one response ends and the next response begins, particularly during pipelined HTTP operation.[[8\]](https://en.wanweibaike.com/wiki-HTTP_persistent_connection#cite_note-8) This is a serious problem when `Content-Length` cannot be used due to streaming.[[9\]](https://en.wanweibaike.com/wiki-HTTP_persistent_connection#cite_note-9) To solve this problem, HTTP 1.1 introduced a [chunked transfer coding](https://en.wanweibaike.com/wiki-Chunked_transfer_coding) that defines a `last-chunk` bit.[[10\]](https://en.wanweibaike.com/wiki-HTTP_persistent_connection#cite_note-10) The `last-chunk` bit is set at the end of each response so that the client knows where the next response begins.

### Use in web browsers

All modern web browsers including [Google Chrome](https://en.wanweibaike.com/wiki-Google_Chrome), [Firefox](https://en.wanweibaike.com/wiki-Firefox), [Internet Explorer](https://en.wanweibaike.com/wiki-Internet_Explorer) (since 4.01), [Opera](https://en.wanweibaike.com/wiki-Opera_(web_browser)) (since 4.0)[[14\]](https://en.wanweibaike.com/wiki-HTTP_persistent_connection#cite_note-14) and [Safari](https://en.wanweibaike.com/wiki-Safari_(web_browser)) use persistent connections.





## csdn [HTTP协议浅谈（一）之TCP长连接](https://blog.csdn.net/huangyuhuangyu/article/details/78220005)