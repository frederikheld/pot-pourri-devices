'use strict'

const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline

const request = require('request')


// -- consts
// TODO: Should be set via parameter on start of the service

const serialPortPath = '/dev/ttyACM0'
const baudRate = 115200
const lineDelimiter = '\r\n'

const apiRoot = 'http://localhost:3000/api/v1'


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
		try {
			var jsonData = JSON.parse(data)
		} catch (err) {
			console.log('JSON object incomplete: ' + data)
			return
		}

		// Add data:
		jsonData.timestamp = new Date().toISOString()

		// Alter data:
		// jsonData.value_raw = jsonData.value_analog
		// delete jsonData.value_analog
		// delete jsonData.value_digital
		// Not needed right now but kept as an example

		console.log("data: " + JSON.stringify(jsonData))

		request({
			url: apiRoot + '/samples',
			method: 'POST',
			json: jsonData
		}, (err, res, body) => {
			if (!err && res.statusCode === 201) {
				console.log(res.statusCode + ': ' + body.msg)
			} else {
				console.error('Error: ' + err)
				console.error('response.statusCode: ' + res.statusCode)
				console.error('response.statusText: ' + res.statusText)
			}
		})

	})
})

// TODO: Program crashes at json parsing if data chunk received is not complete