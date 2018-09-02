This microservice provides a web UI for pot-pourri.

The microservice runs in a Docker container.

To build this image run

`$ docker build -t pot-pourri-ui .`

To run the container run

`$ sudo docker run --rm --name pot-pourri-ui -p 3002:3002 pot-pourri-ui`
