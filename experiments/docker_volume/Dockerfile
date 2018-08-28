# choose the base image to build upon
FROM node:9.11-alpine

# define working directory
WORKDIR /app

# add application code
COPY ./hello_world.sh ./

# run the app
CMD ["sh", "hello_world.sh"]
