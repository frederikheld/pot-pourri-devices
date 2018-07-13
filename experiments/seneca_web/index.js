'use strict'


/*
 * Public api with seneca and express
 */

var seneca = require('seneca')()
var seneca_web = require('seneca-web')
var adapter = require('seneca-web-adapter-express')
var express = require('express')()

var routes = require('./routes.js')
var api = require('./api.js')


// -- configure api server

var config = {
    routes: routes,
    adapter: adapter,
    context: express,
    // options: {
    //     parseBody: true
    // }
}


// -- create api server

seneca
    .use(api)
    .use(seneca_web, config)
    .ready(() => {
        var app = seneca.export('web/context')()
        app.listen(3001, () => {
            console.log('API server started. Listening on port 3001.')
        })
    })