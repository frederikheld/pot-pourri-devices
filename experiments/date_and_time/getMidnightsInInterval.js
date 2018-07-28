'use strict'

function getMidnightsInInterval(startTime, endTime) {

    var time = startTime
    var midnights = new Array()
    while (true) {

        time = new Date(
            time.getFullYear(),
            time.getMonth(),
            time.getDate() + 1
        )

        if (time < endTime) {
            midnights.push(time)
        } else {
            break
        }

    }

    return midnights

}

var date = new Date()
var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 72 // 72 h
// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 48 // 48 h
// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 24 // 24 h
// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 12 // 12 h
// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 6 // 6 h
// var datapoints_interval_in_microseconds = 1000 * 60 * 60 * 1 // 6 h
var startTime = new Date(date.getTime() - datapoints_interval_in_microseconds)
var endTime = new Date(date.getTime())

var midnightsInInterval = getMidnightsInInterval(startTime, endTime)

console.log("start:         " + startTime)

var difference = (new Date(endTime) - new Date(startTime))
var differenceInDays = difference / 24 / 60 / 60 / 1000
// console.log("difference (seconds): " + difference)
// console.log("difference (days):    " + differenceInDays)

var firstMidnightInInterval = new Date(
    startTime.getFullYear(),
    startTime.getMonth(),
    startTime.getDate() + 1
)
var lastMidnightInInterval = new Date(
    endTime.getFullYear(),
    endTime.getMonth(),
    endTime.getDate())
// console.log("first midnigt: " + firstMidnightInInterval)
// console.log("last midnigt:  " + lastMidnightInInterval)

console.log("midnights: ")
midnightsInInterval.forEach((midnight) => {
    console.log("               " + midnight)
})

console.log("")
console.log("end:           " + endTime)