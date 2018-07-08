'use strict'

const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline

var client = require('seneca')()
	.client()

// -- consts
// TODO: Should be set via parameter on start of the service

const serialPortPath = '/dev/ttyACM0'
const baudRate = 115200
const lineDelimiter = '\r\n'

// -- init

var serialConnection = new SerialPort(serialPortPath, {
	baudRate: baudRate
})
var serialParser = serialConnection.pipe(new Readline({
	delimiter: lineDelimiter
}))

// -- event handlers

// Read from serial connection:
serialConnection.on('open', () => {

	serialParser.on('data', (data) => {

		// Parse received json string:
		var jsonData = JSON.parse(data)

		// Add data:
		jsonData.timestamp = new Date().toISOString()

		// Alter data:
		jsonData.value_raw = jsonData.value_analog
		delete jsonData.value_analog

		console.log(jsonData)

		// Send data to datastore service:
		client.act('role: sensors_datastore, cmd: add_datapoint, data: ' + JSON.stringify(jsonData))

	})
})