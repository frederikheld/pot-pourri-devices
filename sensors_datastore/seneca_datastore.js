'use strict'

var actions = require('./seneca_actions')

module.exports = function sensors_datastore(options) {

	// -- action patterns

	this.add('init: sensors_datastore', actions.init)

	this.add('role: sensors_datastore, cmd: add_datapoint', actions.add_datapoint)
	this.add('role: sensors_datastore, cmd: get_datapoints_interval', actions.get_datapoints_interval)


}