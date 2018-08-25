1.  Install Docker according to the official guideline that you can find here https://docs.docker.com/install/

    > This package is tested with Docker CE on Ubuntu 18.04

1.  Build image: `$ sudo docker build -t pot-pourri-example-docker .`. The last parameter tells Docker where to look for the Dockerfile.

1.  Run container: `$ sudo docker run --name dockerized_web_app -p 3333:3333 pot-pourri-example-docker`

1.  Run container that auto-deletes itself after stopping: `$ sudo docker run --rm --name dockerized_web_app -p 3333:3333 pot-pourri-example-docker`

1.  List all containers: `$ sudo docker ps -a`

1.  List all running containers: `$ sudo docker ps`

1.  Stop container: `$ sudo docker stop <container_tag>`. You can do this from a different command line.

1.  Remove container: `$ sudo docker rm <container_id>`
