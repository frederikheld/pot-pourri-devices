# build datastore:
cd datastore
sudo docker build -t pot-pourri-datastore .
cd ..

# build ui:
cd ui
sudo docker build -t pot-pourri-ui .
cd ..

# run datastore:
cd datastore
sudo docker run --rm --name pot-pourri-datastore -p 3000:3000 pot-pourri-datastore &
cd ..

# run ui:
cd ui
sudo docker run --rm --name pot-pourri-ui -p 3002:3002 pot-pourri-ui &
cd ..
