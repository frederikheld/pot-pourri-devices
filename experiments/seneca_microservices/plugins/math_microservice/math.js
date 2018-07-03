'use strict'

module.exports = function math(options) {

	// --- action patterns

	// this.add('init: math', init)

	this.add('role: math, cmd: sum', sum)
	this.add('role: math, cmd: product', product)

	// --- wrapper

	this.wrap('role: math', function (msg, respond) {
		msg.a = Number(msg.a).valueOf()
		msg.b = Number(msg.b).valueOf()
		this.prior(msg, respond)
	})

	// --- actions implemented

	// function init(msg, respond) {
	// 	// nothing to do yet
	// }

	function sum(msg, respond) {
		var out = {
			answer: msg.a + msg.b
		}
		respond(null, out)
	}

	function product(msg, respond) {
		var out = {
			answer: msg.a * msg.b
		}
		respond(null, out)
	}

}