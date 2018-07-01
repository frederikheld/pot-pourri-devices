'use strict'

const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline

const sqlite3 = require('sqlite3').verbose()

// The following settings should be set via GUI later:
var serialPortPath = '/dev/ttyACM0'

// Prepare database:
let db = new sqlite3.Database('./db/data.db', (error) => {
	if (error) {
		return console.error(error.message)
	}
	console.log('Successfully connected to the SQLite database')

	db.run(`CREATE TABLE IF NOT EXISTS sensor_log(
		id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
		sensor_id INTEGER NOT NULL,
		value_analog INTEGER NOT NULL,
		timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
	)`)

})

// Prepare serial connection:
var serialConnection = new SerialPort(serialPortPath, {
	baudRate: 9600
})
var serialParser = serialConnection.pipe(new Readline({
	delimiter: '\r\n'
}))

// Read from serial connection:
serialConnection.on('open', () => {
	console.log("Serial Port " + serialPortPath + " successfully opened")

	serialParser.on('data', (data) => {
		console.log("Data received: " + data)

		try {

			// Parse string:
			var jsonData = JSON.parse(data)

			// Write to database:
			db.run(`INSERT INTO sensor_log(sensor_id, value_analog) VALUES(` + jsonData.sensor_id + `, ` + jsonData.value_analog + `)`, [], (error) => {
				if (error) {
					return console.error(error.message)
				}

				// Close database connection:
				// db.close((error) => {
				// 	if (error) {
				// 		return console.error(error.message)
				// 	}
				// 	console.log('Database connection closed')
				// })

			})
		} catch (error) {
			return console.error(error.message)
		}
	})
})
