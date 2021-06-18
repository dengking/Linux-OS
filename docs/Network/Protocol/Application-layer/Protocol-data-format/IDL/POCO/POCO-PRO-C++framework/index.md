# [POCO-PRO C++ FRAMEWORKS](https://pocoproject.org/pocopro.html)



## REMOTING FOR C++

**MULTI-PROTOCOL STACK AND CODE GENERATOR**

> NOTE： 
>
> 一、它的code generator是让我感兴趣的
>
> 二、从下面的描述来看，它包含两个code generator:
>
> 1、Remoting code generator
>
> 后面的"REST API SAMPLE"章节展示了它的例子	
>
> 2、SOAP AND WSDL/XSD-TO-C++ CODE GENERATION

Remoting for C++ is a web services and remote method call framework for C++. Remoting supports different communication protocols. This includes JSON-based REST APIs, JSON-RPC, SOAP and a highly efficient binary protocol.

Remote services are implemented as C++ classes, annotated with special comments. The Remoting code generator takes care of the rest. There is no need to maintain a separate interface definition using an interface definition language (IDL).

**SOAP AND WSDL/XSD-TO-C++ CODE GENERATION**

Remoting also includes a tool for generating C++ code from WSDL 1.1 (document/literal wrapped) and XML Schema (XSD) documents. This makes it possible to build C++ clients for SOAP 1.1 and 1.2 web services built with Java, Microsoft .NET, or other middleware technologies.



### REST API SAMPLE

> NOTE: 
>
> 它的这种风格是类似于Java、Python的

The following code snipped shows an example for how to define a RESTful API with Remoting. This definition is specific to the Remoting REST transport. Note how the method names correspond to HTTP methods. Also note the special comments. The Remoting code generator (RemoteGen) parses these definitions and generates C++ code that implements serialization, deserialization and remote invocation.

```cpp
//@ serialize
struct User
{
    Poco::Optional<std::string> name;
    Poco::Optional<std::string> password;
    Poco::Optional<std::set<std::string>> permissions;
    Poco::Optional<std::set<std::string>> roles;
};

//@ remote
//@ path="/api/1.0/users"
class UserCollectionEndpoint
{
public:
    User post(const User& user);
        /// Create a new user.

    //@ $maxResults={in=query, optional}
    //@ $start={in=query, optional}
    std::vector<User> get(int maxResults = 0, int start = 0);
        /// Return a list of user objects, starting with
        /// the given start index, and return at most
        /// maxResults items.
};

//@ remote
//@ path="/api/1.0/users/{name}"
class UserEndpoint
{
public:
    //@ $name={in=path}
    User put(const std::string& name, const User& user);
        /// Update a user (calls patch()).

    //@ $name={in=path}
    User patch(const std::string& name, const User& user);
        /// Update a user.

    //@ $name={in=path}
    User get(const std::string& name);
        /// Retrieve a user by name.

    //@ $name={in=path}
    void delete_(const std::string& name);
        /// Delete a user.
};
```

## OPEN SERVICE PLATFORM

> NOTE: 
>
> 和HS CRES middleware 非常类似

**BUILD, DEPLOY AND MANAGE DYNAMIC, MODULAR C++ APPLICATIONS**

Open Service Platform (OSP) enables the creation, deployment and management of dynamically extensible, modular applications, based on a powerful plug-in and (nano-) services model. Applications built with OSP can be extended, upgraded and managed even when deployed in the field. At the core of OSP lies a powerful software component (plug-in) and services model based on the concept of bundles. A bundle is a deployable entity, consisting of both executable code (shared libraries) and the required configuration, data and resource files.

**PLUG-IN AND SERVICE-BASED ARCHITECTURE**



![Open Service Platform](https://pocoproject.org/images/osp.png)
