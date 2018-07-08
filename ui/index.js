'use strict'

var express = require('express')
var path = require("path")


// -- Settings (should later be made in ui)

// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 24 // 24 h


// -- Publish web interface (client)

function publish_webinterface() {
    var app = express()

    app.use(express.static(path.join(__dirname, "web")))
    app.get("/", function (request, result) {
        result.sendFile(path.join(__dirname, "web", "index.html"))
    })

    app.listen(3000, () => console.log("ui listening on port 3000"))
}
publish_webinterface()

// -- Provide communication between client and server:

var client = require('seneca')()
    .client()

// var latest_local_timestamp = initTimestamp(datapoints_interval_in_microseconds)
// With the first request we have to poll all data for the selected interval.
// After that we will only poll the delta.

var poll_datapoints_timer = setInterval((timestampGeneartor) => {
    poll_sensors_datastore(timestampGeneartor())
    // }, 1000, latest_local_timestamp)
}, 1000, intervalOneHour)
// var poll_datapoints_timer = setInterval(poll_sensors_datastore.bind(null, latest_local_timestamp), 1000)
// We have to use polling here since seneca-pubsub
// is broken and development will not be continued.
// On the other hand sensors_datastore should not know
// about possible subscribers. Sending every datapoint
// as it ist stored explicitly from the datastore to
// the ui would be bad style.

function intervalOneHour() {
    return initTimestamp(60 * 60)
}

function initTimestamp(start) {
    var now_minus_interval = new Date().getTime() - start
    return new Date(now_minus_interval).toISOString()
}

function poll_sensors_datastore(begin, end = new Date().toISOString()) {

    // Query data from sensors_datastore:
    console.log('begin: ' + begin + ', end: ' + end)
    var data = client.act(
        'role: sensors_datastore, cmd: get_datapoints_interval, begin: ' + begin + ', end: ' + end,
        (error, reply) => {
            sendReplyToUi(reply)
            // latest_local_timestamp = extractLatestTimestamp(reply)
        })

    // Send to ui:
    function sendReplyToUi(data) {
        console.log("reply: " + JSON.stringify(data))
    }

    // Extract latest local timestamp and save for next interval:
    function extractLatestTimestamp(data) {
        var latest_timestamp = initTimestamp(datapoints_interval_in_microseconds) // this is just until I have the real data
        // return latest_timestamp
        return Math.random()
    }

}