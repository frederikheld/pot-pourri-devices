'use strict'

module.exports = function api(options) {

    var seneca = this


    // -- define actions

    seneca.add('role: test, cmd: home', home)
    seneca.add('role: test, cmd: hello_world', hello_world)


    // -- implement actions

    function home(args, respond) {
        respond(null, {
            msg: 'Welcome!'
        })
    }

    function hello_world(args, respond) {
        respond(null, {
            msg: "Hello World!"
        })
    }

}