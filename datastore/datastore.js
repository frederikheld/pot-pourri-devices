'use strict'

var fs = require('fs')
var sqlite3 = require('sqlite3')

module.exports = function datastore(options) {

	// -- vars

	var db

	// -- action patterns

	this.add('init: datastore', init)

	this.add('role: datastore, cmd: insert', insert)

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

	function insert(msg, respond) {

		db.run(`INSERT INTO sensor_log(sensor_id, value_raw, timestamp) VALUES(` +
			msg.data.sensor_id + `, ` + msg.data.value_raw + `, "` + msg.data.timestamp +
			`")`, [],
			(err) => {
				if (err) {
					return respond(err)
				}

				respond()
			})

	}

}