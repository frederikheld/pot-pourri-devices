'use strict'


// -- imports

var argv = require('minimist')(process.argv.slice(2))
var express = require('express')
var cors = require('cors')

var router = require('./router')


// config

var port = argv.port || argv.p || 3000
// var dbPath = argv.db_path || argv.d || './db/data.db'
var apiRoot = argv.api_root || argv.a || '/api/v1'


// -- main

var app = express()
app.use(cors()) // allow from all locations
app.use(apiRoot, router)

// allow access from different sources
app.use(function (req, res, next) {

	// Website you wish to allow to connect
	res.setHeader('Access-Control-Allow-Origin', '*');

	// Request methods you wish to allow
	res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

	// Request headers you wish to allow
	res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

	// Set to true if you need the website to include cookies in the requests sent
	// to the API (e.g. in case you use sessions)
	res.setHeader('Access-Control-Allow-Credentials', true);

	// Pass to next layer of middleware
	next();
});

var server = app.listen(port, () => {
	console.log("Server is listening on port " + port)
	console.log("API is accessible at http://localhost:" + port + apiRoot)
	console.log("To call from another machine in the same network, replace 'localhost' by the IP or hostname of this machine.")
})