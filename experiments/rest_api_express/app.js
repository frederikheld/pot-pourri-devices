'use strict'

var express = require('express')
var app = express()
var db = require('./db')

var router = require('./router')
app.use('/', router)

module.exports = app