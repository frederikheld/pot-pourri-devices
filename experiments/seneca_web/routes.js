'use strict'

module.exports = [{
    pin: 'role: test, cmd: *',
    map: {
        hello_world: {
            GET: true
        },
        home: {
            GET: true,
            POST: true,
            alias: '/'
        }
    }
}]