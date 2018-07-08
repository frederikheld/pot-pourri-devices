'use strict'

var date = new Date()

console.log(date)
console.log(date.getTime())

var nowMinus24h = date.getTime() - 1000 * 60 * 60 * 24
console.log(nowMinus24h)
console.log(new Date(nowMinus24h).toISOString())

var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 24 // 24 h
var begin = new Date(date.getTime() - datapoints_interval_in_microseconds)
var end = new Date(date.getTime())
console.log('begin: ' + begin.toISOString())
console.log('end:   ' + end.toISOString())