'use strict'

var seneca = require('seneca')()

seneca.add('role:math, cmd:product', (msg, respond) => {
	respond(null, {
		answer: (msg.a * msg.b)
	})
})

seneca.act({
	role: 'math',
	cmd: 'product',
	a: 3,
	b: 4
}, function (err, res) {
	if (err) {
		return console.log(err)
	}
	console.log(res)
})