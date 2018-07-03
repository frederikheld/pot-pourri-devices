'use strict'

var fs = require('fs')

function math(options) {

	var log

	// --- patterns

	this.add('init :math', init)

	this.add('role: math, cmd: sum', sum)
	this.add('role: math, cmd: product', product)

	// --- actions

	function init(msg, respond) {
		fs.open(options.logfile, 'a', function (err, fd) {
			if (err) return respond(err)

			log = make_log(fd)
			respond()
		})
	}

	function sum(msg, respond) {
		var out = {
			answer: msg.a + msg.b
		}
		log('sum ' + msg.a + ' + ' + msg.b + ' = ' + out.answer + '\n')
		respond(null, out)
	}

	function product(msg, respond) {
		var out = {
			answer: msg.a * msg.b
		}
		log('product ' + msg.a + ' * ' + msg.b + ' = ' + out.answer + '\n')
		respond(null, out)
	}

	// --- helpers

	function make_log(fd) {
		return function (entry) {
			fs.write(fd, new Date().toISOString() + ' ' + entry, null, 'utf8', function (err) {
				if (err) return console.error(err)

				fs.fsync(fd, function (err) {
					if (err) return console.error(err)
				})
			})
		}
	}
}

// --- require

var seneca = require('seneca')()
	.use(math, {
		logfile: 'math.log'
	})

// --- try it

seneca.act('role: math, cmd: sum, a: 1, b: 2', console.log)