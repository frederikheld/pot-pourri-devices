'use strict'

const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline

// The following settings should be set via GUI later:
var serialPortPath = '/dev/ttyACM0'

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
	})
})
