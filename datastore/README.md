This microservice provides access to the datastore via an api.

// todo: API documentation

You can this service as a stand-alone node app by just executing `npm start`. This is the quickest way for development.

For deployment you can run it inside a Docker container.

From within `/absolute/path/to/pot-pourri/datastore` first build it with

`$ docker build -t pot-pourri-datastore .`

Then run the container with

`$ docker run --rm --name pot-pourri-datastore -p 3000:3000 -v $(pwd)/db:/app/db pot-pourri-datastore`

This will mount the directory `./db` as a bind mount within the container at the same path relative to index.js. So no matter if you run the app stand-alone or in a container, it will always write to the same database

> I'm not quite sure if this is a good practice or an anti-pattern. Right now it supports my way of doing things but it might lead to interferences, if you develop and run the app on the same macheine - what I don't do anymore.
