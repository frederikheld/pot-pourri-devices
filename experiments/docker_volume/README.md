# What does it do?

Anytime you run this container, it will add a line to the file hello.txt in the bound volume.

# Build and run

## With docker

Build this image:

`$ docker build -t pot-pourri_experiment_docker-volume .`

Run the container:

`$ docker run -v /absolute/path/to/pot-pourri/experiments/docker_volume/volumes/db:/db pot-pourri_experiment_docker-volume`

## With docker-compose

Build this image:

`$ docker-compose build`

Run the container:

`$ docker-compose up`

# Access volume

The volume will be bind mounted. So basically it's a folder that can be accessed from within the container as well as from the host.

It will be mounted inside the container at /db. So _inside the container_ you can write to it like

`$ echo "Hello World!" >> /db/hello.txt`

You can access the file _on the host_ like

`$ cat ./volumes/db/hello.txt`
