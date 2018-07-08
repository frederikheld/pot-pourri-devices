'use strict'

var fs = require('fs')
var sqlite3 = require('sqlite3')

module.exports = function sensors_datastore(options) {

	// -- vars

	var db

	// -- action patterns

	this.add('init: sensors_datastore', init)

	this.add('role: sensors_datastore, cmd: add_datapoint', add_datapoint)
	this.add('role: sensors_datastore, cmd: get_datapoints_interval', get_datapoints_interval)

	// -- actions implemented

	function init(msg, respond) {

		var db_dir = './db';

		if (!fs.existsSync(db_dir)) {
			fs.mkdirSync(db_dir)
		}

		db = new sqlite3.Database(
			db_dir + '/data.db',
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

	function add_datapoint(msg, respond) {

		var query = `INSERT INTO sensor_log(sensor_id, value_raw, timestamp) VALUES(` +
			msg.data.sensor_id + `, ` + msg.data.value_raw + `, "` + msg.data.timestamp +
			`")`

		db.run(query, [],
			(err) => {
				if (err) {
					return respond(err)
				}

				console.log(query)
				respond()
			})


	}

	function get_datapoints_interval(msg, respond) {
		console.log('begin:' + msg.begin + ', end: ' + msg.end)

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

}