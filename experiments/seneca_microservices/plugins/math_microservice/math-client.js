'use strict'

var seneca_client = require('seneca')()
	.client()

seneca_client.act('role: math, cmd: sum, a: 3, b: 5', console.log)