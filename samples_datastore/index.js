'use strict'


// -- imports

var argv = require('minimist')(process.argv.slice(2))
var express = require('express')
var router = require('./router')


// config

var port = argv.port || argv.p || 3000
// var dbPath = argv.db_path || argv.d || './db/data.db'
var apiRoot = argv.api_root || argv.a || '/api/v1'


// -- main

var app = express()
app.use(apiRoot, router)

var server = app.listen(port, () => {
	console.log("Server is listening on port " + port)
	console.log("API is accessible at http://localhost:" + port + apiRoot)
	console.log("To call from another machine in the same network, replace 'localhost' by the IP or hostname of this machine.")
})