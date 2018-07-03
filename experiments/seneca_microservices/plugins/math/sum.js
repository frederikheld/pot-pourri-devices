'use strict'

var seneca = require('seneca')()

seneca.add(
		'role:math, cmd:sum',
		function (msg, respond) {
			var sum = msg.a + msg.b
			respond(null, {
				answer: sum
			})
		})
	.add(
		'role: math, cmd: sum',
		function (msg, respond) {

			if (!Number.isFinite(msg.a) || !Number.isFinite(msg.b)) {
				return respond(new Error("Expected a and be to be numbers."))
			}

			this.prior(
				'role:math, cmd: sum, a: ' + msg.a + ', b: ' + msg.b,
				function (err, result) {
					if (err) {
						return respond(err)
					}

					result.info = msg.a + ' + ' + msg.b
					respond(null, result)
				})
		})

seneca.add(
	'role: math, cmd: sum, integer: true',
	function (msg, respond) {
		this.act({
			role: 'math',
			cmd: 'sum',
			a: Math.floor(msg.a),
			b: Math.floor(msg.b)
		}, respond)
	})

// --- call actions:

seneca.act(
	'role: math, cmd: sum, a: 1, b: 2',
	(err, res) => {
		if (err) {
			return console.log(err)
		}
		console.log(res)
	})

seneca.act(
	'role: math, cmd: sum, a: 1.5, b: 2.5',
	(err, res) => {
		if (err) {
			return console.log(err)
		}
		console.log(res)
	})

seneca.act(
	'role: math, cmd: sum, a: 1.5, b: 2.5, integer: true',
	(err, res) => {
		if (err) {
			return console.log(err)
		}
		console.log(res)
	})