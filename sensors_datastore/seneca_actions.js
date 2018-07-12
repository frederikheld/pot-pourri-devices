'use strict'

var fs = require('fs')
var sqlite3 = require('sqlite3')
var mkdirp = require('mkdirp')
var path = require('path')

var actions = new Object();


// -- config

const db_path = './db/data.db'


// -- actions implemented

actions.init = function (msg, respond) {

    var dir = path.dirname(db_path)
    mkdirp(dir, function (err) {
        if (err) {
            return console.error(err)
        } else {
            // return console.log('Successfully created "' + dir + '" to store database.')
        }
    });

    var db = new sqlite3.Database(
        db_path,
        (err) => {
            if (err) return console.log(err)
        })

    db.run(`CREATE TABLE IF NOT EXISTS sensor_log(
        		id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        		sensor_id INTEGER NOT NULL,
        		value_raw INTEGER NOT NULL,
        		timestamp TEXT NOT NULL
        	)`)

    respond()
}

actions.add_datapoint = function (msg, respond) {

    // Some devices can't set a timestamp because they have no clock.
    // In this case the timestamp has to be added here.
    if (!msg.data.hasOwnProperty('timestamp')) {
        msg.data.timestamp = new Date().toISOString()
    }

    var db = new sqlite3.Database(
        db_path,
        (err) => {
            if (err) return console.log(err)
        })

    var query = `INSERT INTO sensor_log(sensor_id, value_raw, timestamp) VALUES(` +
        msg.data.sensor_id + `, ` + msg.data.value_raw + `, "` + msg.data.timestamp +
        `")`

    db.run(query, [],
        (err) => {
            if (err) {
                console.log(err)
                return respond(err)
            }

            console.log(query)
            respond()
        })

}

actions.get_datapoints_interval = function (msg, respond) {
    console.log('begin:' + msg.begin + ', end: ' + msg.end)

    var db = new sqlite3.Database(
        db_path,
        (err) => {
            if (err) return console.log(err)
        })

    var query = `SELECT *
					FROM sensor_log
					WHERE timestamp
						BETWEEN ?
						AND ?
					ORDER BY timestamp
						ASC`

    db.all(query, [msg.begin, msg.end],
        (err, rows) => {
            if (err) {
                return respond(err)
            }

            respond({
                data: rows
            })
        })

}

module.exports = actions;