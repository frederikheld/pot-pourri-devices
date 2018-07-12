'use strict'


// config

var port = 3000
var dbPath = './db/data.db'

var apiRoot = '/api/v1'


// imports

var express = require('express')
var app = express()

var router = require('./router')
app.use(apiRoot, router)

var actions = require('./actions')

actions.initDB(dbPath)
	.catch((err) => {
		console.error(err)
	})
	.then((res) => {
		console.log("Database is ready.")

		var server = app.listen(port, () => {
			console.log("Server is listening on port " + port)
			console.log("You can call the API locally via http://localhost:" + port + apiRoot)
			console.log("If you want to call from another machine in the same network, replace 'localhost' by the IP or hostname that this machine has in this network.")
		})
	})