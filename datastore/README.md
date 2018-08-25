This microservice provides access to the datastore via an api.

// todo: API documentation

The microservice runs in a Docker container.

To build this image run

`$ docker build -t pot-pourri-datastore .`

To run the container run

`$ sudo docker run --rm --name pot-pourri-datastore -p 3000:3000 pot-pourri-datastore`
