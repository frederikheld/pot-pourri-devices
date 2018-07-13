'use strict'


// config

var port = 3000
var dbPath = './db/data.db'

var apiRoot = '/api/v1'


// -- imports

var express = require('express')
var app = express()

var router = require('./router')
app.use(apiRoot, router)

var server = app.listen(port, () => {
	console.log("Server is listening on port " + port)
	console.log("API is accessible at http://localhost:" + port + apiRoot)
	console.log("To call from another machine in the same network, replace 'localhost' by the IP or hostname of this machine.")
})