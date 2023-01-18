# Docker Image Layers



## vsupalov [What Are Docker Image Layers?](https://vsupalov.com/docker-image-layers/)



## packagecloud [What Are Docker Image Layers?](https://blog.packagecloud.io/what-are-docker-image-layers/)

### **Docker Layers** **Explained** 

Layers are what make up an image. Each layer is a “diff” that contains the changes made to the image since the last one was added. When building an image, the platform creates a new layer for each instruction in the file. The container starts at the first instruction in the file and executes all instructions in order. The first instruction might install packages, while later instructions might copy files or create directories. 

#### **imagedb**

The imagedb is an image database that stores information about the **Docker layers** and the relationships between them (for example, how one depends on the other). The Docker daemon stores the imagedb. The daemon is the process that runs on the host machine and manages containers. When running a container, the platform uses this database to retrieve information about each layer.

  

#### **layerdb**

The layerdb is a database that holds information about the relationship between layers. It also holds instructions for building layers. This database is stored in the daemon. When running a container using an image, the Docker daemon uses both the imagedb and layerdb to start the container.

