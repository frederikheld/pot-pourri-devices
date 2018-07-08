'use strict'

var client = require('seneca')()
    .client()

// -- Settings (should later be made in ui)

// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 24 // 24 h
var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 24 * 10 // 10 d


// -- actions implemented

function poll_sensors_datastore(begin, end = new Date().toISOString()) {

    var date = new Date()
    var begin = new Date(date.getTime() - datapoints_interval_in_microseconds)
    var end = new Date(date.getTime())

    // Query data from sqlite_select_datastore:
    console.log('begin: ' + begin + ', end: ' + end)
    client.act(
        'role: sqlite_select_datastore, cmd: get_datapoints_interval', {
            begin: begin,
            end: end
        },
        (error, reply) => {
            if (error) {
                return console.error(error)
            }
            console.log("reply: " + JSON.stringify(reply))
        })

}

var poll_datapoints_timer = setInterval((start) => {
    poll_sensors_datastore(start)
}, 1000, "dummy")